#pragma once

#include "repo_rental.h"
#include "observer.h"

#include <string>

class ServiceRental: public Observable
{
private:
	RepoRental& repo_rental;

public:
	ServiceRental() = default;
	ServiceRental(RepoRental& repo_rental) noexcept : repo_rental{ repo_rental } {} 
	void addBookToCart(const Book& book_found);
	void deleteAllCart();
	void generateCart(std::vector<Book>& book_list, size_t number_of_books);
	void exportCart(std::string& filename);
	std::vector<Book> getAllCart();
};