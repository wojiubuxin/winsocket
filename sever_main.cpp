#include<iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")  //��̬����ws2_32.lib
using namespace std;
int main()
{
	struct fuckstruct
	{
		int num;
		char name[10];
	};
	SOCKET serversoc;
	SOCKET clientsoc;
	SOCKADDR_IN serveraddr;
	SOCKADDR_IN clientaddr;
	char buf[1024];

	int len = sizeof(clientaddr);
	WSADATA wsa;
	int fuckflag = WSAStartup(MAKEWORD(2, 2), &wsa);
	serversoc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9102);
	serveraddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	fuckflag = _WINSOCK2API_::bind(serversoc, (SOCKADDR*)&serveraddr, sizeof(SOCKADDR));

	cout << "��ʼ����\n";

	listen(serversoc, 1);
	clientsoc = _WINSOCK2API_::accept(serversoc, (SOCKADDR*)&clientaddr, &len);
	cout << "������:" << clientsoc << endl;
	cout << WSAGetLastError() << endl;
	cout << fuckflag << endl;
	cout << serversoc << endl;
	int i = 0;
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		int fuck = recv(clientsoc, buf, 1024, 0);
		if (fuck <= 0)
		{
			cout << "�ͻ��˹ر�����:" << fuck << endl;
			break;
		}

		fuckstruct fuckflag;
		memset(&fuckflag, 0, sizeof(fuckflag));
		fuckflag.num = i;
		memcpy(fuckflag.name, buf, sizeof(fuckflag.name));

		cout << "������յ��ͻ��˷��͵�����:" << buf << "----" << sizeof(fuckflag) << endl;;
		memset(buf, 0, sizeof(buf));
		memcpy(buf, &fuckflag, sizeof(fuckflag));
		//cout << "�����׼����������:" << "----" << sizeof(buf) << endl;;
		if (send(clientsoc, buf, sizeof(fuckflag) + 1, 0) <= 0)
		{
			cout << "�����ͻ��˴���\n";
		}
		i++;
	}



	closesocket(serversoc);
	closesocket(clientsoc);
	WSACleanup();

	system("pause");
	return 0;
}