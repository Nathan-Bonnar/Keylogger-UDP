//Nathan Bonnar - Keylogger Example - Sends data via UDP
#include<stdio.h>
#include<WS2tcpip.h>
#include<WinSock2.h>
#include<string.h>
#include<memory.h>
#include<string.h>
#include<stdlib.h>
#include<io.h>
#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")
#define MAXLINE 1024
#define SERV_LEN 256
#define HOST_LEN 256
#define DEFAULT_DATA 4
#define MAX 80
#define PORT 8080	
int main()
{
	char negativeidenfier[] = { "[-]" };
	char positiveidentfier[] = { "[+]" };
	int sockfd, connfd, len = { 0 };
	struct sockaddr_in servaddr;
	struct sockaddr_in cli;
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	char RecvBuf[1024];
	int buflen = 1024;
	struct in_addr inaddrbuff;
	wVersionRequested = MAKEWORD(2, 2);
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

	
	ZeroMemory(&servaddr, sizeof(servaddr));
	memset(&cli, 0, sizeof(cli));
	
	
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(sockfd, (SOCKADDR*)&servaddr, sizeof(servaddr)) < 0)
	{
		printf("%s BIND failed\n", negativeidenfier);
		printf("%d\n", WSAGetLastError());
		exit(0);
	}
	else
	{
		printf("%s socket was bound to port successfully\n",positiveidentfier);
	}
	int servaddrlen = sizeof(servaddr);
	getsockname(sockfd, (SOCKADDR*)&servaddr, (int*)&servaddrlen);

	printf("Server: Receiving IP(s) used: %s\n", inet_ntoa(servaddr.sin_addr));

	printf("Server: Receiving port used: %d\n", htons(servaddr.sin_port));

	printf("Server: I\'m ready to receive data packages. Waiting...\n\n");

	int n;
	int clilen = sizeof(cli);
	while (1) 
	{
		n = recvfrom(sockfd, RecvBuf, buflen, 0, (SOCKADDR*)&cli, &clilen);
		if (n == SOCKET_ERROR) {
			wprintf(L"recvfrom failed with error: %d\n", WSAGetLastError());
			closesocket(sockfd);
			WSACleanup();
			return 1;
		}
		else
		{
			printf("Server: Total Bytes received: %d\n", n);
			printf("Server: The data is: %s\n", RecvBuf);
			printf("\n");
		}
	
	}	
	closesocket(sockfd);
	WSACleanup();
}
