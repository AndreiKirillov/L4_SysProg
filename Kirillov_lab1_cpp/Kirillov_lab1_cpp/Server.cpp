#include "pch.h"
#include "Server.h"

extern std::mutex console_mtx;

Server::Server(): _tasks_to_do()
{
}

Server::~Server()
{
}

// Функция обработки подключенного клиента, будет выполняться в потоке. 
void Server::ProcessClient(HANDLE hPipe)
{
	while (true)
	{
		//string s = GetString(hPipe);
		//cout << s << endl;
		//if (s == "quit")
		{
			break;
		}
		//SendInt(hPipe, ++i);
	}
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
}

// Функция подключения нового клиента к серверу
void Server::WaitForConnection()    
{
	while (true)
	{
		HANDLE hPipe = CreateNamedPipeA("\\\\.\\pipe\MyPipe_lab4", PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES, 1024, 1024, 0, NULL);

		if (!ConnectNamedPipe(hPipe, NULL))
		{
			std::lock_guard<std::mutex> console_lock(console_mtx);
			std::cout << "Server error connecting to client!" << std::endl;
		}
		else
		{

		}
	}
}

Task Server::GetOldestTask()
{
	Task front_task = _tasks_to_do.front();
	_tasks_to_do.pop();
	return front_task;
}
