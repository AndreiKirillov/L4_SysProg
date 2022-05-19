#pragma once
#include "framework.h"
#include "ThreadStorage.h"

class Server
{
private:
	
	//std::
	ThreadStorage working_threads;


	Server(Server&);               // запрещаем копирование и присваивание
	Server(const Server&);		 // сделав конструкторы приватными
	Server& operator=(Server&);

	void ProcessClient(HANDLE hConnection);
public:
	Server();

	void WaitForConnection();

};

