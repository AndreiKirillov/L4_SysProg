#pragma once
#include "framework.h"

class Connection
{
private:
	int _id;
	std::thread _implementation;
	HANDLE _control_event;

	static int MAX_ID;
public:
	Connection();
	~Connection();

	template <typename Function, typename ...Args> 
	void Start(Function&& init_function, Args&&... args);

};

