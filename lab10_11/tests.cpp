#include <iostream>
#include <cassert>
#include <fstream>

#include "book.h"
#include "validator_book.h"
#include "service_books.h"
#include "repo_books.h"
#include "service_rental.h"
#include "repo_rental.h"
#include "fake_repo_lab11.h"
#include "tests.h"

void Tests::FilterByTitle_EmptyList() const
{
	ValidatorBook validator_book;
	FakeRepo fake_repo;
	fake_repo.case_test = 1;
	Service service_books{ fake_repo, validator_book };
	auto filter_list = service_books.serviceFilterByTitle("test");
	assert(filter_list.size() == 0);
}

void Tests::FilterByTitle_EmptyFilteredList() const
{
	ValidatorBook validator_book;
	FakeRepo fake_repo;
	fake_repo.case_test = 2;
	Service service_books{ fake_repo, validator_book };
	auto filter_list = service_books.serviceFilterByTitle("test");
	assert(filter_list.size() == 0);
}

void Tests::FilterByTitle_NormalFilteredList() const
{
	ValidatorBook validator_book;
	FakeRepo fake_repo;
	fake_repo.case_test = 3;
	Service service_books{ fake_repo, validator_book };
	auto filter_list = service_books.serviceFilterByTitle("test");
	assert(filter_list.size() == 2);
}

void Tests::runFakeRepoTest() const
{
	Tests::FilterByTitle_EmptyList();
	Tests::FilterByTitle_EmptyFilteredList();
	Tests::FilterByTitle_NormalFilteredList();
}

void Tests::runDomainGettersTest() const
{
	/*
	This function runs tests for domain getters
	*/
	Book test_book{ "Enigma Otiliei", "G.Calinescu", "roman", 1930 };
	assert(test_book.getTitle() == "Enigma Otiliei");
	assert(test_book.getAuthor() == "G.Calinescu");
	assert(test_book.getGenre() == "roman");
	assert(test_book.getYear() == 1930);
}

void Tests::runDomainSettersTest() const
{
	/*
	This function runs tests for domain setters
	*/
	Book test_book{};
	test_book.setTitle("Moara cu noroc");
	test_book.setAuthor("Ioan Slavici");
	test_book.setGenre("nuvela");
	test_book.setYear(1870);
	assert(test_book.getTitle() == "Moara cu noroc");
	assert(test_book.getAuthor() == "Ioan Slavici");
	assert(test_book.getGenre() == "nuvela");
	assert(test_book.getYear() == 1870);
}

void Tests::runRepoAddTest() const
{
	Book book1{ "Enigma Otiliei", "G.Calinescu", "roman", 1930 };
	Book book2{ "Moara cu noroc", "Ioan Slavici", "nuvela", 1870 };
	Book book3{ "O scrisoare pierduta", "I.L. Caragiale", "comedie", 1880 };
	Repo repo_books;
	repo_books.repoAddBook(book1);
	repo_books.repoAddBook(book2);
	repo_books.repoAddBook(book3);
	std::vector<Book> all_books = repo_books.repoGetAllBooks();
	assert(all_books.size() == 3);
	assert(book1 == all_books.at(0));
	assert(book2 == all_books.at(1));
	assert(book3 == all_books.at(2));
	try
	{
		repo_books.repoAddBook(book3);
	}
	catch (RepoException& repo_exception)
	{
		assert(repo_exception.getMessageError() == "existing book!\n");
	}
}

void Tests::runRepoDeleteTest() const
{
	Book book1{ "Enigma Otiliei", "G.Calinescu", "roman", 1930 };
	Book book2{ "Moara cu noroc", "Ioan Slavici", "nuvela", 1870 };
	Book book3{ "O scrisoare pierduta", "I.L. Caragiale", "comedie", 1880 };
	Repo repo_books;
	repo_books.repoAddBook(book1);
	repo_books.repoAddBook(book2);
	repo_books.repoAddBook(book3);
	assert(repo_books.repoGetAllBooks().size() == 3);
	repo_books.repoDeleteBook("Moara cu noroc");
	std::vector<Book> all_books = repo_books.repoGetAllBooks();
	assert(repo_books.repoGetAllBooks().size() == 2);
	assert(all_books.at(1) == book3); // all books from right move 1 position to left
	try
	{
		repo_books.repoDeleteBook("Harap-Alb");
	}
	catch (RepoException& repo_exception)
	{
		assert(repo_exception.getMessageError() == "inexisting book!\n");
	}
}

void Tests::runRepoModifyTest() const
{
	Book book1{ "Enigma Otiliei", "G.Calinescu", "roman", 1930 };
	Book book2{ "Moara cu noroc", "Ioan Slavici", "nuvela", 1870 };
	Book book3{ "O scrisoare pierduta", "I.L. Caragiale", "comedie", 1880 };
	Repo repo_books;
	repo_books.repoAddBook(book1);
	repo_books.repoAddBook(book2);
	repo_books.repoAddBook(book3);
	Book new_book{ "Tata bogat tata sarac", "Kiyosaki", "finance", 1995};
	repo_books.repoModifyBook("O scrisoare pierduta", new_book);
	std::vector<Book> all_books = repo_books.repoGetAllBooks();
	assert(all_books.at(2) == new_book);
	try
	{
		repo_books.repoModifyBook("Harap-Alb", new_book);
	}
	catch (RepoException& repo_exception)
	{
		assert(repo_exception.getMessageError() == "inexisting book!\n");
	}
}

void Tests::runRepoFindTest() const
{
	Book book1{ "Enigma Otiliei", "G.Calinescu", "roman", 1930 };
	Book book2{ "Moara cu noroc", "Ioan Slavici", "nuvela", 1870 };
	Repo repo_books;
	repo_books.repoAddBook(book1);
	repo_books.repoAddBook(book2);
	Book book1_found = repo_books.repoFindBook("Enigma Otiliei");
	assert(book1_found == book1);
	try
	{
		repo_books.repoFindBook("O scrisoare pierduta");
	}
	catch (RepoException& repo_exception)
	{
		assert(repo_exception.getMessageError() == "book not found!\n");
	}
}

void Tests::runRepoDeleteAllTest() const
{
	Book book1{ "Enigma Otiliei", "G.Calinescu", "roman", 1930 };
	Book book2{ "Moara cu noroc", "Ioan Slavici", "nuvela", 1870 };
	Repo repo_books;
	repo_books.repoAddBook(book1);
	repo_books.repoAddBook(book2);
	assert(repo_books.repoGetAllBooks().size() == 2);
	repo_books.repoDeleteAllBooks();
	assert(repo_books.repoGetAllBooks().size() == 0);
}

void Tests::runServiceAddTest() const
{
	Repo repo_books{};
	ValidatorBook validator_book{};
	Service service_books{repo_books, validator_book};
	service_books.serviceAddBook("Enigma Otiliei", "G.Calinescu", "roman", 1930);
	service_books.serviceAddBook("Moara cu noroc", "Ioan Slavici", "nuvela", 1870);
	service_books.serviceAddBook("O scrisoare pierduta", "I.L. Caragiale", "comedie", 1880);
	std::vector<Book> all_books = service_books.serviceGetBookList();
	assert(all_books.size() == 3);
	try
	{
		service_books.serviceAddBook("", "", "", -1);
	}
	catch (ValidatorException& validator_exception)
	{
		assert(validator_exception.getMessageError() == "invalid title!\ninvalid author!\ninvalid genre!\ninvalid year!\n");
	}
}

void Tests::runServiceDeleteTest() const
{
	Repo repo_books{};
	ValidatorBook validator_book{}; 
	Service service_books{ repo_books, validator_book };
	service_books.serviceAddBook("Enigma Otiliei", "G.Calinescu", "roman", 1930);
	service_books.serviceAddBook("Moara cu noroc", "Ioan Slavici", "nuvela", 1870);
	service_books.serviceAddBook("O scrisoare pierduta", "I.L. Caragiale", "comedie", 1880);
	std::vector<Book> all_books = service_books.serviceGetBookList();
	assert(all_books.size() == 3);
	service_books.serviceDeleteBook("Enigma Otiliei");
	all_books = service_books.serviceGetBookList();
	assert(all_books.size() == 2);
	try
	{
		service_books.serviceDeleteBook("");
	}
	catch (ValidatorException& validator_exception)
	{
		assert(validator_exception.getMessageError() == "invalid title!\n");
	}
}

void Tests::runServiceModifyTest() const
{
	Repo repo_books{};
	ValidatorBook validator_book{};
	Service service_books{ repo_books, validator_book };
	service_books.serviceAddBook("Enigma Otiliei", "G.Calinescu", "roman", 1930);
	service_books.serviceAddBook("Moara cu noroc", "Ioan Slavici", "nuvela", 1870);
	service_books.serviceAddBook("O scrisoare pierduta", "I.L. Caragiale", "comedie", 1880);
	service_books.serviceModifyBook("Moara cu noroc", "Tata bogat tata sarac", "Kiyosaki", "finance", 1995);
	Book new_book{ "Tata bogat tata sarac", "Kiyosaki", "finance", 1995 };
	std::vector<Book> all_books = service_books.serviceGetBookList();
	assert(all_books.at(1) == new_book);
	try
	{
		service_books.serviceModifyBook("", "", "", "", -1);
	}
	catch (ValidatorException& validator_exception)
	{
		assert(validator_exception.getMessageError() == "invalid title!\n"); // current title
	}
	try
	{
		service_books.serviceModifyBook("Enigma Otiliei", "", "", "", -1);
	}
	catch (ValidatorException& validator_exception)
	{
		assert(validator_exception.getMessageError() == "invalid title!\ninvalid author!\ninvalid genre!\ninvalid year!\n"); // new book
	}
}

void Tests::runServiceFindTest() const
{
	Book book1{ "Enigma Otiliei", "G.Calinescu", "roman", 1930 };
	Book book2{ "Moara cu noroc", "Ioan Slavici", "nuvela", 1870 };
	Repo repo_books{};
	ValidatorBook validator_book{};
	Service service_books{ repo_books, validator_book };
	service_books.serviceAddBook("Enigma Otiliei", "G.Calinescu", "roman", 1930);
	service_books.serviceAddBook("Moara cu noroc", "Ioan Slavici", "nuvela", 1870);
	Book book1_found = service_books.serviceFindBook("Enigma Otiliei");
	assert(book1_found == book1);
	try
	{
		service_books.serviceFindBook("");
	}
	catch (ValidatorException& validator_exception)
	{
		assert(validator_exception.getMessageError() == "invalid title!\n");
	}
}

void Tests::runServiceFilterByTitleTest() const
{
	Book book1{ "Ultima noapte de dragoste, intaia noapte de razboi", "Camil Petrescu", "roman", 1925 };
	Book book2{ "O noapte furtunoasa", "I.L. Caragiale", "comedie", 1880 };
	Repo repo_books{};
	ValidatorBook validator_book{};
	Service service_books{ repo_books, validator_book };
	service_books.serviceAddBook("Ultima noapte de dragoste, intaia noapte de razboi", "Camil Petrescu", "roman", 1925);
	service_books.serviceAddBook("Moara cu noroc", "Ioan Slavici", "nuvela", 1870);
	service_books.serviceAddBook("O noapte furtunoasa", "I.L. Caragiale", "comedie", 1880);
	std::vector<Book> filtered_books = service_books.serviceFilterByTitle("noapte");
	assert(filtered_books.size() == 2);
	assert(filtered_books.at(0) == book1);
	assert(filtered_books.at(1) == book2);
	try
	{
		service_books.serviceFilterByTitle("");
	}
	catch(ValidatorException& validator_exception)
	{
		assert(validator_exception.getMessageError() == "invalid title!\n");
	}
}

void Tests::runServiceFilterByYearTest() const
{
	Book book1{ "Moara cu noroc", "Ioan Slavici", "nuvela", 1870 };
	Book book2{ "O noapte furtunoasa", "I.L. Caragiale", "comedie", 1880 };
	Repo repo_books{};
	ValidatorBook validator_book{};
	Service service_books{ repo_books, validator_book };
	service_books.serviceAddBook("Ultima noapte de dragoste, intaia noapte de razboi", "Camil Petrescu", "roman", 1925);
	service_books.serviceAddBook("Moara cu noroc", "Ioan Slavici", "nuvela", 1870);
	service_books.serviceAddBook("O noapte furtunoasa", "I.L. Caragiale", "comedie", 1880);
	std::vector<Book> filtered_books = service_books.serviceFilterByYear(1850, 1900);
	assert(filtered_books.size() == 2);
	assert(filtered_books.at(0) == book1);
	assert(filtered_books.at(1) == book2);
	try
	{
		service_books.serviceFilterByYear(-4, 1900);
	}
	catch (ValidatorException& validator_exception)
	{
		assert(validator_exception.getMessageError() == "invalid year!\n");
	}
}

void Tests::runServiceSortByTitle() const
{
	Book book1{ "Moara cu noroc", "Ioan Slavici", "nuvela", 1870 };
	Book book2{ "Enigma Otiliei", "G.Calinescu", "roman", 1930 };
	Book book3{ "O scrisoare pierduta", "I.L. Caragiale", "comedie", 1880 };
	Book book4{ "Harap-Alb", "Ion Creanga", "basm", 1875 };
	Repo repo_books{};
	ValidatorBook validator_book{};
	Service service_books{ repo_books, validator_book };
	service_books.serviceAddBook("Moara cu noroc", "Ioan Slavici", "nuvela", 1870);
	service_books.serviceAddBook("Enigma Otiliei", "G.Calinescu", "roman", 1930);
	service_books.serviceAddBook("O scrisoare pierduta", "I.L. Caragiale", "comedie", 1880);
	service_books.serviceAddBook("Harap-Alb", "Ion Creanga", "basm", 1875);
	std::vector<Book> sorted_books = service_books.serviceSortByTitle();
	assert(sorted_books.size() == 4);
	assert(sorted_books.at(0) == book2);
	assert(sorted_books.at(1) == book4);
	assert(sorted_books.at(2) == book1);
	assert(sorted_books.at(3) == book3);
}

void Tests::runServiceSortByAuthor() const
{
	Book book1{ "Moara cu noroc", "Ioan Slavici", "nuvela", 1870 };
	Book book2{ "Enigma Otiliei", "G.Calinescu", "roman", 1930 };
	Book book3{ "O scrisoare pierduta", "Caragiale", "comedie", 1880 };
	Book book4{ "Fat-frumos", "Mihai Eminescu", "basm", 1875 };
	Repo repo_books{};
	ValidatorBook validator_book{};
	Service service_books{ repo_books, validator_book };
	service_books.serviceAddBook("Moara cu noroc", "Ioan Slavici", "nuvela", 1870);
	service_books.serviceAddBook("Enigma Otiliei", "G.Calinescu", "roman", 1930);
	service_books.serviceAddBook("O scrisoare pierduta", "Caragiale", "comedie", 1880);
	service_books.serviceAddBook("Fat-frumos", "Mihai Eminescu", "basm", 1875);
	std::vector<Book> sorted_books = service_books.serviceSortByAuthor();
	assert(sorted_books.size() == 4);
	assert(sorted_books.at(0) == book3);
	assert(sorted_books.at(1) == book2);
	assert(sorted_books.at(2) == book1);
	assert(sorted_books.at(3) == book4);
}

void Tests::runServiceSortByYearAndGenre() const
{
	Book book1{ "Moara cu noroc", "Ioan Slavici", "nuvela", 1870 };
	Book book2{ "Enigma Otiliei", "G.Calinescu", "roman", 1930 };
	Book book3{ "O scrisoare pierduta", "Caragiale", "comedie", 1880 };
	Book book4{ "Fat-frumos", "Mihai Eminescu", "basm", 1880 };
	Repo repo_books{};
	ValidatorBook validator_book{};
	Service service_books{ repo_books, validator_book };
	service_books.serviceAddBook("Moara cu noroc", "Ioan Slavici", "nuvela", 1870);
	service_books.serviceAddBook("Enigma Otiliei", "G.Calinescu", "roman", 1930);
	service_books.serviceAddBook("O scrisoare pierduta", "Caragiale", "comedie", 1880);
	service_books.serviceAddBook("Fat-frumos", "Mihai Eminescu", "basm", 1880);
	std::vector<Book> sorted_books = service_books.serviceSortByYearAndGenre();
	assert(sorted_books.size() == 4);
	assert(sorted_books.at(0) == book1);
	assert(sorted_books.at(1) == book4);
	assert(sorted_books.at(2) == book3);
	assert(sorted_books.at(3) == book2);
}

void Tests::runTitleValidator() const
{
	ValidatorBook validator{};
	try
	{
		validator.validateTitle("");
	}
	catch (ValidatorException& validator_exception)
	{
		assert(validator_exception.getMessageError() == "invalid title!\n");
	}
}

void Tests::runAuthorValidator() const
{
	ValidatorBook validator{};
	try
	{
		validator.validateAuthor("");
	}
	catch (ValidatorException& validator_exception)
	{
		assert(validator_exception.getMessageError() == "invalid author!\n");
	}
}

void Tests::runGenreValidator() const
{
	ValidatorBook validator{};
	try
	{
		validator.validateGenre("");
	}
	catch (ValidatorException& validator_exception)
	{
		assert(validator_exception.getMessageError() == "invalid genre!\n");
	}
}

void Tests::runYearValidator() const
{
	ValidatorBook validator{};
	try
	{
		validator.validateYear(-1);
	}
	catch (ValidatorException& validator_exception)
	{
		assert(validator_exception.getMessageError() == "invalid year!\n");
	}
	try
	{
		validator.validateYear(0);
	}
	catch (ValidatorException& validator_exception)
	{
		assert(validator_exception.getMessageError() == "invalid year!\n");
	}
}

void Tests::runBookValidator() const
{
	ValidatorBook validator{};
	try
	{
		validator.validateBook({ "", "", "", -1 });
	}
	catch (ValidatorException& validator_exception)
	{
		assert(validator_exception.getMessageError() == "invalid title!\ninvalid author!\ninvalid genre!\ninvalid year!\n");
	}
}

void Tests::runRepoRentalAddTest() const
{
	Book book1{ "Enigma Otiliei", "G.Calinescu", "roman", 1930 };
	Book book2{ "Moara cu noroc", "Ioan Slavici", "nuvela", 1870 };
	Book book3{ "O scrisoare pierduta", "I.L. Caragiale", "comedie", 1880 };
	Repo repo_books;
	repo_books.repoAddBook(book1);
	repo_books.repoAddBook(book2);
	repo_books.repoAddBook(book3);
	RepoRental repo_rental;
	repo_rental.addBookToCart(book2);
	std::vector<Book> rented_books = repo_rental.getAllCart();
	assert(rented_books.size() == 1);
	assert(rented_books.at(0) == book2);
}

void Tests::runServiceRentalAddTest() const
{
	Book book1{ "Moara cu noroc", "Ioan Slavici", "nuvela", 1870 };
	Book book2{ "Enigma Otiliei", "G.Calinescu", "roman", 1930 };
	Book book3{ "O scrisoare pierduta", "Caragiale", "comedie", 1880 };
	Book book4{ "Fat-frumos", "Mihai Eminescu", "basm", 1880 };
	Repo repo_books{};
	ValidatorBook validator_book{};
	Service service_books{ repo_books, validator_book };
	service_books.serviceAddBook("Moara cu noroc", "Ioan Slavici", "nuvela", 1870);
	service_books.serviceAddBook("Enigma Otiliei", "G.Calinescu", "roman", 1930);
	service_books.serviceAddBook("O scrisoare pierduta", "Caragiale", "comedie", 1880);
	service_books.serviceAddBook("Fat-frumos", "Mihai Eminescu", "basm", 1880);
	std::vector<Book> all_books = service_books.serviceGetBookList();
	assert(all_books.size() == 4);
	RepoRental repo_rental = RepoRental();
	ServiceRental service_rental{ repo_rental };
	service_rental.addBookToCart(service_books.serviceFindBook("Moara cu noroc"));
	std::vector<Book> rented_books = service_rental.getAllCart();
	assert(rented_books.size() == 1);
	assert(rented_books.at(0) == book1);
	try
	{
		service_rental.addBookToCart(service_books.serviceFindBook("Harap-Alb"));
	}
	catch (RepoException& repo_exception)
	{
		assert(repo_exception.getMessageError() == "book not found!\n");
	}
}

void Tests::runRepoRentalDeleteTest() const
{
	Book book1{ "Enigma Otiliei", "G.Calinescu", "roman", 1930 };
	Book book2{ "Moara cu noroc", "Ioan Slavici", "nuvela", 1870 };
	Book book3{ "O scrisoare pierduta", "I.L. Caragiale", "comedie", 1880 };
	Repo repo_books;
	repo_books.repoAddBook(book1);
	repo_books.repoAddBook(book2);
	repo_books.repoAddBook(book3);
	RepoRental repo_rental;
	repo_rental.addBookToCart(book1);
	repo_rental.addBookToCart(book2);
	repo_rental.addBookToCart(book3);
	std::vector<Book> rented_books = repo_rental.getAllCart();
	assert(rented_books.size() == 3);
	repo_rental.deleteAllCart();
	rented_books = repo_rental.getAllCart();
	assert(rented_books.size() == 0);
}

void Tests::runServiceRentalDeleteTest() const
{
	Repo repo_books{};
	ValidatorBook validator_book{};
	Service service_books{ repo_books, validator_book };
	service_books.serviceAddBook("Moara cu noroc", "Ioan Slavici", "nuvela", 1870);
	service_books.serviceAddBook("Enigma Otiliei", "G.Calinescu", "roman", 1930);
	service_books.serviceAddBook("O scrisoare pierduta", "Caragiale", "comedie", 1880);
	service_books.serviceAddBook("Fat-frumos", "Mihai Eminescu", "basm", 1880);
	RepoRental repo_rental = RepoRental();
	ServiceRental service_rental{ repo_rental };
	service_rental.addBookToCart(service_books.serviceFindBook("Moara cu noroc"));
	service_rental.addBookToCart(service_books.serviceFindBook("O scrisoare pierduta"));
	std::vector<Book> rented_books = service_rental.getAllCart();
	assert(rented_books.size() == 2);
	service_rental.deleteAllCart();
	rented_books = service_rental.getAllCart();
	assert(rented_books.size() == 0);
}

void Tests::runServiceRentalGenerateTest() const
{
	Repo repo_books{};
	ValidatorBook validator_book{};
	Service service_books{ repo_books, validator_book };
	service_books.serviceAddBook("Moara cu noroc", "Ioan Slavici", "nuvela", 1870);
	service_books.serviceAddBook("Enigma Otiliei", "G.Calinescu", "roman", 1930);
	service_books.serviceAddBook("O scrisoare pierduta", "Caragiale", "comedie", 1880);
	service_books.serviceAddBook("Fat-frumos", "Mihai Eminescu", "basm", 1880);
	RepoRental repo_rental = RepoRental();
	ServiceRental service_rental{ repo_rental };
	std::vector<Book> book_list = service_books.serviceGetBookList();
	service_rental.generateCart(book_list, 10); // test generate more books that book list size
	assert(service_rental.getAllCart().size() == 10);
	service_rental.generateCart(book_list, 2); // test multiple generate
	assert(service_rental.getAllCart().size() == 12);
}

void Tests::runServiceRentalExportTest() const
{
	Repo repo_books{};
	ValidatorBook validator_book{};
	Service service_books{ repo_books, validator_book };
	service_books.serviceAddBook("Moara cu noroc", "Ioan Slavici", "nuvela", 1870);
	service_books.serviceAddBook("Enigma Otiliei", "G.Calinescu", "roman", 1930);
	service_books.serviceAddBook("O scrisoare pierduta", "Caragiale", "comedie", 1880);
	service_books.serviceAddBook("Fat-frumos", "Mihai Eminescu", "basm", 1880);
	RepoRental repo_rental{};
	ServiceRental service_rental{repo_rental};
	std::vector<Book> book_list = service_books.serviceGetBookList();
	service_rental.generateCart(book_list, 20);
	std::string filename = "test_export";
	service_rental.exportCart(filename);
	std::ifstream HTML_export(filename);
	int number_of_lines = 0;
	std::string line;
	while (std::getline(HTML_export, line))
	{
		number_of_lines++;
	}
	assert(number_of_lines == 22); // first and last line contains HTML tags
}

void Tests::runUndoTest() const
{
	Repo repo_books{};
	ValidatorBook validator_book{};
	Service service_books{ repo_books, validator_book };
	service_books.serviceAddBook("Moara cu noroc", "Ioan Slavici", "nuvela", 1870);
	service_books.serviceAddBook("Enigma Otiliei", "G.Calinescu", "roman", 1930);
	service_books.serviceAddBook("O scrisoare pierduta", "Caragiale", "comedie", 1880);
	service_books.serviceAddBook("Fat-frumos", "Mihai Eminescu", "basm", 1880);
	assert(service_books.serviceGetBookList().size() == 4);
	service_books.undo(); // test undoAdd
	assert(service_books.serviceGetBookList().size() == 3);
	try
	{
		service_books.serviceFindBook("Fat-frumos");
	}
	catch (RepoException& repo_exception)
	{
		assert(repo_exception.getMessageError() == "book not found!\n");
	}
	service_books.serviceDeleteBook("Enigma Otiliei");
	assert(service_books.serviceGetBookList().size() == 2);
	service_books.undo(); // test undoDelete
	assert(service_books.serviceGetBookList().size() == 3); // Moara, OSP, Enigma
	service_books.serviceModifyBook("O scrisoare pierduta", "a", "b", "c", 1);
	try
	{
		service_books.serviceFindBook("O scrisoare pierduta");
	}
	catch (RepoException& repo_exception)
	{
		assert(repo_exception.getMessageError() == "book not found!\n");
	}
	service_books.undo(); // test undoModify
	assert(service_books.serviceGetBookList().at(1).getAuthor() == "Caragiale");
	service_books.undo();
	service_books.undo();
	service_books.undo();
	assert(service_books.serviceGetBookList().size() == 0);
	try
	{
		service_books.undo();
	}
	catch (const std::string& other_exception)
	{
		assert(other_exception == "empty undo list!\n");
	}
}

void Tests::runDomainTest() const
{
	/*
	This function runs tests for domain
	*/
	Tests::runDomainGettersTest();
	Tests::runDomainSettersTest();
}

void Tests::runRepoTest() const
{
	Tests::runRepoAddTest();
	Tests::runRepoDeleteTest();
	Tests::runRepoModifyTest();
	Tests::runRepoFindTest();
	Tests::runRepoDeleteAllTest();
}

void Tests::runServiceTest() const
{
	Tests::runServiceAddTest();
	Tests::runServiceDeleteTest();
	Tests::runServiceModifyTest();
	Tests::runServiceFindTest();
	Tests::runServiceFilterByTitleTest();
	Tests::runServiceFilterByYearTest();
	Tests::runServiceSortByTitle();
	Tests::runServiceSortByAuthor();
	Tests::runServiceSortByYearAndGenre();
}

void Tests::runValidatorTest() const
{
	Tests::runTitleValidator();
	Tests::runAuthorValidator();
	Tests::runGenreValidator();
	Tests::runYearValidator();
	Tests::runBookValidator();
}

void Tests::runRentalTest() const
{
	Tests::runRepoRentalAddTest();
	Tests::runServiceRentalAddTest();
	Tests::runRepoRentalDeleteTest();
	Tests::runServiceRentalDeleteTest();
	Tests::runServiceRentalGenerateTest();
	Tests::runServiceRentalExportTest();
}

void Tests::runAllTests() const
{
	/*
	This function runs all tests for the app
	*/
	Tests::runFakeRepoTest();
	Tests::runDomainTest();
	Tests::runRepoTest();
	Tests::runServiceTest();
	Tests::runValidatorTest();
	Tests::runRentalTest();
	Tests::runUndoTest();
}