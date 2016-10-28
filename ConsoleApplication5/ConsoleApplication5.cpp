#pragma comment(lib,"Ws2_32.lib") 


#include "stdafx.h" 
#include <WinSock2.h> 
#include <iostream> 
#include <WS2tcpip.h>
#include <thread>

using namespace std;

SOCKET server;
SOCKET client;
bool _end=0;
char *name;
void SendMToServer()
{
	char *buffer = new char[4096];
	for (;; Sleep(100))
	{
		memset(buffer, 0, 10);
		//cout << buffer << endl;
		cin >> buffer;
		if (buffer[0] == '0')
		{
			_end = 1;
			shutdown(client, 1);
			break;
		}
		send(client, name, strlen(buffer), NULL);
		send(client, buffer, strlen(buffer), NULL);
	}
	delete buffer;
}
void GetMFServer()
{
	char *buffer = new char[4096];
	for (;; Sleep(100))
	{
		memset(buffer, 0, strlen(buffer));
		//cout << "123" << endl;
		if (recv(client, buffer, 4096, NULL))
		{
			cout << buffer << endl;
		}
		if (_end == 1)
			break;
	}
	delete buffer;
}

int main()
{
	setlocale(LC_ALL, "russian");
	WSAData data;
	WORD version = MAKEWORD(2, 2);
	int res = WSAStartup(version, &data);     
	if (res != 0)
		return 0;
	name = new char[16];
	cin >> name;
	struct sockaddr_in hints;
	//ZeroMemory(&hints, sizeof(hints));
	hints.sin_family = AF_INET;
	hints.sin_addr.S_un.S_addr = inet_addr("192.168.14.131");
	hints.sin_port = htons(7770);
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(client, (sockaddr *)&hints, sizeof(hints));
	std::thread t1(GetMFServer);
	std::thread t2(SendMToServer);
	t1.join();
	t2.join();
	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GetMFServer, NULL, NULL, NULL);
	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SendMToServer, NULL, NULL, NULL);
	//for (;; Sleep(100));
	//SendMToServer();
	//system("pause");
	return 1;
}