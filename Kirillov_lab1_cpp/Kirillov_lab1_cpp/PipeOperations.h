#pragma once
#include "framework.h"
#include "Kirillov_lab1_cpp.h"

using namespace std;

inline header ReadHeader(HANDLE hPipe)
{
	DWORD dwDone;
	header h{ -1,-1,-1 };

	if (!ReadFile(hPipe, &h, sizeof(header), &dwDone, NULL) || dwDone == 0)
		return header{ -1,-1,-1 };
	return h;
}

inline void SendInt(HANDLE hPipe, int n, bool bFlush = true)
{
	DWORD dwDone;
	WriteFile(hPipe, &n, sizeof(n), &dwDone, NULL);
	if (bFlush)
		FlushFileBuffers(hPipe);
}

inline string GetString(HANDLE hPipe)
{
	header msg_header = ReadHeader(hPipe);
	if(msg_header.)


	DWORD dwDone;
	vector <char> v(msg);
	ReadFile(hPipe, &v[0], nLength, &dwDone, NULL);
	return string(&v[0], nLength);
}

inline void SendString(HANDLE hPipe, const string& s)
{
	DWORD dwDone;
	int nLength = s.length();

	SendInt(hPipe, nLength, false);
	WriteFile(hPipe, s.c_str(), nLength, &dwDone, NULL);
	FlushFileBuffers(hPipe);
}
