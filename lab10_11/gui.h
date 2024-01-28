#include <QWidget>
#include <QPushbutton>
#include <QLabel>
#include <QComboBox>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringListModel>
#include <QLineEdit>
#include <QMessageBox>
#include <QDialog>
#include <QInputDialog>
#include <QSpinBox>

#include "service_books.h"
#include "service_rental.h"
#include "cartGUI.h"
#include "my_list_model.h"

#define FILTER_BY_TITLE 0
#define FILTER_BY_YEAR 1

#define SORT_BY_TITLE 0
#define SORT_BY_AUTHOR 1
#define SORT_BY_YEAR_AND_GENRE 2


class GUI : public QWidget
{
private:
	Service& service_books;
	ServiceRental& service_rentals;

	QFont app_font{"Verdana", 12};
	
	MyListModel* content;

	QLabel* book_title_label;
	QLabel* book_author_label;
	QLabel* book_genre_label;
	QLabel* book_year_label;

	QLineEdit* book_title;
	QLineEdit* book_author;
	QLineEdit* book_genre;
	QSpinBox* book_year;

	QPushButton* add_book_button;
	QPushButton* delete_book_button;
	QPushButton* modify_book_button;
	
	QInputDialog* find_input_dialog;
	QPushButton* find_book;
	QInputDialog* filter_title_input_dialog;
	QInputDialog* filter_year_lower_input_dialog;
	QInputDialog* filter_year_upper_input_dialog;
	QComboBox* filter_books;
	QComboBox* sort_books;

	QPushButton* add_to_cart;
	QPushButton* clear_cart;
	QPushButton* generate_cart;
	QPushButton* crud_cart;
	QPushButton* read_only_cart;
	
	QPushButton* undo_button;

	//std::vector<QPushButton*> genre_buttons;

	void buildGUI();
	void connectSignalsSlots();
	void populateListWidget(MyListModel* list_widget, std::vector<Book> book_list);
	void filterByTitle();
	void filterByYear();

public:
	GUI(Service& service_books, ServiceRental& service_rentals) : service_books{ service_books }, service_rentals{ service_rentals } 
	{
		this->buildGUI();
		this->connectSignalsSlots();
		this->populateListWidget(this->content, this->service_books.serviceGetBookList());
	}
};