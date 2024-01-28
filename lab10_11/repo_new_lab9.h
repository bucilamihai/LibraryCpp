#pragma once

#include <random>
#include <map>
#include <iostream>

#include "repo_books.h"

class NewRepo : public Repo
{
private:
	std::map<std::string, Book> book_list{};
	int probability;
public:
	NewRepo(int probability) : probability{ probability % 100 } {}

	int pickNumber() const
	{
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution<> distribution(0, 100);
		const int random_number = distribution(mt);// random number between [0, 100]
		return random_number;
	}

	void repoAddBook(const Book& book_to_add) override
	{
		/*
		This function adds a new car to the book list
		*/
		const int probability_action = pickNumber();
		if (probability_action < this->probability)
		{
			bool found{ false };
			for (const auto& book : this->book_list)
				if (&book != nullptr && book.second == book_to_add)
					found = true;
			std::string message_error;
			if (found)
				throw RepoException("existing book!\n");
			this->book_list.insert(std::pair<std::string, Book>(book_to_add.getTitle(), book_to_add));
		}
		else
		{
			std::string error_message{ "probability!\n" };
			throw error_message;
		}
	}

	void repoDeleteBook(const std::string& title) override
	{
		/*
		This function deletes from the book list the book with the title *title*
		*/
		const int probability_action = pickNumber();
		if (probability_action < this->probability)
		{
			bool found{ false };
			for (const auto& book : this->book_list)
				if (&book != nullptr && book.second.getTitle() == title)
				{
					this->book_list.erase(find(this->book_list.begin(), this->book_list.end(), book));
					found = true;
				}
			if (!found)
				throw RepoException("inexisting book!\n");
		}
		else
		{
			std::string error_message{ "probability!\n" };
			throw error_message;
		}
	}

	void repoModifyBook(const std::string& title, const Book& new_book) override
	{
		/*
		This function modifies the book with the title *title*
		*/
		const int probability_action = pickNumber();
		if (probability_action < this->probability)
		{
			bool found{ false };
			for (auto& book : this->book_list)
				if (&book != nullptr && book.second.getTitle() == title)
				{
					book.second = new_book;
					found = true;
				}
			std::string message_error;
			if (!found)
				throw RepoException("inexisting book!\n");
		}
		else
		{
			std::string error_message{ "probability!\n" };
			throw error_message;
		}
	}

	std::vector<Book> repoGetAllBooks() const override
	{
		/*
		This function returns a vector with all the books
		*/
		const int probability_action = pickNumber();
		if (probability_action < this->probability)
		{
			std::vector<Book> all_books;
			for (const auto& book : this->book_list)
			{
				if (&book != nullptr)
				{
					all_books.push_back(book.second);
				}
			}
			return all_books;
		}
		else
		{
			std::string error_message{ "probability!\n" };
			throw error_message;
		}
	}

	Book repoFindBook(const std::string& title) const override
	{
		/*
		This function searches a book with the title *title* and returns it
		*/
		const int probability_action = pickNumber();
		if (probability_action < this->probability)
		{
			auto find_book = this->book_list.find(title);
			std::string message_error{};
			if (find_book == this->book_list.end())
				throw RepoException("book not found!\n");
			std::pair<std::string, Book> book_found = *find_book;
			return book_found.second;
		}
		else
		{
			std::string error_message{ "probability!\n" };
			throw error_message;
		}
	}

	void repoDeleteAllBooks() override
	{
		/*
		This function deletes all books from book list
		*/
		const int probability_action = pickNumber();
		if (probability_action < this->probability)
		{
			this->book_list.clear();
		}
		else
		{
			std::string error_message{ "probability!\n" };
			throw error_message;
		}
	}
	virtual ~NewRepo() = default;
};