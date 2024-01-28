#pragma once

#include <string>

#include "book.h"
#include "exceptions.h"

class ValidatorBook
{
public:
	void validateTitle(const std::string& title);
	void validateAuthor(const std::string& author);
	void validateGenre(const std::string& genre);
	void validateYear(const int& year);
	void validateBook(const Book& book);
};