#include <iostream>
#include "Tests.h"
#include <fstream>
#include "CommandsExecutor.h"

using namespace std;

//Тестване на класът Product
void testProduct()
{
	Product firstProduct = Product();
	ISODate expiryDate;
	expiryDate.constructDate("2020-05-11");
	ISODate dateOfReceipt;
	dateOfReceipt.constructDate("2020-05-30");
	Product secondProduct = Product("Milk", expiryDate, dateOfReceipt, "Mia Stoyanova", "1 liter", 20, Location(1,2,3), "Milk - 1 l");
	cout << secondProduct << endl;
	secondProduct.productPrint();
	Product thirdProduct = secondProduct;
	cout << thirdProduct << endl;
	thirdProduct.productPrint();

	Product fourthProduct = Product(secondProduct);
	cout << fourthProduct << endl;
	fourthProduct.productPrint();

	//Тестване на оператор >>
	Product inputProduct;
	cin >> inputProduct;
	cout << inputProduct;
}

//Тестване на клас Location
void testLocation()
{
	Location* firstLocation = new Location();
	Location* secondLocation = new Location(1, 3, 5);
	cout << secondLocation << endl;
	Location location = Location(1, 5, 7);
	location.printLocation();

	//Тестване на оператор >>
	Location inputLocation;
	cin >> inputLocation;
	cout << inputLocation;
}

//Тестване на клас Space
void testSpace()
{
	Space firstSpace = Space();
	Location* secondLocation = new Location(1, 3, 5);
	Space secondSpace = Space(secondLocation, "kg", 12);
	Space thirdSpace = secondSpace;
	cout << thirdSpace << endl;

	Space fourthSpace = Space(secondSpace);
	cout << fourthSpace << endl;

	//Тестване на оператор >> и оператор <<
	Space inputSpace;
	cin >> inputSpace;
	cout << inputSpace;
}

//Тестване на клас Store
void testStore()
{
	Store store = Store();
	Product firstProduct = Product();
	ISODate expiryDate;
	expiryDate.constructDate("2020-05-11");
	ISODate dateOfReceipt;
	dateOfReceipt.constructDate("2020-05-30");
	Product secondProduct = Product("Milk", expiryDate, dateOfReceipt, "Mia Stoyanova", "1 liter", 20, Location(1, 2, 3), "Milk - 1 l");

	store.enterName(firstProduct);
	store.enterNameOfManufacturer(firstProduct);
	store.enterUnit(firstProduct);
	store.add();
	store.enterDateOfReceipt(firstProduct);
}

void testISODate()
{
	ISODate date;
	//Тестване дали конструирането на датата в ISO 8601 формат работи
	//Тестваме дали работи с невисокоснa годинa
	cout << "2001-02-29 - " << boolalpha << date.constructDate("2001-02-29") << endl;
	//Тестваме дали работи с високосна година
	cout << "2000-02-29 - " << boolalpha << date.constructDate("2000-02-29") << endl;
	//Тестваме дали работи с валидна дата
	cout << "2001-02-12 - " << boolalpha << date.constructDate("2001-02-12") << endl;
	//Тестваме дали работи с невалидна година
	cout << "200123-04-29 - " << boolalpha << date.constructDate("200123-04-29") << endl;
	//Тестваме дали работи с невалиден месец
	cout << "2001-22-29 - " << boolalpha << date.constructDate("2001-22-29") << endl;
	//Тестваме дали работи с невалиден ден
	cout << "2001-02-55 - " << boolalpha << date.constructDate("2001-02-55") << endl;
}

void testAuditStatement()
{
	AuditStatement auditStatement = AuditStatement();
	ISODate expiryDate;
	expiryDate.constructDate("2020-05-11");
	ISODate dateOfReceipt;
	dateOfReceipt.constructDate("2020-05-30");
	Product secondProduct = Product("Milk", expiryDate, dateOfReceipt, "Mia Stoyanova", "1 liter", 20, Location(1, 2, 3), "Milk - 1 l");
	ISODate date;
	date.constructDate("2020-05-30");
	AuditStatement secondAuditStatement = AuditStatement("add", secondProduct, date);
	AuditStatement thirdAuditStatement = secondAuditStatement;
	cout << thirdAuditStatement << endl;
	AuditStatement fourthAuditStatement = AuditStatement(secondAuditStatement);
	cout << fourthAuditStatement << endl;
}

//Save file
void saveProductInfoInFile(string outputFilePath, Product product)
{
	ofstream outputFileStream;
	outputFileStream.open(outputFilePath, ios::out);
	if (outputFileStream.is_open())
	{
		outputFileStream << "Name of the product: " << product.getName() << endl;
		outputFileStream << "Expiry date: " << product.getExpiryDate() << endl;
		outputFileStream << "Date of receipt: " << product.getDateOfReceipt() << endl;
		outputFileStream << "Name of manufacturer: " << product.getNameOfManufacturer() << endl;
		outputFileStream << "Unit: " << product.getUnit() << endl;
		outputFileStream << "Available quantity: " << product.getAvailableQuantity() << endl;
		outputFileStream << "Comment: " << product.getComment() << endl;
		outputFileStream.close();
		printSuccessMessage(outputFilePath);
	}

	else
	{
		printErrorMessage(outputFilePath);
	}
}

//Save as file
void saveAsProductToFile(string filePath, Product* products, int numberOfProducts)
{
	ofstream outputFileStream;
	outputFileStream.open(filePath, ios::out);
	if (outputFileStream.is_open())
	{
		for (int i = 0; i < numberOfProducts; i++)
		{
			outputFileStream << products[i].getName() << " " << products[i].getExpiryDate()
				<< " " << products[i].getDateOfReceipt() << " "
				<< products[i].getNameOfManufacturer() << " " << products[i].getUnit()
				<< products[i].getAvailableQuantity() << " " << products[i].getComment() << endl;
		}

		printSuccessMessage(filePath);
		outputFileStream.close();
	}

	else
	{
		printErrorMessage(filePath);
	}
}

void testPrint()
{
	Location* location = new Location(1, 3, 5);
	ISODate expiryDate;
	expiryDate.constructDate("2020-05-11");
	ISODate dateOfReceipt;
	dateOfReceipt.constructDate("2020-05-30");
	Product product = Product("Milk", expiryDate, dateOfReceipt, "Mia Stoyanova", "1 liter", 20, Location(1, 2, 3), "Milk - 1 l");
	Product secondProduct = Product("Eggs", expiryDate, dateOfReceipt, "Sisi Stoyanova", "1 kg", 20, Location(2, 2, 3), "Eggs - 1 kg");
	product.productPrint();
	cout << "Location: " << endl;
	location->printLocation();
	cout << endl;
	secondProduct.productPrint();
	cout << "Location: " << endl;
	location->printLocation();
}

//Отваряне на файл.
void openFile(string filePath)
{
	ifstream inputFileStream;
	inputFileStream.open(filePath, ios::in);

	if (inputFileStream.is_open())
	{
		char lineFromFile[MAX_SIZE];

		while (!inputFileStream.eof())
		{
			inputFileStream.getline(lineFromFile, MAX_SIZE);
			cout << lineFromFile << endl;
		}

		inputFileStream.close();
		printSuccessMessage(filePath);
	}

	else
	{
		printErrorMessage(filePath);
	}
}

//Съобщение, ако сме успяли да запазим информацията във файл.
void printSuccessMessage(string filePath)
{
	cout << endl;
	cout << "Successfully saved content in file: " << filePath << endl;
}

//Съобщение, ако не сме успяли да запазим информацията във файл.
void printErrorMessage(string filePath)
{
	cerr << endl;
	cerr << "There was a problem opening file with name: " << filePath << endl;
}