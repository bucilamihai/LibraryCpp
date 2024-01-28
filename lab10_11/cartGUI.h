#pragma once
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
#include <QPainter>
#include <QPaintEvent>

#include <stdlib.h>

#include "observer.h"
#include "service_rental.h"
#include "book.h"

class CartCRUDGUI: public QWidget, public Observer
{
private:
	ServiceRental& service_rentals;
	QListWidget* cart_content;
	QPushButton* clear_cart;
	QPushButton* export_cart;

	void update() override
	{
		this->populateListWidget(this->cart_content, this->service_rentals.getAllCart());
	}

	void populateListWidget(QListWidget* list_widget, std::vector<Book> book_list)
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

public:
	CartCRUDGUI(ServiceRental& service_rentals) : service_rentals{service_rentals}
	{
		this->service_rentals.addObserver(this); // add this window as observer
		this->buildGUI();
		this->connectSignalsSlots();
		this->populateListWidget(this->cart_content, this->service_rentals.getAllCart());
	}
	void buildGUI()
	{
		this->cart_content = new QListWidget;
		this->clear_cart = new QPushButton("Clear cart");
		this->export_cart = new QPushButton("Export cart");
		QVBoxLayout* layout = new QVBoxLayout;
		layout->addWidget(this->cart_content);
		layout->addWidget(this->clear_cart);
		layout->addWidget(this->export_cart);
		this->setLayout(layout);
		this->setWindowTitle("CRUD cart");
	}
	void connectSignalsSlots()
	{
		QObject::connect(this->clear_cart, &QPushButton::clicked,
			[this]()
			{
				this->service_rentals.deleteAllCart();
			});
		QObject::connect(this->export_cart, &QPushButton::clicked,
			[this]()
			{
				QInputDialog* export_input = new QInputDialog;
				bool ok;
				auto export_text_file = QInputDialog::getText(export_input, "Export cart", "Enter file name", QLineEdit::Normal, "", &ok).toStdString();
				if (ok)
				{
					this->service_rentals.exportCart(export_text_file);
				}
			});
	}
};





class CartReadOnlyGUI: public QWidget, public Observer
{
private:
	ServiceRental& service_rentals;
	QPaintEvent* paint_event;

	void update() override
	{
		this->paintEvent(paint_event);
	}

protected:
	void paintEvent(QPaintEvent* ev) override 
	{
		QPainter painter{ this };
		for (int i = 0; i < this->service_rentals.getAllCart().size(); i++)
		{
			int x = 10*i;
			int y = 10*i;
			painter.drawImage(x, y, QImage("book.png"));
		}
		Q_UNUSED(ev); // to avoid warning
	}

public:
	CartReadOnlyGUI(ServiceRental& service_rentals) : service_rentals{ service_rentals }
	{
		this->service_rentals.addObserver(this);
		this->buildGUI();
	}

	void buildGUI()
	{
		this->setWindowTitle("Read-Only cart");
	}
};