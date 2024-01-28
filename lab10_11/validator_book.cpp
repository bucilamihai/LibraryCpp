#include <string>

#include "validator_book.h"

void ValidatorBook::validateTitle(const std::string& title)
{
	/*
	This function validates a title
	*/
	if(title == "")
		throw ValidatorException("invalid title!\n");
}

void ValidatorBook::validateAuthor(const std::string& author)
{
	/*
	This function validates an author
	*/
	if (author == "")
		throw ValidatorException("invalid author!\n");
}

void ValidatorBook::validateGenre(const std::string& genre)
{
	/*
	This function validates a genre
	*/
	if (genre == "")
		throw ValidatorException("invalid genre!\n");
}

void ValidatorBook::validateYear(const int& year)
{
	/*
	This function validates a year
	*/
	if (year <= 0)
		throw ValidatorException("invalid year!\n");
}

void ValidatorBook::validateBook(const Book& book)
{
	/*
	This function validates a book
	*/
	std::string message_errors{};
	if (book.getTitle() == "")
		message_errors += "invalid title!\n";
	if (book.getAuthor() == "")
		message_errors += "invalid author!\n";
	if (book.getGenre() == "")
		message_errors += "invalid genre!\n";
	if (book.getYear() <= 0)
		message_errors += "invalid year!\n";
	if (message_errors.size() > 0)
		throw ValidatorException(message_errors);
}