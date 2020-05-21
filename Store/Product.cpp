#include <iostream>
#include "Product.h"
#include "Location.h"
#include "AuditStatement.h"

using namespace std;

void Product::copy(const Product& other)
{
	this->name = other.name;
	this->expiryDate = other.expiryDate;
	this->dateOfReceipt = other.dateOfReceipt;
	this->nameOfManufacturer = other.nameOfManufacturer;
	this->unit = other.unit;
	this->availableQuantity = other.availableQuantity;
	this->location = other.location;
	this->comment = other.comment;
}

void Product::erase()
{
}

Product::Product()
{
	this->name = '\0';
	this->expiryDate = ISODate();
	this->dateOfReceipt = ISODate();
	this->nameOfManufacturer = '\0';
	this->unit = '\0';
	this->availableQuantity = 0;
	this->location = Location();
	this->comment = '\0';
}

Product::Product(string name, ISODate expiryDate, ISODate dateOfReceipt,
	string nameOfManufacturer, string unit, double availableQuantity, Location location, string comment)
{
	this->name = name;
	this->expiryDate = expiryDate;
	this->dateOfReceipt = dateOfReceipt;
	this->nameOfManufacturer = nameOfManufacturer;
	this->unit = unit;
	this->availableQuantity = availableQuantity;
	this->location = location;
	this->comment = comment;
}

Product::Product(const Product& other)
{
	this->copy(other);
	//this->availableQuantity = other.availableQuantity;
}

Product& Product::operator=(const Product& other)
{
	if (this != &other)
	{
		//this->erase();
		this->copy(other);
	}

	return *this;
}

bool Product::operator==(const Product& other)
{
	return this->name == other.name &&
		this->expiryDate == other.expiryDate &&
		this->dateOfReceipt == other.dateOfReceipt &&
		this->nameOfManufacturer == other.nameOfManufacturer &&
		this->unit == other.unit &&
		this->availableQuantity == other.availableQuantity &&
		this->location == other.location &&
		this->comment == other.comment;
}

Product::~Product()
{
	this->erase();
}

//Setters
void Product::setName(string name)
{
	this->name = name;
}

void Product::setExpiryDate(ISODate expiryDate)
{
	this->expiryDate = expiryDate;
}

void Product::setDateOfReceipt(ISODate dateOfReceipt)
{
	this->dateOfReceipt = dateOfReceipt;
}

void Product::setNameOfManufacturer(string nameOfManufacturer)
{
	this->nameOfManufacturer = nameOfManufacturer;
}

void Product::setUnit(string unit)
{
	this->unit = unit;
}

void Product::setAvailableQuantity(double availableQuantity)
{
	this->availableQuantity = availableQuantity;
}

void Product::setLocation(Location location)
{
	this->location = location;
}

void Product::setComment(string comment)
{
	this->comment = comment;
}

//Getters
string Product::getName()const
{
	return this->name;
}

ISODate Product::getExpiryDate()const
{
	return this->expiryDate;
}

ISODate Product::getDateOfReceipt()const
{
	return this->dateOfReceipt;
}

string Product::getNameOfManufacturer()const
{
	return this->nameOfManufacturer;
}

string Product::getUnit()const
{
	return this->unit;
}

double Product::getAvailableQuantity()const
{
	return this->availableQuantity;
}

Location Product::getLocation() const
{
	return this->location;
}

string Product::getComment()const
{
	return this->comment;
}

ostream& operator<<(ostream& output, const Product& product)
{
	output << product.name << endl;
	output << product.expiryDate << endl;
	output << product.dateOfReceipt << endl;
	output << product.nameOfManufacturer << endl;
	output << product.unit << endl;
	output << product.availableQuantity << endl;
	output << product.location << endl;
	output << product.comment << endl;

	return output;
}

istream& operator>>(istream& input, Product& product)
{
	getline(input, product.name);
	input >> product.expiryDate;
	input >> product.dateOfReceipt;
	getline(input, product.nameOfManufacturer);
	getline(input, product.unit);
	string availableQuantity;
	getline(input, availableQuantity);
	product.setAvailableQuantity(stod(availableQuantity));
	input >> product.location;
	getline(input,product.comment);

	return input;
}

void Product::productPrint()const
{
	cout << "Name of the product: " << this->name << endl;
	cout << "Expiry date: " << this->expiryDate << endl;
	cout << "Date of receipt: " << this->dateOfReceipt << endl;
	cout << "Name of the manufacturer: " << this->nameOfManufacturer << endl;
	cout << "Unit: " << this->unit << endl;
	cout << "Available quantity: " << this->availableQuantity << endl;
	this->location.printLocation();
	cout << "Comment: " << this->comment << endl;

}
