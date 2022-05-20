#include "pch.h"
#include "Connection.h"

static int MAX_ID = 0;

Connection::Connection(): _id(++MAX_ID), _implementation(), _control_event()
{
}

template <typename Function, typename ...Args>
void Connection::Start(Function&& init_function, Args&&... args)
{
	_implementation = std::thread(std::move(init_function), std::move(args));

	_control_event = CreateEventA(NULL, FALSE, FALSE, NULL);
}