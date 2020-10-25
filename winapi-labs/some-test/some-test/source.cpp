/*
#include <stdio.h>
#include <stdlib.h>

#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable : 4996)

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

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
		sa.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		connect(s, (const sockaddr*)&sa, sizeof(SOCKADDR_IN));

		CONST INT arr[] = { 1, 2, 3, 4, 5 };
		send(s, (CONST CHAR*)arr, sizeof(arr), 0);

		CHAR from_server[22];
		memset(&from_server, 0, sizeof(from_server));
		recv(s, from_server, sizeof(from_server), 0);
		printf(from_server);

		Sleep(3000);
	}

	if (c == 's')
	{
		bind(s, (const sockaddr*)&sa, sizeof(SOCKADDR_IN));
		listen(s, 100);

		INT buf[5];
		memset(&buf, 0, sizeof(INT));
		SOCKET client_socket;
		SOCKADDR_IN client_addr;
		INT client_addr_size = sizeof(SOCKADDR_IN);

		while (client_socket = accept(s, (sockaddr*)&client_addr, &client_addr_size))
		{
			printf("connect OK\n");

			while (recv(client_socket, (CHAR*)buf, sizeof(buf), 0) > 0)
			{
				for (int i = 0; i < 5; ++i)
					printf("%d,", *(buf + i));

				const char reply[22] = "hello world, client\0";
				send(client_socket, reply, sizeof(reply), 0);
			}
		}
	}

	closesocket(s);
	system("pause");

	return 0;
}
*/