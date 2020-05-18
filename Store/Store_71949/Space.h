#pragma once
#include <iostream>
#include <string>
#include "Location.h"
using namespace std;

class Space
{
private:
	Location* location;
	string unit;
	int availableQuantity;
	void copy(const Space& other);
	
public:
	Space();
	Space(Location* location, string unit, int availableQuantity);
	Space(const Space& other);
	Space& operator=(const Space& other);
	bool operator==(const Space& other);
	Space(Location* location, const int availableQuantity);

	//Setters
	void setLocation(Location* location);
	void setUnit(string unit);
	void setAvailableQuantity(const int availableQuantity);

	//Getters
	Location* getLocation() const;
	string getUnit() const;
	int getAvailableQuantity() const;

	friend ostream& operator<<(ostream& os, const Space& sp);
	friend istream& operator>>(istream& input, Space& space);
};
