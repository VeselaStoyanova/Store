#include <iostream>
#include "Location.h"

using namespace std;

void Location::copy(const Location& other)
{
	this->section = other.section;
	this->shelf = other.shelf;
	this->number = other.number;
}

Location::Location()
{
	this->section = 0;
	this->shelf = 0;
	this->number = 0;
}

Location::Location(int section, int shelf, int number)
{
	this->section = section;
	this->shelf = shelf;
	this->number = number;
}

Location::Location(const Location& other)
{
	this->section = other.section;
	this->shelf = other.shelf;
	this->number = other.number;
}

Location& Location::operator=(const Location& other)
{
	if (this != &other)
	{
		this->copy(other);
	}
	return *this;
}

bool Location::operator==(const Location& other)
{
	return this->section == other.section &&
		this->shelf == other.shelf &&
		this->number == other.number;
}

//Setters
void Location::setSection(const int section)
{
	this->section = section;
}

void Location::setShelf(const int shelf)
{
	this->shelf = shelf;
}

void Location::setNumber(const int number)
{
	this->number = number;
}

//Getters
int Location::getSection()const
{
	return this->section;
}

int Location::getShelf()const
{
	return this->shelf;
}

int Location::getNumber()const
{
	return this->number;
}

ostream& operator<<(ostream& output, const Location& location)
{
	output << location.section << endl;
	output << location.shelf << endl;
	output << location.number << endl;

	return output;
}

istream& operator>>(istream& input, Location& location)
{
	input >> location.section;
	input >> location.shelf;
	input >> location.number;

	return input;
}

/*
void Store::enterAvailableQuantity(Product& product)
{
	double availableQuantity;
	do
	{
		cout << "Enter the quantity of the product: " ;
		cin >> availableQuantity;
	}

	while (availableQuantity <= 0);
	product.setAvailableQuantity(availableQuantity);
}
*/

//Принтираме мястото на продукта
void Location::printLocation()
{
	cout << "Section: " << getSection() << endl;
	cout << "Shelf: " << getShelf() << endl;
	cout << "Number: " << getNumber() << endl;
}