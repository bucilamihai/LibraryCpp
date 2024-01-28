#pragma once


#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#include "repo_books.h"
#include "service_books.h"
#include "validator_book.h"


class UndoAction;

class Service
{
private:
	Repo& repo_books;
	ValidatorBook& validator_book;
	std::vector<UndoAction*> undo_actions{};

public:
	Service() = default;
	Service(Repo& repo_books, ValidatorBook& validator_book) noexcept 
		: repo_books{ repo_books }, validator_book{ validator_book } {}
	void serviceAddBook(const std::string& title, const std::string& author, const std::string& genre, const int& year);
	void serviceDeleteBook(const std::string& title);
	void serviceModifyBook(const std::string& title, const std::string& new_title, const std::string& new_author, const std::string& new_genre, const int& new_year);
	std::vector<Book> serviceGetBookList() const;
	Book serviceFindBook(const std::string& title);
	
	std::vector<Book> serviceFilterByTitle(const std::string& title);
	std::vector<Book> serviceFilterByYear(const int& lower_bound_year, const int& upper_bound_year);

	std::vector<Book> serviceSortByTitle() const;
	std::vector<Book> serviceSortByAuthor() const;
	std::vector<Book> serviceSortByYearAndGenre() const;

	void undo();
	std::vector<std::string> getListOfGenres();
};


class UndoAction
{
	// abstract class
public:
	virtual void doUndo() = 0; // pure virtual function	
	virtual ~UndoAction() {};
};


class UndoAdd : public UndoAction
{
private:
	Book book_to_delete;
	Repo& repo_books;
public:
	UndoAdd(const Book& book, Repo& repo_books) 
		: book_to_delete{ book }, repo_books{ repo_books } {}
	void doUndo() override
	{
		repo_books.repoDeleteBook(book_to_delete.getTitle());
	}
};

class UndoDelete : public UndoAction
{
private:
	Book book_to_add;
	Repo& repo_books;
public:
	UndoDelete(const Book& book, Repo& repo_books)
		: book_to_add{ book }, repo_books{ repo_books } {}
	void doUndo() override
	{
		repo_books.repoAddBook(book_to_add);
	}
};

class UndoModify : public UndoAction
{
private:
	Book book_before_modify;
	Book book_after_modify;
	Repo& repo_books;
public:
	UndoModify(const Book& book_before, const Book& book_after, Repo& repo_books)
		: book_before_modify{ book_before }, book_after_modify{ book_after }, repo_books{ repo_books } {}
	void doUndo() override
	{
		repo_books.repoModifyBook(book_after_modify.getTitle(), book_before_modify);
	}
};