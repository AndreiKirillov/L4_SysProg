#pragma once

#include "resource.h"
#include "framework.h"

using namespace std;

struct header // заголовок для сообщения
{
    int event_code;
    int thread_id;
    int message_size;
};

// тип задачи для обработки сервером
enum class Task
{
	nothing, start_thread, stop_thread, process_message
};

