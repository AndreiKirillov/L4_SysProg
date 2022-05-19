// FileMapping.cpp: определяет процедуры инициализации для библиотеки DLL.
//

#include "pch.h"
#include "framework.h"
#include "FileMapping.h"
#include <string>
#include <vector>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
//
//TODO: если эта библиотека DLL динамически связана с библиотеками DLL MFC,
//		все функции, экспортированные из данной DLL-библиотеки, которые выполняют вызовы к
//		MFC, должны содержать макрос AFX_MANAGE_STATE в
//		самое начало функции.
//
//		Например:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// тело нормальной функции
//		}
//
//		Важно, чтобы данный макрос был представлен в каждой
//		функции до вызова MFC.  Это означает, что
//		должен стоять в качестве первого оператора в
//		функции и предшествовать даже любым объявлениям переменных объекта,
//		поскольку их конструкторы могут выполнять вызовы к MFC
//		DLL.
//
//		В Технических указаниях MFC 33 и 58 содержатся более
//		подробные сведения.
//

// CFileMappingApp

BEGIN_MESSAGE_MAP(CFileMappingApp, CWinApp)
END_MESSAGE_MAP()


// Создание CFileMappingApp

CFileMappingApp::CFileMappingApp()
{
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект CFileMappingApp

CFileMappingApp theApp;


// Инициализация CFileMappingApp

BOOL CFileMappingApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

// структура для заголовка сообщения
struct header    
{
	int event_code;
	int thread_id;
	int message_size;
};


HANDLE hClientPipe;


extern "C"
{
	// Функция подключения клиента к серверу
	__declspec(dllexport) bool __stdcall ConnectToServer()
	{
		if (!WaitNamedPipeA("\\\\.\\pipe\\MyPipe_lab4", 3000))
		{
			return false;
		}
		else
		{
			HANDLE hPipe = CreateFileA("\\\\.\\pipe\\MyPipe_lab4", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
			if (hPipe == INVALID_HANDLE_VALUE)
				return false;
			else
			{
				hClientPipe = hPipe;      // Сохраняем хэндл канала
				return true;
			}
		}
	}

	__declspec(dllexport) bool __stdcall SendMessageToServer(const char* message, header& h)
	{
		DWORD dwWrite;
		if (!WriteFile(hClientPipe, &h, sizeof(header), &dwWrite, nullptr) || dwWrite == 0) // пишем заголовок
			return false;

		dwWrite = 0;
		if (!WriteFile(hClientPipe, message, strlen(message) + 1, &dwWrite, nullptr) || dwWrite == 0) // пишем тело сообщения
			return false;
		return true;
	}

}

// Функция чтения заголовка сообщения
__declspec(dllexport) header __stdcall ReadHeader()
{
	header received_header{ -1,-1,-1 };

	DWORD dwRead;
	if (!ReadFile(hClientPipe, &received_header, sizeof(header), &dwRead, nullptr) || dwRead == 0)
		return header{ -1,-1,-1 };

	return received_header;
}

//string ReadFromServer()
//{
//	DWORD dwDone;
//	int nLength = GetInt(hPipe);
//
//	vector <char> v(nLength);
//	ReadFile(hPipe, &v[0], nLength, &dwDone, NULL);
//	return string(&v[0], nLength);
//}
