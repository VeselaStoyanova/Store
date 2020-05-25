#include <iostream>
#include "Space.h"

using namespace std;

void Space::copy(const Space& other)
{
	this->location = other.location;
	this->unit = other.unit;
	this->availableQuantity = other.availableQuantity;
}

Space::Space()
{
	this->location = 0;
	this->unit = '\0';
	this->availableQuantity = 0;
}

Space::Space(Location* location, string unit, const int availableQuantity)
{
	this->location = location;
	this->unit = unit;
	this->availableQuantity = availableQuantity;
}

Space::Space(Location* location, const int availableQuantity)
{
	this->location = location;
	this->availableQuantity = availableQuantity;
}

Space::Space(const Space& other)
{
	this->copy(other);
	this->location = other.location;
	this->unit = other.unit;
	this->availableQuantity = other.availableQuantity;
}

Space& Space:: operator=(const Space& other)
{
	if (this != &other)
	{
		this->copy(other);
	}

	return *this;
}

bool Space:: operator==(const Space& other)
{
	return this->location == other.location &&
		this->unit == other.unit &&
		this->availableQuantity == other.availableQuantity;
}

//Setters
void Space::setLocation(Location* location)
{
	delete[] this->location;
	*this->location = *location;
}

void Space::setUnit(string unit)
{
	this->unit = unit;
}

void Space::setAvailableQuantity(const int availableQuantity)
{
	this->availableQuantity = availableQuantity;
}

//Getters
Location* Space::getLocation() const
{
	return this->location;
}

string Space::getUnit() const
{
	return this->unit;
}

int Space::getAvailableQuantity() const
{
	return this->availableQuantity;
}

ostream& operator<<(ostream& output, const Space& space)
{
	output << *space.location << endl;
	output << space.unit << endl;
	output << space.availableQuantity << endl;

	return output;
}

istream& operator>>(istream& input, Space& space)
{
	space.location = new Location();
	input >> *space.location;
	getline(input, space.unit);
	string availableQuantity;
	getline(input, availableQuantity);
	space.setAvailableQuantity(stod(availableQuantity));

	return input;
}

