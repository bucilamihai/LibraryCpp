#include "service_rental.h"

#include <algorithm>
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock
#include <fstream>
#include <iostream>

void ServiceRental::addBookToCart(const Book& book_found)
{
	/*
	This function adds a book to cart
	*/
	this->repo_rental.addBookToCart(book_found);
	this->notify(); 
	// we call this function in order to make the change in all cart-related windows that are opened
}

void ServiceRental::deleteAllCart()
{
	/*
	This function deletes all books from cart
	*/
	this->repo_rental.deleteAllCart();
	this->notify();
}

void ServiceRental::generateCart(std::vector<Book>& book_list, size_t number_of_books)
{
	/*
	This function generates a cart
	*/
	while (number_of_books)
	{
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(book_list.begin(), book_list.end(), std::default_random_engine((unsigned int)seed));
		for (auto& i : book_list)
		{
			if (&i != nullptr && &this->repo_rental != nullptr)
			{
				this->repo_rental.addBookToCart(i);
				number_of_books--;
				if (number_of_books == 0)
					break;
			}
		}
	}
	this->notify();
}

void ServiceRental::exportCart(std::string& filename)
{
	/*
	This function creates a HTML file and exports the cart to the file
	*/
	filename += ".html";
	std::ofstream HTML_export(filename);
	std::vector<Book> cart = this->getAllCart();
	HTML_export << "<!DOCTYPE html><html><head></head><body>\n";
	for (const auto& i : cart)
	{
		if (&i != nullptr)
		{
			HTML_export << "<p><span>";
			HTML_export << i.getTitle() << " </span><span>";
			HTML_export << i.getAuthor() << " </span><span>";
			HTML_export << i.getGenre() << " </span><span>";
			HTML_export << i.getYear() << " </span><span></p>\n";
		}
	}
	HTML_export << "</body></html>";
	HTML_export.close();
}

std::vector<Book> ServiceRental::getAllCart()
{
	/*
	This function returns a list with all rented books
	*/
	return this->repo_rental.getAllCart();
}