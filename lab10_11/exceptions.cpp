#include "exceptions.h"

RepoException::RepoException(const std::string& message_error)
{
	/*
	This function creates a new exception (constructor)
	*/
	this->message_error = message_error;
}

std::string RepoException::getMessageError()
{
	return this->message_error;
}

ValidatorException::ValidatorException(const std::string& message_error)
{
	/*
	This function creates a new exception (constructor)
	*/
	this->message_error = message_error;
}

std::string ValidatorException::getMessageError()
{
	return this->message_error;
}