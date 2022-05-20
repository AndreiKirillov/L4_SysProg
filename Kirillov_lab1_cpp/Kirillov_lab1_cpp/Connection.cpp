#include "pch.h"
#include "Connection.h"

int Connection::MAX_ID = 0;

Connection::Connection(): _id(++MAX_ID), _implementation()
{
}

Connection::Connection(Connection&& connection)
{
	_id = connection._id;
	_implementation = std::move(connection._implementation);
}

Connection::~Connection()
{
	if (_implementation.joinable())
		_implementation.detach();
}

int Connection::GetID() const
{
	return _id;
}

bool operator<(const Connection& a, const Connection& b)
{
	return a._id < b._id;
}
