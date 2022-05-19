#pragma once

#include "resource.h"
#include "framework.h"

using namespace std;

struct header // ��������� ��� ���������
{
    int event_code;
    int thread_id;
    int message_size;
};

// ��� ������ ��� ��������� ��������
enum class Task
{
	nothing, start_thread, stop_thread, process_message
};

