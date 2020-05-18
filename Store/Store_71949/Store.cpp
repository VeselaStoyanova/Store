#include <iostream>
#include "Store.h"
#include "Product.h"
#include "Location.h"
#include <limits>
#include <string>

using namespace std;

Store::Store()
{
	
}

Store::Store(vector<Space>spaces)
{
	this->spaces = spaces;
}

void Store::add()
{
	Product product;
	enterName(product); 
	enterExpiryDate(product);
	enterDateOfReceipt(product);
	enterNameOfManufacturer(product);
	enterUnit(product);
	enterAvailableQuantity(product);
	this->products.push_back(product);
}

void Store::enterName(Product &product)
{
	string name;
	do
	{
		cout << "Enter the name of the product: " ;
		getline(cin, name);
	} 

	while (name.empty() || name.size() > MAX_NAME_LENGTH);
	product.setName(name.c_str());
}

void Store::enterExpiryDate(Product &product)
{
	string expiryDate;
	ISODate isoDate;
	bool isDateValid;

	do
	{
		cout << "Enter the expiry date of the product: ";
		getline(cin, expiryDate);
		isDateValid = isoDate.constructDate(expiryDate);
	} 
	
	while (expiryDate.empty() || expiryDate.size() > MAX_DATE_LENGTH || !isDateValid);
	product.setExpiryDate(isoDate);
}

void Store::enterDateOfReceipt(Product& product)
{
	string dateOfReceipt;
	ISODate isoDate;
	bool isDateValid;

	do
	{
		cout << "Enter the date of receipt the product: ";
		getline(cin, dateOfReceipt);
		isDateValid = isoDate.constructDate(dateOfReceipt);
	}
	
	while (dateOfReceipt.empty()|| dateOfReceipt.size()> MAX_DATE_LENGTH || !isDateValid);
	product.setDateOfReceipt(isoDate);
}

void Store::enterNameOfManufacturer(Product &product)
{
	string nameOfManufacturer;
	do
	{
		cout << "Enter the name of the manufacturer of the product: ";
		getline(cin, nameOfManufacturer);
	}

	while (nameOfManufacturer.empty() || nameOfManufacturer.size() > MAX_NAME_LENGTH );
	product.setNameOfManufacturer(nameOfManufacturer.c_str());
}

void Store::enterUnit(Product &product)
{
	string unit;
	do
	{
		cout << "Enter the unit of the product (kg for kilograms and l for liter): ";
		getline(cin, unit);
	} 
	while (unit.empty() || unit.size() > MAX_UNIT_LENGTH || strcmp(unit.c_str(), "kg") != 0 && strcmp(unit.c_str(), "l") != 0);
	product.setUnit(unit.c_str());
}

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

ostream& operator<<(ostream& output, const Store& store)
{
	for (int i = 0; i < store.products.size(); i++)
	{
		cout << store.products[i] << endl;
	}

	return output;
}

istream& operator>>(istream& input, Store& store)
{
	for(int i = 0; i < store.products.size(); i++)
	{ 
		cin >> store.products[i];
	}
	
	return input;
}

//void Store::print()
//{
//	for (int i = 0; i < this->products.size(); i++)
//	{
//		products[i].print();
//	}
//}
