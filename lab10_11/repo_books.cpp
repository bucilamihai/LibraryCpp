#include "repo_books.h"


void Repo::repoAddBook(const Book& book_to_add)
{
	/*
	This function adds a new car to the book list
	*/
	bool found{ false };
	for (const auto& i : this->book_list)
		if (&i != nullptr && i == book_to_add)
			found = true;
	std::string message_error;
	if (found)
		throw RepoException("existing book!\n");
	this->book_list.push_back(book_to_add);
}

void Repo::repoDeleteBook(const std::string& title)
{
	/*
	This function deletes from the book list the book with the title *title*
	*/
	bool found{ false };
	for (const auto& i : this->book_list)
		if (&i != nullptr && i.getTitle() == title)
		{
			this->book_list.erase(find(this->book_list.begin(), this->book_list.end(), i));
			found = true;
		}	
	if (!found)
		throw RepoException("inexisting book!\n");
}

void Repo::repoModifyBook(const std::string& title, const Book& new_book)
{
	/*
	This function modifies the book with the title *title*
	*/
	bool found{ false };
	for (auto& i : this->book_list)
		if (&i != nullptr && i.getTitle() == title)
		{
			i = new_book;
			found = true;
		}
	std::string message_error;
	if (!found)
		throw RepoException("inexisting book!\n");
}

std::vector<Book> Repo::repoGetAllBooks()
{
	/*
	This function returns a vector with all the books
	*/
	std::vector<Book> all_books;
	for (const auto& i : this->book_list)
	{
		if (&i != nullptr)
		{
			all_books.push_back(i);
		}
	}
	return all_books;
}

Book Repo::repoFindBook(const std::string& title) const
{
	/*
	This function searches a book with the title *title* and returns it
	*/
	auto find_book = std::find_if(this->book_list.begin(), this->book_list.end(), [title](const Book& book) {return book.getTitle() == title; });
	std::string message_error{};
	if (find_book == this->book_list.end())
		throw RepoException("book not found!\n");
	Book book_found = *find_book;
	return book_found;
}

void Repo::repoDeleteAllBooks()
{
	/*
	This function deletes all books from book list
	*/
	this->book_list.clear();
}