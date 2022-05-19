#pragma once
#include "framework.h"
#include "Kirillov_lab1_cpp.h"
#include "ThreadStorage.h"

// ����� �������, ������� ����� ������������ ����������� ��������
class Server
{
private:
	
	std::queue<Task> _tasks_to_do;
	ThreadStorage _working_threads;


	Server(Server&);               // ��������� ����������� � ������������
	Server(const Server&);		 // ������ ������������ ����������
	Server& operator=(Server&);

	void ProcessClient(HANDLE hConnection);
public:
	Server();
	~Server();

	void WaitForConnection();

	Task GetOldestTask();
};

