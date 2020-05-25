#pragma once
#include <iostream>
#include "Common.h"
#include "Location.h"
#include "ISODate.h"

using namespace std;

class Product
{
private:
	string name;
	ISODate expiryDate;
	ISODate dateOfReceipt;
	string nameOfManufacturer;
	string unit;
	double availableQuantity;
	Location location;
	string comment;
	
public:
	Product();
	Product(string name, ISODate expiryDate, ISODate dateOfReceipt,
		string nameOfManufacturer, string unit, double availableQuantity, Location location, string comment);
	Product(const Product& other);
	Product& operator=(const Product& other);
	bool operator==(const Product& other);
	~Product();

	//Setters
	void setName(string name);
	void setExpiryDate(ISODate expiryDate);
	void setDateOfReceipt(ISODate dateOfReceipt);
	void setNameOfManufacturer(string nameOfManufacturer);
	void setUnit(string unit);
	void setAvailableQuantity(double availableQuantity);
	void setLocation(Location location);
	void setComment(string comment);

	//Getters
	string getName()const;
	ISODate getExpiryDate()const;
	ISODate getDateOfReceipt()const;
	string getNameOfManufacturer()const;
	string getUnit()const;
	double getAvailableQuantity()const;
	Location getLocation() const;
	string getComment()const;

	friend ostream& operator<<(ostream& output, const Product& product);
	friend istream& operator>>(istream& input, Product& product);
	void productPrint()const;

private:
	void copy(const Product& other);
	void erase();
};
