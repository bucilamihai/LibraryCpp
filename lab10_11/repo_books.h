#pragma once

#include <vector>

#include "book.h"
#include "exceptions.h"

class Repo
{
private:
	std::vector<Book> book_list{};

public:
	Repo() = default;
	virtual void repoAddBook(const Book& book_to_add);
	virtual void repoDeleteBook(const std::string& title);
	virtual void repoModifyBook(const std::string& title, const Book& new_book);
	virtual std::vector<Book> repoGetAllBooks();
	virtual Book repoFindBook(const std::string& title) const;
	virtual void repoDeleteAllBooks();
	virtual ~Repo() = default;
};