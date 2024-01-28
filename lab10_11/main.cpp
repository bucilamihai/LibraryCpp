#include <QApplication>

#include "repo_books.h"
#include "validator_book.h"
#include "service_books.h"
#include "repo_rental.h"
#include "service_rental.h"
#include "gui.h"
#include "tests.h"


int runApp(int argc, char** argv)
{
	QApplication app(argc, argv);

	Repo repo_books{};
	ValidatorBook validator_book{};
	Service service_books{ repo_books, validator_book };

	RepoRental repo_rentals{};
	ServiceRental service_rentals{ repo_rentals };

	GUI main_app{ service_books, service_rentals };

	return app.exec();
}

void runTests()
{
	Tests tests{};
	tests.runAllTests();
}

int main(int argc, char** argv)
{
	runApp(argc, argv);
	//runTests();
	return 0;
}
