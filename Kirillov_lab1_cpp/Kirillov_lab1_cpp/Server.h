#pragma once
#include "framework.h"
#include "Kirillov_lab1_cpp.h"
#include "ThreadStorage.h"
#include "PipeOperations.h"

// ����� �������, ������� ����� ������������ ����������� ��������
class Server
{
private:
	std::set<std::thread> _connections;
	ThreadStorage _working_threads;
	std::queue<Task> _tasks_to_do;

	void ProcessClient(HANDLE hConnection);
public:
	Server();
	~Server();

	void WaitForConnection();

	Task WaitForTask();
};

