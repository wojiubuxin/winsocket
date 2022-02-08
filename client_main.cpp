#include <winsock2.h>
#include <iostream>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")  //静态加载ws2_32.lib
using namespace std;
struct fuckstruct
{
	int num;
	char name[10];
};
int main()
{
	SOCKET clientsocket;
	SOCKADDR_IN serveraddr;
	SOCKADDR_IN clientaddr;
	char buf[1024];
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);	//初始化WS2_32.DLL
	if ((clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		cout << "创建套接字失败" << endl;
		return -1;
	}
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9102);
//	serveraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET, "127.0.0.1", (void*)&serveraddr.sin_addr.S_un.S_addr);
	cout<<"尝试连接中...\n";

	if (connect(clientsocket, (SOCKADDR *)&serveraddr, sizeof(serveraddr)) != 0)
	{
		cout << "连接失败...\n";
		return -1;
	}
	cout << "连接成功...开始敲字发送\n";
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		cin >> buf;
		cout << strlen(buf)<<endl;
		cout << sizeof(buf) << endl;
		if (send(clientsocket, buf, strlen(buf) + 1, 0) <= 0)
		{
			cout << "发送错误\n";
		}
		
		Sleep(10);
		memset(buf, 0, sizeof(buf));


		if (recv(clientsocket, buf, 1024, 0) <= 0)
		{
			cout << "客户端接收错误\n";
			break;
		}
		fuckstruct fuckflag;
		memcpy(&fuckflag, buf, sizeof(fuckflag));


		cout << "接受服务端发来的信息:" << fuckflag.name<<"-----"<<fuckflag.num<<endl;
	}
	

	system("pause");
	return 0;
}

