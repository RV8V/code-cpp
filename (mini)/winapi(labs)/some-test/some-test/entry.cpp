#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996)

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

void chat(SOCKET s)
{
	char message[200];
	WSAEventSelect(s, 0, FD_READ);
	do
	{
		if (GetKeyState(VK_F1) < 0 && GetForegroundWindow() == GetConsoleWindow())
		{
			printf("message: ");
			while (getch() != 0);
			scanf("\n%200[0-9a-zA-Z.,! ]", message);
			send(s, message, sizeof(message), 0);
		}

		if (recv(s, message, sizeof(message), 0) > 0)
			printf("%s\n", message);
	} while (GetKeyState(VK_ESCAPE) >= 0);
}

int main()
{
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);

	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
		memset(&sa, 0, sizeof(SOCKADDR_IN));
		sa.sin_family = AF_INET;
		sa.sin_port = htons(1234);

	CHAR c;
	printf("s - server\nk - client\n");
	scanf("%c", &c);

	if (c == 'k')
	{
		char ip[100];
		printf("set ip address: ");
		scanf("\n%100[0-9]", ip);

		sa.sin_addr.S_un.S_addr = inet_addr(ip);
		connect(s, (const sockaddr*)&sa, sizeof(SOCKADDR_IN));

		chat(s);
	}

	if (c == 's')
	{
		bind(s, (const sockaddr*)&sa, sizeof(SOCKADDR_IN));
		listen(s, 100);

		char buf[200];
		memset(&buf, 0, sizeof(INT));
			SOCKET client_socket;
			SOCKADDR_IN client_addr;
			INT client_addr_size = sizeof(SOCKADDR_IN);

		while (client_socket = accept(s, (sockaddr*)&client_addr, &client_addr_size))
		{
			printf("connect OK\n");
			chat(client_socket);
		}
	}

	closesocket(s);
	system("pause");

	return 0;
}