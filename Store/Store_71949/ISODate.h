#pragma once
#include <iostream>
#include <string>
#include "Common.h"
using namespace std;

class ISODate
{
private:
	int year;
	int month;
	int day;
	string date;

public:
	bool constructDate(string date);
	bool operator==(const ISODate& other);
	ISODate& operator=(const ISODate& other);
	friend ostream& operator<<(ostream& output, const ISODate& location);
	friend istream& operator>>(istream& input, ISODate& location);

private:
	bool checkIfDateIsInISOFormat(string date);
	bool isValidDate(int day, int month, int year);
	bool isLeap(int year);
	void copy(const ISODate& other);
};