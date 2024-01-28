#pragma once

#include <string>

class RepoException
{
private:
	std::string message_error;

public:
	RepoException(const std::string& message_error);
	std::string getMessageError();
};

class ValidatorException
{
private:
	std::string message_error;

public:
	ValidatorException(const std::string& message_error);
	std::string getMessageError();
};
