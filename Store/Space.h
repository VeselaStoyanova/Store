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

	friend ostream& operator<<(ostream& output, const Space& space);
	friend istream& operator>>(istream& input, Space& space);

private:
	void copy(const Space& other);
};
