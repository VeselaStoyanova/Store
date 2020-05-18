#pragma once
#include <iostream>
#include "Product.h"

using namespace std;

class Location
{
private:
	int section;
	int shelf;
	int number;
	void copy(const Location& other);

public:
	Location();
	Location(int section, int shelf, int number);
	Location(const Location& other);
	Location& operator=(const Location& other);
	bool operator==(const Location& other);

	//Setters
	void setSection(const int section);
	void setShelf(const int shelf);
	void setNumber(const int number);

	//Getters
	int getSection()const;
	int getShelf()const;
	int getNumber()const;

	friend ostream& operator<<(ostream& output, const Location& location);
	friend istream& operator>>(istream& input, Location& location);
	void printLocation();
};

