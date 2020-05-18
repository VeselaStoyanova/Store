#include <iostream>
#include "ISODate.h"
using namespace std;

ISODate::ISODate()
{
    this->year = 0;
    this->month = 0;
    this->day = 0;
    this->date = "";
}

ISODate::ISODate(const ISODate& other)
{
    this->year = other.year;
    this->month = other.month;
    this->day = other.day;
    this->date = other.date;
}

bool ISODate::operator==(const ISODate& other)
{
    return this->year == other.year &&
        this->month == other.month &&
        this->day == other.day &&
        this->date == other.date;
}

ISODate& ISODate::operator=(const ISODate& other) 
{
    if (this != &other)
    {
        this->copy(other);
    }
    return *this;
}

bool ISODate::operator>(const ISODate& other)
{
    if (this->year > other.year)
    {
        return true;
    }

    if (this->year == other.year && this->month > other.month)
    {
        return true;
    }

    if (this->year == other.year && this->month == other.month && this->day > other.day)
    {
        return true;
    }

    return false;
}

bool ISODate::operator<(const ISODate& other)
{
    return !(*this > other || *this == other);
}

bool ISODate::operator<=(const ISODate& other)
{
    return *this < other || *this == other;
}

bool ISODate::operator>=(const ISODate& other)
{
    return *this > other || *this == other;
}

void ISODate::copy(const ISODate& other)
{
    this->year = other.year;
    this->month = other.month;
    this->day = other.day;
    this->date = other.date;
}


ostream& operator<<(ostream& output, const ISODate& isoDate)
{
    output << isoDate.date;

    return output;
}

istream& operator>>(istream& input, ISODate& isoDate)
{    
    string str;
    getline(input, str);
    isoDate.constructDate(str);

    return input;
}

bool ISODate::constructDate(string date)
{
	if (!checkIfDateIsInISOFormat(date)) 
    {
		return false;
	}

	string yearStr = date.substr(0, 4);
	this->year = stoi(yearStr);

	string monthStr = date.substr(5, 2);
	this->month = stoi(monthStr);

	string dayStr = date.substr(8, 2);
	this->day = stoi(dayStr);

    bool isDateValid = isValidDate(this->day, this->month, this->year);
    if (!isDateValid) 
    {
        return false;
    }

    this->date = date;
	return true;
}

bool ISODate::checkIfDateIsInISOFormat(string date) 
{
	if (date.size() != strlen("YYYY-MM-DD"))
    {
		return false;
	}

	for (int i = 0; i < date.size(); i++) 
    {
		if (i == 4 || i == 7) 
        {
			bool isDash = date[i] == 45;
			if (!isDash) 
            {
				return false;
			}
		}

		else 
        {
			bool isNumber = date[i] >= 48 && date[i] <= 57;
			if (!isNumber) 
            {
				return false;
			}
		}
	}
	return true;
}

    //Проверяваме дали годината е високосна
bool ISODate::isLeap(int year)
{
    // Връща true ако годината се дели на 4 и не се дели на 100 
    // или се дели на 400.
    return (((year % 4 == 0) &&
        (year % 100 != 0)) ||
        (year % 400 == 0));
}

    //Проверяваме дали датата е валидна
bool ISODate::isValidDate(int d, int m, int y)
{
    if (y > MAX_VALID_YEAR || y < MIN_VALID_YEAR)
    {
        return false;
    }

    if (m < 1 || m > 12)
    {
        return false;
    }

    if (d < 1 || d > 31)
    {
        return false;
    }

    //Проверяваме за месец февруари 
    //Ако годината е високосна то максималните дни са 29
    //Ако годината не е високосна то максималните дни са 30
    if (m == 2)
    {
        if (isLeap(y))
        {
            return (d <= 29);
        }

        else
        {
            return (d <= 28);
        }
    }

    //Месеците април, юни, септември и ноември трябва да имат максимум 30 дни.
    if (m == 4 || m == 6 ||
        m == 9 || m == 11)
    {
        return (d <= 30);
    }

    return true;
}