#pragma once

#include "resource.h"


// тип задачи для обработки сервером
enum class Task
{
	start_thread, stop_thread, process_message
};