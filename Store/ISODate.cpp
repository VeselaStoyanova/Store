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
        //Проверяваме дали символ на място номер 4 и на място номер 7 са тирета.
        //2000-01-01 - примерна дата в ISO формат
		if (i == 4 || i == 7) 
        {
            //Използваме символа за тире от ASCII таблицата - 45. 
			bool isDash = date[i] == 45;

            //Ако на място номер 4 или на място номер 7 не стоят тирета, то връщаме грешка.
			if (!isDash) 
            {
				return false;
			}
		}

        //Ако на място номер 4 и на място номер 7 стоят тирета, то проверяваме дали останлите символи са цифри и проверяваме дали това е валидна дата.
        //За проверката на символите дали са цифри използваме символите от 48 до 57 от ASCII таблицата.
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
// Връща true ако годината се дели на 4 и не се дели на 100 или се дели на 400.

bool ISODate::isLeap(int year)
{
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}   

//Проверяваме дали датата е валидна
bool ISODate::isValidDate(int day, int month, int year)
{
    if (year > MAX_VALID_YEAR || year < MIN_VALID_YEAR)
    {
        return false;
    }

    if (month < 1 || month > 12)
    {
        return false;
    }

    if (day < 1 || day > 31)
    {
        return false;
    }

    //Проверяваме за месец февруари.
    //Ако годината е високосна то максималните дни са 29.
    //Ако годината не е високосна то максималните дни са 28.
    if (month == 2)
    {
        if (isLeap(year))
        {
            return (day <= 29);
        }

        else
        {
            return (day <= 28);
        }
    }

    //Месеците април, юни, септември и ноември трябва да имат максимум 30 дни.
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        return (day <= 30);
    }

    return true;
}