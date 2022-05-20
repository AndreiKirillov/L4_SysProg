#include "pch.h"
#include "Server.h"

extern mutex console_mtx;
extern shared_mutex data_mtx;
extern shared_ptr<string> ptr_global_message;
extern HANDLE confirm_finish_of_thread_event;

Server::Server(): _connections(),_working_threads(), _tasks_to_do()
{
}

Server::~Server()
{
	/*for (auto thread_connection : _connections)
	{
		if (thread_connection.joinable())
			thread_connection.detach();
	}*/
}

// Функция обработки подключенного клиента, будет выполняться в потоке. 
void Server::ProcessClient(HANDLE hPipe)
{
    while (true)
    {
        header client_header = ReadHeader(hPipe);

        switch (client_header.task_code)
        {
        case Task::start_thread:         // Событие создания потока
        {
            std::unique_ptr<ThreadKirillov> new_thread = std::make_unique<ThreadKirillov>(); // Новый объект потока

            // параметры для потока
            int thread_id = _working_threads.GetCount() + 1;
            HANDLE thread_finish_event = CreateEventA(NULL, FALSE, FALSE, NULL);
            HANDLE thread_msg_event = CreateEventA(NULL, FALSE, FALSE, NULL);
            if (thread_finish_event == NULL || thread_msg_event == NULL)
                break;

            std::weak_ptr<string> wptr_to_message(ptr_global_message); // передадим в поток этот указатель на сообщение из канала

            // инициализируем объект реальным потоком
            new_thread->Init(std::thread(ThreadFunction, thread_id, thread_finish_event, thread_msg_event, std::move(wptr_to_message)));
            new_thread->SetID(thread_id);
            new_thread->SetFinishEvent(thread_finish_event);
            new_thread->SetMessageEvent(thread_msg_event);

            _working_threads.AddThread(std::move(new_thread));   // Помещаем в общее хранилище потоков
            //SetEvent(confirm_event);
        }
        break;

        case Task::stop_thread:              // Событие завершения потока
        {
            if (_working_threads.GetCount() > 0)
            {
                _working_threads.FinishLastThread();
                WaitForSingleObject(confirm_finish_of_thread_event, INFINITE); // Ждём завершение потока
                _working_threads.DeleteLastThread();                            // Только после этого освобождаем ресурсы
                //SetEvent(confirm_event);
            }
            else      // Освобождаем все ресурсы, если нет активных потоков
            {
                //SetEvent(close_programm_event);
                //threads_storage.KillAndReleaseAll();

                CloseHandle(confirm_finish_of_thread_event);
                return;
            }
        }
        break;

        case Task::process_message:
        {
            if (client_header.message_size != 0)
            {
                std::string client_message = ReadMessage(hPipe, client_header);  // читаем сообщение из именованного канала
                if (client_message == "quit")
                {
                    DisconnectNamedPipe(hPipe);      // отключение клиента от сервера
                    CloseHandle(hPipe);
                    return;
                }

                unique_lock<shared_mutex> writing_data_lock(data_mtx); // монопольный захват мьютекса для записи нового сообщения 
                                                                  // в этот момент потоки с общей блокировкой не смогут читать
                *ptr_global_message = client_message;  
                writing_data_lock.unlock();                          // освобождаем монопольный захват

                switch (client_header.thread_id)
                {
                case -1:                               // Чтение из всех потоков
                {
                    ProcessMessage(ptr_global_message);
                    _working_threads.ActionAll();
                }
                break;

                case 0:                                // Чтение из главного потока
                {
                    ProcessMessage(ptr_global_message);
                }
                break;

                default:                              // Чтение из произвольного потока
                {
                    try
                    {
                        _working_threads.ActionThreadByID(client_header.thread_id);
                    }
                    catch (exception ex)             // вдруг нет потока с данным id
                    {
                        lock_guard<mutex> console_lock(console_mtx);
                        cout << ex.what() << endl;
                    }
                }
                }

            }
            // SetEvent(confirm_event);
        }
        }
    }
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
			_connections.insert(std::thread(&Server::ProcessClient, this, hPipe));  // запускаем обработку клиента в отдельном потоке
		}
	}
}

Task Server::WaitForTask()
{
	//while
	Task front_task = _tasks_to_do.front();
	_tasks_to_do.pop();
	return front_task;
}
