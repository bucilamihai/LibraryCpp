#include "repo_books.h"

class FakeRepo : public Repo
{
public:
	int case_test;
	std::vector<Book> repoGetAllBooks() override
	{
		std::vector<Book> sample_book;
		if (case_test == 1)
		{
			sample_book.clear(); // empty list
		}
		if (case_test == 2)
		{
			sample_book.push_back({ "a", "b", "c", 5 });
			sample_book.push_back({ "d", "e", "f", 6 });
			sample_book.push_back({ "x", "y", "z", 7 });
		}
		if (case_test == 3)
		{
			sample_book.push_back({ "test", "b", "c", 5 });
			sample_book.push_back({ "d", "e", "f", 6 });
			sample_book.push_back({ "test", "y", "z", 7 });
		}
		return sample_book;
	}
	virtual ~FakeRepo() = default;
};