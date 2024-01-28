#pragma once

#include "book.h"

#include <vector>

class RepoRental
{
private:
	std::vector<Book> rental_cart{};

public:
	RepoRental() = default;
	void addBookToCart(const Book& book);
	void deleteAllCart();
	std::vector<Book> getAllCart();
};