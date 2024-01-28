#include <iostream>
#include <string>

#include "book.h"


Book::Book(const std::string& title, const std::string& author, const std::string& genre, const int& year)
{
	/*
	This function is the constructor for class Book
	*/
	this->title = title;
	this->author = author;
	this->genre = genre;
	this->year = year;
}

Book::Book(const Book& other)
{
	/*
	This function is the copy constructor for class Book
	*/
	this->title = other.title;
	this->author = other.author;
	this->genre = other.genre;
	this->year = other.year;
	//std::cout << " ~~ copy constructor ~~\n";
}

Book::Book(Book&& other)
{
	/*
	This function is the move constructor for class Book
	*/
	this->title = other.title;
	this->author = other.author;
	this->genre = other.genre;
	this->year = other.year;
	other.title = "";
	other.author = "";
	other.genre = "";
	other.year = -1;
	//std::cout << " ~~ move constructor ~~\n";
}

std::string Book::getTitle() const
{
	/*
	This function returns the book's title
	*/
	return this->title;
}

std::string Book::getAuthor() const
{
	/*
	This function returns the book's author
	*/
	return this->author;
}

std::string Book::getGenre() const
{
	/*
	This function returns the book's genre
	*/
	return this->genre;
}

int Book::getYear() const noexcept
{
	/*
	This function returns the book's year of publication
	*/
	return this->year;
}

void Book::setTitle(const std::string& new_title)
{
	/*
	This function sets a new title for a book
	*/
	this->title = new_title;
}

void Book::setAuthor(const std::string& new_author)
{
	/*
	This function sets a new author for a book
	*/
	this->author = new_author;
}

void Book::setGenre(const std::string& new_genre)
{
	/*
	This function sets a new genre for a book
	*/
	this->genre = new_genre;
}

void Book::setYear(const int& new_year) noexcept
{
	/*
	This function sets a new year for a book
	*/
	this->year = new_year;
}

bool Book::operator==(const Book& other) const
{
	/*
	This function overloads equality operator
	*/
	return this->getTitle() == other.getTitle() &&
		this->getAuthor() == other.getAuthor() &&
		this->getGenre() == other.getGenre() &&
		this->getYear() == other.getYear();
}

Book& Book::operator=(const Book& other)
{
	/*
	This function overloads assignment operator
	*/
	this->setTitle(other.getTitle());
	this->setAuthor(other.getAuthor());
	this->setGenre(other.getGenre());
	this->setYear(other.getYear());
	return *this;
}

Book& Book::operator=(Book&& other)
{
	/*
	This function overloads assignment operator
	*/
	this->setTitle(other.getTitle());
	this->setAuthor(other.getAuthor());
	this->setGenre(other.getGenre());
	this->setYear(other.getYear());
	other.title = "";
	other.author = "";
	other.genre = "";
	other.year = -1;
	return *this;
}