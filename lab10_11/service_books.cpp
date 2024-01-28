#include "service_books.h"
#include "book.h"


void Service::serviceAddBook(const std::string& title, const std::string& author, const std::string& genre, const int& year)
{
	/*
	This function adds a new car to the book list
	*/
	Book book_to_add{ title, author, genre, year };
	this->validator_book.validateBook(book_to_add);
	this->repo_books.repoAddBook(book_to_add);
	UndoAdd* undo_add = new UndoAdd(book_to_add, this->repo_books);
	this->undo_actions.push_back(undo_add);
}

void Service::serviceDeleteBook(const std::string& title)
{
	/*
	This function deletes from the book list the book with the title *title*
	*/
	this->validator_book.validateTitle(title);
	Book book_to_delete = this->repo_books.repoFindBook(title);
	this->repo_books.repoDeleteBook(title);
	UndoDelete* undo_delete = new UndoDelete(book_to_delete, this->repo_books);
	this->undo_actions.push_back(undo_delete);
}

void Service::serviceModifyBook(const std::string& title, const std::string& new_title, const std::string& new_author, const std::string& new_genre, const int& new_year)
{
	/*
	This function modifies the book with the title *title* 
	*/
	Book new_book{ new_title, new_author, new_genre, new_year };
	this->validator_book.validateTitle(title);
	this->validator_book.validateBook(new_book);
	Book old_book = this->repo_books.repoFindBook(title);
	this->repo_books.repoModifyBook(title, new_book);
	UndoModify* undo_modify = new UndoModify(old_book, new_book, this->repo_books);
	this->undo_actions.push_back(undo_modify);
}

std::vector<Book> Service::serviceGetBookList() const
{
	/*
	This function returns a vector with all the books
	*/
	return this->repo_books.repoGetAllBooks();
}

Book Service::serviceFindBook(const std::string& title)
{
	/*
	This function searches a book with the title *title* and returns it 
	*/
	this->validator_book.validateTitle(title);
	return this->repo_books.repoFindBook(title);
}

std::vector<Book> Service::serviceFilterByTitle(const std::string& title)
{
	/*
	This function filters the list of books by title and returns a list that contains
		the books whose title contains the string *title* 
	*/
	this->validator_book.validateTitle(title);
	std::vector<Book> all_books = this->repo_books.repoGetAllBooks();
	std::vector<Book> filtered_books;
	std::copy_if(all_books.begin(), all_books.end(), std::back_inserter(filtered_books), [title](const Book& book) {return book.getTitle().find(title) != std::string::npos; }); 
	return filtered_books;
}

std::vector<Book> Service::serviceFilterByYear(const int& lower_bound_year, const int& upper_bound_year)
{
	/*
	This function filters the list of books by year and returns a list that contains
		the books whose year is between lower bound and upper bound
	*/
	this->validator_book.validateYear(lower_bound_year);
	this->validator_book.validateYear(upper_bound_year);
	std::vector<Book> all_books = this->repo_books.repoGetAllBooks();
	std::vector<Book> filtered_books;
	std::copy_if(all_books.begin(), all_books.end(), std::back_inserter(filtered_books), [=](const Book& book) noexcept {return lower_bound_year <= book.getYear() && book.getYear() <= upper_bound_year; }); 
		// [=] - equal sign means we pass the parameters from outside the lambda function by value
	return filtered_books;
}

std::vector<Book> Service::serviceSortByTitle() const
{
	/*
	This function returns a list sorted by title (increasing)
	*/
	std::vector<Book> sorted_book = this->repo_books.repoGetAllBooks();
	std::sort(sorted_book.begin(), sorted_book.end(), [](const Book& book1, const Book& book2) {return book1.getTitle() <= book2.getTitle(); });
	return sorted_book;
}

std::vector<Book> Service::serviceSortByAuthor() const
{
	/*
	This function returns a list sorted by author (increasing)
	*/
	std::vector<Book> sorted_book = this->repo_books.repoGetAllBooks();
	std::sort(sorted_book.begin(), sorted_book.end(), [](const Book& book1, const Book& book2) {return book1.getAuthor() <= book2.getAuthor(); });
	return sorted_book;
}

std::vector<Book> Service::serviceSortByYearAndGenre() const
{
	/*
	This function returns a list sorted by year and genre (increasing by year, for equal year, increasing by genre)
	*/
	std::vector<Book> sorted_book = this->repo_books.repoGetAllBooks();
	std::sort(sorted_book.begin(), sorted_book.end(), [](const Book& book1, const Book& book2) {return book1.getYear() < book2.getYear() || (book1.getYear() == book2.getYear() && book1.getGenre() <= book2.getGenre()); });
	return sorted_book;
}

void Service::undo()
{
	if (this->undo_actions.empty())
	{
		std::string error_message{ "empty undo list!\n" };
		throw error_message;
	}
	UndoAction* action = this->undo_actions.back();
	if (action != nullptr)
	{
		action->doUndo();
		this->undo_actions.pop_back();
		delete action;
	}
}

std::vector<std::string> Service::getListOfGenres()
{
	std::vector<std::string> genres;
	std::vector<Book> books = this->repo_books.repoGetAllBooks();
	for (const auto& book : books)
	{
		auto found = std::find(genres.begin(), genres.end(), book.getGenre());
		if (found == genres.end()) // genre not found
			genres.push_back(book.getGenre());
	}
	return genres;
}