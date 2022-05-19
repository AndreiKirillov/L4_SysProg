#pragma once
#include "framework.h"
#include "Kirillov_lab1_cpp.h"
#include "ThreadStorage.h"

// Класс сервера, который будет обрабатывать подключения клиентов
class Server
{
private:
	
	std::queue<Task> _tasks_to_do;


	Server(Server&);               // запрещаем копирование и присваивание
	Server(const Server&);		 // сделав конструкторы приватными
	Server& operator=(Server&);

	void ProcessClient(HANDLE hConnection);
public:
	Server();
	~Server();

	void WaitForConnection();

	Task GetOldestTask();
};

