#pragma once
#include "framework.h"
#include "Kirillov_lab1_cpp.h"
#include "ThreadStorage.h"
#include "PipeOperations.h"
#include "Connection.h"

// Класс сервера, который будет обрабатывать подключения клиентов
class Server
{
private:
	std::set<Connection> _connections;
	ThreadStorage _working_threads;


	void ProcessClient(HANDLE hConnection, int client_id);
	void CloseClient(int client_id);
public:
	Server();
	~Server();

	void WaitForConnection();

	int GetClientsCount();
};

