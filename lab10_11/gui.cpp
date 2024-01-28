#include "gui.h"


void GUI::buildGUI()
{
	/*
	This function builds all the elements of GUI - windows, widgets ...
	*/
	// Adding some books
	this->service_books.serviceAddBook("Moara cu noroc", "Ioan Slavici", "nuvela", 1870);
	this->service_books.serviceAddBook("Enigma Otiliei", "G.Calinescu", "roman", 1930);
	this->service_books.serviceAddBook("O scrisoare pierduta", "Caragiale", "comedie", 1880);
	this->service_books.serviceAddBook("Fat-frumos", "Mihai Eminescu", "basm", 1880);
	//this->service_books.serviceAddBook("Ultima noapte de dragoste, intaia noapte de razboi", "Camil Petrescu", "roman", 1925);
	this->service_books.serviceAddBook("Tata bogat tata sarac", "Kiyosaki", "finance", 1995);
	this->service_books.serviceAddBook("Harap-Alb", "Ion Creanga", "basm", 1870);
	//

	this->content = new MyListModel;
	QListView* list_view = new QListView;
	list_view->setModel(this->content);
	this->add_book_button = new QPushButton("Add book");
	this->delete_book_button = new QPushButton("Delete book");
	this->modify_book_button = new QPushButton("Modify book");
	this->book_title = new QLineEdit;
	this->book_author = new QLineEdit;
	this->book_genre = new QLineEdit;
	this->book_year = new QSpinBox;
	this->book_year->setMinimum(0);
	this->book_year->setMaximum(9999);
	this->book_year->setValue(2023);
	this->book_title_label = new QLabel;
	this->book_title_label->setText("Title: ");
	this->book_author_label = new QLabel;
	this->book_author_label->setText("Author: ");
	this->book_genre_label = new QLabel;
	this->book_genre_label->setText("Genre: ");
	this->book_year_label = new QLabel;
	this->book_year_label->setText("Year: ");
	this->content->setFont(this->app_font);

	QHBoxLayout* left_and_right = new QHBoxLayout;
	QVBoxLayout* left = new QVBoxLayout;
	QHBoxLayout* left_corner_crud_input = new QHBoxLayout;
	QVBoxLayout* label_input = new QVBoxLayout;
	QVBoxLayout* input = new QVBoxLayout;
	QVBoxLayout* crud_buttons = new QVBoxLayout;

	label_input->addWidget(this->book_title_label);
	label_input->addWidget(this->book_author_label);
	label_input->addWidget(this->book_genre_label);
	label_input->addWidget(this->book_year_label);
	input->addWidget(this->book_title);
	input->addWidget(this->book_author);
	input->addWidget(this->book_genre);
	input->addWidget(this->book_year);
	crud_buttons->addWidget(this->add_book_button);
	crud_buttons->addWidget(this->delete_book_button);
	crud_buttons->addWidget(this->modify_book_button);
	left_corner_crud_input->addLayout(label_input);
	left_corner_crud_input->addLayout(input);
	left_corner_crud_input->addStretch();
	left_corner_crud_input->addLayout(crud_buttons);
	left->addWidget(list_view);
	left->addStretch();
	left->addLayout(left_corner_crud_input);

	this->find_input_dialog = new QInputDialog;
	this->find_book = new QPushButton("Find book");
	this->filter_books = new QComboBox;
	this->filter_books->setPlaceholderText("Filter books by ...");
	this->filter_books->addItem("Filter by title");
	this->filter_books->addItem("Filter by year");
	this->filter_title_input_dialog = new QInputDialog;
	this->filter_year_lower_input_dialog = new QInputDialog;
	this->filter_year_upper_input_dialog = new QInputDialog;
	this->sort_books = new QComboBox;
	this->sort_books->setPlaceholderText("Sort books by ...");
	this->sort_books->addItem("Sort by title");
	this->sort_books->addItem("Sort by author");
	this->sort_books->addItem("Sort by year + genre");
	this->add_to_cart = new QPushButton("Add book to cart");
	this->clear_cart = new QPushButton("Clear cart");
	this->generate_cart = new QPushButton("Generate cart");
	this->crud_cart = new QPushButton("Open CRUD cart window");
	this->read_only_cart = new QPushButton("Open Read-Only cart window");
	this->undo_button = new QPushButton("Undo");
	QVBoxLayout* right = new QVBoxLayout;
	right->addWidget(this->find_book);
	right->addWidget(this->filter_books);
	right->addWidget(this->sort_books);
	right->addStretch();
	right->addWidget(this->add_to_cart);
	right->addWidget(this->clear_cart);
	right->addWidget(this->generate_cart);
	right->addWidget(this->crud_cart);
	right->addWidget(this->read_only_cart);
	right->addStretch();
	right->addWidget(this->undo_button);
	right->addStretch();
	/*for (const auto& genre : this->service_books.getListOfGenres())
	{
		QPushButton* genre_button = new QPushButton(QString::fromStdString(genre));
		right->addWidget(genre_button);
		this->genre_buttons.push_back(genre_button);
	}*/
	left_and_right->addLayout(left);
	left_and_right->addLayout(right);

	this->setLayout(left_and_right);
	this->setWindowTitle("Book App");
	this->resize(700, 400);
	this->show();
}

void testConnect(std::string text)
{
	QMessageBox test;
	test.setText(QString::fromStdString(text));
	test.exec();
}

void GUI::connectSignalsSlots()
{
	QObject::connect(this->add_book_button, &QPushButton::clicked, 
		[this]()
		{
			try
			{
				auto title = this->book_title->text().toStdString();
				auto author = this->book_author->text().toStdString();
				auto genre = this->book_genre->text().toStdString();
				auto year = this->book_year->value();
				this->service_books.serviceAddBook(title, author, genre, year);
				this->populateListWidget(this->content, this->service_books.serviceGetBookList());
				this->book_title->clear();
				this->book_author->clear();
				this->book_genre->clear();
			}
			catch (ValidatorException&)
			{
				QMessageBox error;
				error.setText("Please enter valid data!");
				error.setIcon(QMessageBox::Warning);
				error.exec();
			}
			catch (RepoException& repo_exception)
			{
				QMessageBox error;
				if (repo_exception.getMessageError() == "existing book!\n")
				{
					error.setText("The book you want to add is already in the book list!");
					error.setIcon(QMessageBox::Information);
				}
				error.exec();
			}
		});
	QObject::connect(this->delete_book_button, &QPushButton::clicked,
		[this]()
		{
			auto selected_items = this->content->selectedItems();
			if (selected_items.size() == 1)
			{
				auto selected_book_string = selected_items.at(0).data().toString();
				//auto selected_book_string = selected_items.at(0)->text().toStdString();
				std::string title = "";
				int i = 0;
				while (selected_book_string.at(i) != '~')
				{
					title.push_back(selected_book_string.at(i).toLatin1());
					i++;
				}
				title.pop_back(); // space between end of title and ~
				this->service_books.serviceDeleteBook(title);
				this->populateListWidget(this->content, this->service_books.serviceGetBookList());
			}
			else
			{
				QMessageBox error;
				error.setText("Please select a book from the list!");
				error.setIcon(QMessageBox::Warning);
				error.exec();
			}
		});
	QObject::connect(this->modify_book_button, &QPushButton::clicked,
		[this]()
		{
			auto selected_items = this->content->selectedItems();
			if (selected_items.size() == 1)
			{
				// get title from list
				auto selected_book_string = selected_items.at(0).data().toString();
				std::string title = "";
				int i = 0;
				while (selected_book_string.at(i) != '~')
				{
					title.push_back(selected_book_string.at(i).toLatin1());
					i++;
				}
				title.pop_back(); // space between end of title and ~
				// get input
				auto new_title = this->book_title->text().toStdString();
				auto new_author = this->book_author->text().toStdString();
				auto new_genre = this->book_genre->text().toStdString();
				auto new_year = this->book_year->value();
				try
				{
					this->service_books.serviceModifyBook(title, new_title, new_author, new_genre, new_year);
					this->populateListWidget(this->content, this->service_books.serviceGetBookList());
					this->book_title->clear();
					this->book_author->clear();
					this->book_genre->clear();
				}
				catch (ValidatorException&)
				{
					QMessageBox error;
					error.setText("Please enter valid data!");
					error.setIcon(QMessageBox::Warning);
					error.exec();
				}
			}
			else
			{
				QMessageBox error;
				error.setText("Please select a book from the list!");
				error.setIcon(QMessageBox::Warning);
				error.exec();
			}
		});
	QObject::connect(this->find_book, &QPushButton::clicked,
		[this]()
		{
			bool ok;
			auto title = QInputDialog::getText(this->find_input_dialog, "Find book", "Enter book title", QLineEdit::Normal, "", &ok);
			//QInputDialog::getText(dialog, window title, label, line edit mode, line edit text, ok)
			if (ok)
			{
				try
				{
					Book book_found = this->service_books.serviceFindBook(title.toStdString());
					QMessageBox found;
					found.setText("Book found!");
					found.setIcon(QMessageBox::Information);
					found.exec();
					auto book_found_content = this->content->findItems(QString::fromStdString(book_found.getTitle()), Qt::MatchStartsWith);
					if (book_found_content.size() == 1)
					{
						/*this->content->clearSelection();
						this->content->setCurrentItem(book_found_content.at(0), QItemSelectionModel::Select); 
						*/// if book is found, select it in list widget
					}
				}
				catch (ValidatorException&)
				{
					QMessageBox error;
					error.setText("Please enter valid data!");
					error.setIcon(QMessageBox::Warning);
					error.exec();
				}
				catch (RepoException& repo_exception)
				{
					QMessageBox error;
					if (repo_exception.getMessageError() == "book not found!\n")
					{
						error.setText("No book found!");
						error.setIcon(QMessageBox::Warning);
					}
					error.exec();
				}
			}
		});
	QObject::connect(this->filter_books, &QComboBox::activated,
		[this]()
		{
			auto selected_item_index = this->filter_books->currentIndex();
			switch (selected_item_index)
			{
				case FILTER_BY_TITLE:
					filterByTitle();
					break;
				case FILTER_BY_YEAR:
					filterByYear();
					break;
			}
			
		});
	QObject::connect(this->sort_books, &QComboBox::activated,
		[this]()
		{
			auto selected_item_index = this->sort_books->currentIndex();
			switch (selected_item_index)
			{
				case SORT_BY_TITLE:
					this->populateListWidget(this->content, this->service_books.serviceSortByTitle());
					break;
				case SORT_BY_AUTHOR:
					this->populateListWidget(this->content, this->service_books.serviceSortByAuthor());
					break;
				case SORT_BY_YEAR_AND_GENRE:
					this->populateListWidget(this->content, this->service_books.serviceSortByYearAndGenre());
					break;
			}
		});
	QObject::connect(this->add_to_cart, &QPushButton::clicked,
		[this]()
		{
			QInputDialog* title_input = new QInputDialog;
			bool ok;
			auto title_text = QInputDialog::getText(title_input, "Add book to cart", "Enter book title", QLineEdit::Normal, "", &ok);
			if (ok)
			{
				try
				{
					Book book_found = this->service_books.serviceFindBook(title_text.toStdString());
					this->service_rentals.addBookToCart(book_found);
				}
				catch (ValidatorException&)
				{
					QMessageBox error;
					error.setText("Please enter valid data!");
					error.setIcon(QMessageBox::Warning);
					error.exec();
				}
				catch (RepoException& repo_exception)
				{
					if (repo_exception.getMessageError() == "book not found!\n")
					{
						QMessageBox error;
						error.setText("No book with this title found!");
						error.setIcon(QMessageBox::Warning);
						error.exec();
					}
				}
			}
		});
	QObject::connect(this->clear_cart, &QPushButton::clicked,
		[this]()
		{
			this->service_rentals.deleteAllCart();
		});
	QObject::connect(this->generate_cart, &QPushButton::clicked,
		[this]()
		{
			QInputDialog* number_input = new QInputDialog;
			bool ok;
			auto number_of_books = QInputDialog::getInt(number_input, "Generate cart", "Enter number of books to generate", 0, 0, 999, 1, &ok);
			if (ok)
			{
				auto book_list = this->service_books.serviceGetBookList();
				this->service_rentals.generateCart(book_list, number_of_books);
			}
		});
	QObject::connect(this->undo_button, &QPushButton::clicked,
		[this]()
		{
			try
			{
				this->service_books.undo();
				this->populateListWidget(this->content, this->service_books.serviceGetBookList());
			}
			catch (std::string& string_error)
			{
				QMessageBox error;
				if (string_error == "empty undo list!\n")
				{
					error.setText("No more actions to undo!");
					error.setIcon(QMessageBox::Warning);
				}
				error.exec();
			}
		});
	
	QObject::connect(this->crud_cart, &QPushButton::clicked,
		[this]()
		{
			// must declare the new window as pointer
			CartCRUDGUI* cart_crud_window = new CartCRUDGUI{service_rentals};
			cart_crud_window->show();
		});
	QObject::connect(this->read_only_cart, &QPushButton::clicked,
		[this]()
		{
			CartReadOnlyGUI* cart_read_only_window = new CartReadOnlyGUI{service_rentals};
			cart_read_only_window->show();
		});
	/*for (const auto& genre_button : this->genre_buttons)
	{
		QObject::connect(genre_button, &QPushButton::clicked,
			[this, genre_button]()
			{
				auto genre_text = genre_button->text().toStdString();
				int count_genre = 0;
				for (const auto& book : this->service_books.serviceGetBookList())
					if (book.getGenre() == genre_text)
						count_genre++;
				QMessageBox message_genre_count;
				message_genre_count.setText(QString::fromStdString(genre_text + ": " + std::to_string(count_genre)));
				message_genre_count.exec();
			});
	}*/
}

void GUI::populateListWidget(MyListModel* list_widget, std::vector<Book> book_list)
{
	/*
	This function adds data from memory to the listWidget GUI component
	*/
	list_widget->clear();
	for (const auto& book : book_list)
	{
		QString line = "";
		line += QString::fromStdString(book.getTitle()) + " ~ ";
		line += QString::fromStdString(book.getAuthor()) + " ~ ";
		line += QString::fromStdString(book.getGenre()) + " ~ ";
		line += QString::fromStdString(std::to_string(book.getYear()));
		list_widget->addItem(line);
	}
}

void GUI::filterByTitle()
{
	bool ok;
	auto title = QInputDialog::getText(this->filter_title_input_dialog, "Filter book by title", "Enter book title (substring)", QLineEdit::Normal, "", &ok);
	if (ok)
	{
		try
		{
			auto filtered_books = this->service_books.serviceFilterByTitle(title.toStdString());
			QListWidget* filtered_books_list = new QListWidget;
			for (const auto& book : filtered_books)
			{
				QString line = "";
				line += QString::fromStdString(book.getTitle()) + " ~ ";
				line += QString::fromStdString(book.getAuthor()) + " ~ ";
				line += QString::fromStdString(book.getGenre()) + " ~ ";
				line += QString::fromStdString(std::to_string(book.getYear()));
				filtered_books_list->addItem(line);
			}
			filtered_books_list->setFont(this->app_font);
			filtered_books_list->show();
		}
		catch (ValidatorException&)
		{
			QMessageBox error;
			error.setText("Please enter valid data!");
			error.setIcon(QMessageBox::Warning);
			error.exec();
		}
	}
}

void GUI::filterByYear()
{
	bool ok_lower;
	auto lower_bound_year = QInputDialog::getInt(this->filter_year_lower_input_dialog, "Filter book by year", "Enter lower bound book year", 2023, 0, 9999, 1, &ok_lower);
	if (ok_lower)
	{
		bool ok_upper;
		auto upper_bound_year = QInputDialog::getInt(this->filter_year_upper_input_dialog, "Filter book by year", "Enter upper bound book year", 2023, 0, 9999, 1, &ok_upper);
		if (ok_upper)
		{
			auto filtered_books = this->service_books.serviceFilterByYear(lower_bound_year, upper_bound_year);
			QListWidget* filtered_books_list = new QListWidget;
			for (const auto& book : filtered_books)
			{
				QString line = "";
				line += QString::fromStdString(book.getTitle()) + " ~ ";
				line += QString::fromStdString(book.getAuthor()) + " ~ ";
				line += QString::fromStdString(book.getGenre()) + " ~ ";
				line += QString::fromStdString(std::to_string(book.getYear()));
				filtered_books_list->addItem(line);
			}
			filtered_books_list->setFont(this->app_font);
			filtered_books_list->show();
		}
	}
}