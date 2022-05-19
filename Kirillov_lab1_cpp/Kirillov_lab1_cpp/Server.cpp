#include "pch.h"
#include "Server.h"

extern std::mutex console_mtx;

Server::Server(): working_threads()
{
}

void Server::ProcessClient(HANDLE hConnection)
{

}

// Функция подключения нового клиента к серверу
void Server::WaitForConnection()    
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
