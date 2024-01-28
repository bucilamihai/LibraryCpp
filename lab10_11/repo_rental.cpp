#include "repo_rental.h"

void RepoRental::addBookToCart(const Book& book)
{
	/*
	This function adds a book to cart
	*/
	this->rental_cart.push_back(book);
}

void RepoRental::deleteAllCart()
{
	/*
	This function deletes all books from cart
	*/
	this->rental_cart.clear();
}

std::vector<Book> RepoRental::getAllCart()
{
	/*
	This function returns a list with all rented books
	*/
	std::vector<Book> all_rented_books;
	for (const auto& i : this->rental_cart)
		if (&i != nullptr)
			all_rented_books.push_back(i);
	return all_rented_books;
}