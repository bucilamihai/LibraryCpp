#pragma once

#include <string>


class Book
{
private:
	std::string title;
	std::string author;
	std::string genre;
	int year = 0;

public:
	Book() = default;
	Book(const std::string& title, const std::string& author, const std::string& genre, const int& year);
	Book(const Book& other); // copy constructor
	Book(Book&& other); // move constructor

	std::string getTitle() const;
	std::string getAuthor() const;
	std::string getGenre() const;
	int getYear() const noexcept;

	void setTitle(const std::string& new_title);
	void setAuthor(const std::string& new_author);
	void setGenre(const std::string& new_genre);
	void setYear(const int& new_year) noexcept;

	bool operator==(const Book& other) const;
	Book& operator=(const Book& other); // (copy) assignment operator
	Book& operator=(Book&& other); // (move) assignment operator
};