#pragma once
#include "framework.h"
#include "Kirillov_lab1_cpp.h"
#include "ThreadStorage.h"
#include "PipeOperations.h"

// ����� �������, ������� ����� ������������ ����������� ��������
class Server
{
private:
	std::vector<std::thread> _connections;
	ThreadStorage _working_threads;


	void ProcessClient(HANDLE hConnection);
public:
	Server();
	~Server();

	void WaitForConnection();

	int GetClientsCount();
};

