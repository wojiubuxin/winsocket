#include <winsock2.h>
#include <iostream>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")  //��̬����ws2_32.lib
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
	WSAStartup(MAKEWORD(2, 2), &wsa);	//��ʼ��WS2_32.DLL
	if ((clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) <= 0)
	{
		cout << "�����׽���ʧ��" << endl;
		return -1;
	}
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9102);
//	serveraddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET, "127.0.0.1", (void*)&serveraddr.sin_addr.S_un.S_addr);
	cout<<"����������...\n";

	if (connect(clientsocket, (SOCKADDR *)&serveraddr, sizeof(serveraddr)) != 0)
	{
		cout << "����ʧ��...\n";
		return -1;
	}
	cout << "���ӳɹ�...��ʼ���ַ���\n";
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		cin >> buf;
		cout << strlen(buf)<<endl;
		cout << sizeof(buf) << endl;
		if (send(clientsocket, buf, strlen(buf) + 1, 0) <= 0)
		{
			cout << "���ʹ���\n";
		}
		
		Sleep(10);
		memset(buf, 0, sizeof(buf));


		if (recv(clientsocket, buf, 1024, 0) <= 0)
		{
			cout << "�ͻ��˽��մ���\n";
			break;
		}
		fuckstruct fuckflag;
		memcpy(&fuckflag, buf, sizeof(fuckflag));


		cout << "���ܷ���˷�������Ϣ:" << fuckflag.name<<"-----"<<fuckflag.num<<endl;
	}
	

	system("pause");
	return 0;
}

