// PipeClient.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <windows.h>
#include <iostream>
#include <conio.h>

struct header // заголовок для сообщения
{
	int task_code;
	int thread_id;
	int message_size;
};

extern "C"
{
	__declspec(dllimport) bool __stdcall ConnectToServer();
	__declspec(dllimport) bool __stdcall SendMessageToServer(const char* message, header& h);
}

using namespace std;

int main()
{
	if (ConnectToServer())
	{
		while (true)
		{
			string s;
			cin >> s;

			header msg_header{ 2, 0, s.size() };

			SendMessageToServer(s.c_str(), msg_header);
			if (s == "quit")
			{
				break;
			}
			//cout << GetInt(hPipe) << endl;
		}
	}
	else
	{
		cout << "No pipes available" << endl;
		_getch();
	}
}