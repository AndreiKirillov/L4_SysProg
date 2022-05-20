#pragma once
#include "framework.h"
#include "Kirillov_lab1_cpp.h"

using namespace std;

inline header ReadHeader(HANDLE hPipe)
{
	DWORD dwDone;
	header h;
	ReadFile(hPipe, &h, sizeof(header), &dwDone, NULL);
	/*if (!ReadFile(hPipe, &h, sizeof(header), &dwDone, NULL) || dwDone == 0)
		return header{ 0,-1,-1 };*/
	return h;
}

inline void SendConfirm(HANDLE hPipe, int n, bool bFlush = true)
{
	DWORD dwDone;

	WriteFile(hPipe, &n, sizeof(n), &dwDone, NULL);
	if (bFlush)
		FlushFileBuffers(hPipe);
}

inline string ReadMessage(HANDLE hPipe, const header& h)
{
	DWORD dwDone;
	vector <char> v(h.message_size);
	ReadFile(hPipe, &v[0], h.message_size, &dwDone, NULL);
	return string(&v[0], h.message_size);
}

inline void SendString(HANDLE hPipe, const string& s)
{
	DWORD dwDone;
	int nLength = s.length();

	SendInt(hPipe, nLength, false);
	WriteFile(hPipe, s.c_str(), nLength, &dwDone, NULL);
	FlushFileBuffers(hPipe);
}
