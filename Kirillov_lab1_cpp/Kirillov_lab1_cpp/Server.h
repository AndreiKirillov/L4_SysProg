#pragma once
#include "framework.h"
#include "ThreadStorage.h"

class Server
{
private:
	
	//std::
	ThreadStorage working_threads;


	Server(Server&);               // ��������� ����������� � ������������
	Server(const Server&);		 // ������ ������������ ����������
	Server& operator=(Server&);

	void ProcessClient(HANDLE hConnection);
public:
	Server();

	void WaitForConnection();

};

