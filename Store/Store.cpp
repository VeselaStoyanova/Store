#include <iostream>
#include "Store.h"
#include "Product.h"
#include "Location.h"
#include "AuditStatement.h"
#include <limits>
#include <string>
#include <time.h>

using namespace std;

Store::Store()
{
	
}

//Създаваме вектор от space-ове.
Store::Store(vector<Space>spaces)
{
	this->spaces = spaces;
}

//Създаваме вектор от auditStatement-и.
Store::Store(vector<AuditStatement> auditStatement)
{
	this->auditStatements = auditStatement;
}

bool Store::addLocation(Product& product)
{
	for (int i = 0; i < products.size(); i++)
	{
		bool areNamesEqual = products[i].getName().compare(product.getName()) == 0;
		bool areExpiryDatesEqual = (products[i].getExpiryDate() == product.getExpiryDate());

		//Проверяваме дали имената на продуктите са еднакви и дали сроковете им на годност са равни.
		//Ако имената са еднакви и сроковете на годност са равни, то слагаме продуктите на едно и също място.
		if (areNamesEqual && areExpiryDatesEqual)
		{
			Location location = products[i].getLocation();
			Space space = findSpaceByLocation(location);

			bool hasAvailableQuantityInSpace = space.getAvailableQuantity() >= product.getAvailableQuantity();
			bool areUnitsTheSame = space.getUnit() == product.getUnit();

			//Проверяваме дали имаме достатъчно място да сложим продуктите с еднакви имена и еднакъв срок на годност на едно и също място.
			if (hasAvailableQuantityInSpace && areUnitsTheSame)
			{
				product.setLocation(location);
				int newAvailableQuantity = space.getAvailableQuantity() - product.getAvailableQuantity();
				space.setAvailableQuantity(newAvailableQuantity);
				return true;
			}
		}
	}

	Space* space = findFirstAvailableSpace(product);

	if (space == nullptr)
	{
		return false;
	}

	else
	{
		Location location = *space->getLocation();
		product.setLocation(location);
		int newAvailableQuantity = space->getAvailableQuantity() - product.getAvailableQuantity();
		space->setAvailableQuantity(newAvailableQuantity);
		return true;
	}
}

Space Store::findSpaceByLocation(Location location)
{
	for (int i = 0; i < spaces.size(); i++)
	{
		if (*spaces[i].getLocation() == location)
		{
			return spaces[i];
		}
	}
}

Space* Store::findFirstAvailableSpace(Product product)
{
	for (int i = 0; i < spaces.size(); i++)
	{
		bool hasAvailableQuantityInSpace = spaces[i].getAvailableQuantity() >= product.getAvailableQuantity();
		bool areUnitsTheSame = spaces[i].getUnit() == product.getUnit();
		
		//Половината склад сме задали да се запълва с продукти в литри, а другата половина - в килограми.
		//Проверяваме дали имаме достатъчно място и дали мерната единица на продуктите е една и съща.
		if (hasAvailableQuantityInSpace && areUnitsTheSame)
		{
			return &spaces[i];
		}
	}
	return nullptr;
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
	enterComment(product);
	bool isSuitableLocationFound = addLocation(product);

	if (isSuitableLocationFound) 
	{
		this->products.push_back(product);
		string currentDateString = currentDateTime();
		ISODate currentDate;
		currentDate.constructDate(currentDateString);
		AuditStatement auditStatement = AuditStatement("add", product, currentDate);
		this->auditStatements.push_back(auditStatement);
	}

	else 
	{
		cout << "No suitable location was found for the product: " << endl << product << endl;
	}
}

void Store::logFromTo(ISODate fromDate, ISODate toDate, Store& store)
{
	int counter = 0;
	if (fromDate <= toDate)
	{
		for (int i = 0; i < auditStatements.size(); i++)
		{
			if (auditStatements[i].getOperationDate() >= fromDate && auditStatements[i].getOperationDate() <= toDate)
			{
				store.auditStatements[i].printAuditStatement();
				counter++;
			}
		}

		if (counter == 0)
		{
			cout << "There is no operation." << endl;
		}
	}

	else if(fromDate > toDate)
	{
		cout << "Error, bad input!" << endl;
	}
}

void Store::clean()
{
	//конструираме string от днешната дата
	string currentDateString = currentDateTime();
	ISODate currentDate;
	currentDate.constructDate(currentDateString);
	
	for (auto it = products.begin(); it != products.end();)
	{
		ISODate date = it->getExpiryDate();
		if (date <= currentDate)
		{
			removeProductFromSpace(*it);
			cout << "Removed product: " << *it << endl;
			it = products.erase(it);
		}
		
		else 
		{
			it++;
		}
	}
}

void Store::remove()
{
	string name = enterName();
	string unit = enterUnit();
	double availableQuantity = enterAvailableQuantity();

	Product* oldestProductMatchingCriteria = nullptr;
	int indexOfOldestProduct;

	for (int i = 0; i < products.size(); i++)
	{
		if(products[i].getName().compare(name) == 0 && products[i].getUnit().compare(unit) == 0 &&
			products[i].getAvailableQuantity() == availableQuantity)
		{
			if (oldestProductMatchingCriteria == nullptr || 
				products[i].getExpiryDate() < oldestProductMatchingCriteria->getExpiryDate())
			{
				oldestProductMatchingCriteria = &products[i];
				indexOfOldestProduct = i;
			}
		}
	}

	if (oldestProductMatchingCriteria == nullptr)
	{
		cout << "No product matching criteria is found." << endl;
	}

	else
	{
		Product productCopy = *oldestProductMatchingCriteria;
		removeProductFromSpace(*oldestProductMatchingCriteria);
		string currentDateString = currentDateTime();
		ISODate currentDate;
		currentDate.constructDate(currentDateString);
		AuditStatement auditStatement = AuditStatement("remove", *oldestProductMatchingCriteria, currentDate);
		this->auditStatements.push_back(auditStatement);
		products.erase(products.begin() + indexOfOldestProduct);
		cout << "The product was removed." << endl;
		cout << productCopy << endl;
	}
}

//Използвано от https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
//Взима текущата дата
const string Store::currentDateTime() 
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

	return buf;
}

void Store::removeProductFromSpace(Product product)
{
	for (int i = 0; i < spaces.size(); i++)
	{
		if (*spaces[i].getLocation() == product.getLocation())
		{
			int newAvailableQuantity = spaces[i].getAvailableQuantity() + product.getAvailableQuantity();
			spaces[i].setAvailableQuantity(newAvailableQuantity);
		}
	}
}

void Store::enterName(Product &product)
{
	string name = enterName();
	product.setName(name);
}

string Store::enterName()
{
	string name;
	do
	{
		cout << "Enter the name of the product: ";
		getline(cin, name);
	}

	while (name.empty() || name.size() > MAX_NAME_LENGTH);
	return name;
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
	product.setNameOfManufacturer(nameOfManufacturer);
}

void Store::enterUnit(Product& product)
{
	string unit = enterUnit();
	product.setUnit(unit);
}

string Store::enterUnit()
{
	string unit;
	do
	{
		cout << "Enter the unit of the product (kg for kilograms and l for liter): ";
		getline(cin, unit);
	}
	
	while (unit.empty() || unit.size() > MAX_UNIT_LENGTH || strcmp(unit.c_str(), "kg") != 0 && strcmp(unit.c_str(), "l") != 0);
	return unit;
}

void Store::enterAvailableQuantity(Product& product)
{
	double availableQuantity = enterAvailableQuantity();
	product.setAvailableQuantity(availableQuantity);
}

double Store::enterAvailableQuantity()
{
	double availableQuantity;
	string availableQuantityString;
	do
	{
		cout << "Enter the quantity of the product: ";	
		getline(cin, availableQuantityString);
		availableQuantity = stod(availableQuantityString);
	}

	while (availableQuantity <= 0);

	return availableQuantity;
}

void Store::enterComment(Product& product)
{
	string comment;
	//cin.ignore(INT_MAX, '\n');
	do
	{
		cout << "Enter a comment: ";
		getline(cin, comment);
	} 
	
	while (comment.empty() || comment.size() > MAX_COMMENT_LENGTH);
	product.setComment(comment);
}

ostream& operator<<(ostream& output, const Store& store)
{
	output << store.products.size()<<endl;

	for (int i = 0; i < store.products.size(); i++)
	{
		output << store.products[i];
	}

	output << store.spaces.size() << endl;

	for (int i = 0; i < store.spaces.size(); i++)
	{
		output << store.spaces[i];
	}

	output << store.auditStatements.size() << endl;

	for (int i = 0; i < store.auditStatements.size(); i++)
	{
		output << store.auditStatements[i];
	}

	return output;
}

istream& operator>>(istream& input, Store& store)
{
	if (store.products.size() > 0)
	{
		store.products.clear();
	}
	if (store.spaces.size() > 0) 
	{
		store.spaces.clear();
	}
	if (store.auditStatements.size() > 0)
	{
		store.auditStatements.clear();
	}

	string productsSizeStr;
	getline(input, productsSizeStr);
	int productsSize = stoi(productsSizeStr);

	for(int i = 0; i < productsSize; i++)
	{ 
		Product p;
		input >> p;
		store.products.push_back(p);
	}

	string spacesSizeStr;
	getline(input, spacesSizeStr);
	int spacesSize = stoi(spacesSizeStr);

	for (int i = 0; i < spacesSize; i++)
	{
		Space s;
		input >> s;
		store.spaces.push_back(s);
	}

	string auditStatementSizeStr;
	getline(input, auditStatementSizeStr);
	int auditStatementSize = stoi(auditStatementSizeStr);

	for (int i = 0; i < auditStatementSize; i++)
	{
		AuditStatement auditSt;
		input >> auditSt;
		store.auditStatements.push_back(auditSt);
	}

	return input;
}

void Store::print()
{
	cout << "The products in the store are: " << endl;
	for (int i = 0; i < this->products.size(); i++)
	{
		products[i].productPrint();
	}
}
