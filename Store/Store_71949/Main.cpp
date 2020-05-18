#include <iostream>
#include <fstream>
#include "Product.h"
#include "Location.h"
#include "Store.h"
#include "Space.h"
#include "Common.h"
#include "ISODate.h"
using namespace std;

//Тестване на класът Product
void testProduct()
{
	Product firstProduct = Product();
	ISODate expiryDate;
	expiryDate.constructDate("2020-05-11");
	ISODate dateOfReceipt;
	dateOfReceipt.constructDate("2020-05-30");
	Product secondProduct = Product("Milk", expiryDate, dateOfReceipt, "Mia Stoyanova", "1 liter", 20, "Milk - 1 l");
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

	//Тестване на оператор >>
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
	Product secondProduct = Product("Milk", expiryDate, dateOfReceipt, "Mia Stoyanova", "1 liter", 20, "Milk - 1 l");

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

void print()
{
	Location* location = new Location(1, 3, 5);
	ISODate expiryDate;
	expiryDate.constructDate("2020-05-11");
	ISODate dateOfReceipt;
	dateOfReceipt.constructDate("2020-05-30");
	Product product = Product("Milk", expiryDate, dateOfReceipt, "Mia Stoyanova", "1 liter", 20, "Milk - 1 l");
	product.productPrint();
	cout << "Location: " << endl;
	location->printLocation();
}

//Функция, чрез която задаваме колко място има в склада
vector<Space> createSpaces() {
	vector<Space> spaces;

	//Задаваме колко секции има в склада
	int sectionsCount = SECTIONS_COUNT;

	//Задаваме колко рафта има в секция
	int shelvesCountPerSection = SHELVES_COUNT;

	//Задаваме колко номера има на рафт
	int numbersCountPerShelf = NUMBERS_COUNT;

	//Обхождаме мястото в склада по секции, рафтове и номера
	for (int i = 1; i < SECTIONS_COUNT; i++)
	{
		for (int j = 1; j < SHELVES_COUNT; j++)
		{
			for (int k = 1; k < NUMBERS_COUNT; k++)
			{
				Space space = Space(new Location(i, j, k), PRODUCTS_NUMBER);
				spaces.push_back(space);
			}
		}
	}

	//Задаваме мерна единица
	//За половината склад задаваме като мерна единица литри
	for (int i = 0; i < spaces.size() / 2; i++)
	{
		spaces[i].setUnit("l");
	}

	//За другата половина от склада задаваме като мерна единица килограми
	for (int i = spaces.size() / 2; i < spaces.size(); i++)
	{
		spaces[i].setUnit("kg");
	}
	return spaces;
}

//когато започваме ще можем да отворим файл, да видим какви команди поддържа програмата и да излезнем от програмата.
void showStartMenu()
{
	double choice;
	do
	{
		cout << "Enter 1 to open an existing file;" << endl;
		cout << "Enter 2 for help;" << endl;
		cout << "Enter 3 to exit;" << endl;
		cout << "Enter your choice: " << endl;
		cin >> choice;
	} 
	
	while (choice != 1 && choice != 2 && choice != 3);

	switch ((int)choice)
	{
	case 1: cout << "Open file." << endl;
		break;
	case 2: cout << "The following commands are supported:" << endl;
		cout << "Open			opens an existing file" << endl;
		cout << "Help			prints this information" << endl;
		cout << "Exit			exits the program" << endl;
		break;
	case 3: cout << "Exiting the program..." << endl;
		break;
	default: cout << "Not a valid choice." << endl;
		break;
	}
}

//Когато сме в даден файл ще можем да го затворим, да запишем промените във файла в същия файл,
//да запишем промените в друг файл, да видим какви команди поддържа програмата и да излезнем от програмата.
void showAdvancedMenu()
{
	double choice;
	do
	{
		cout << "Enter 1 to close the file;" << endl;
		cout << "Enter 2 to save the file;" << endl;
		cout << "Enter 3 to save as the file;" << endl;
		cout << "Enter 4 for help;" << endl;
		cout << "Enter 5 to exit;" << endl;
		cin >> choice;
	}

	while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5);

	switch ((int)choice)
	{
	case 1: cout << "Successfully closed file." << endl;
		break;
	case 2: cout << "Successfully saved file." << endl;
		break;
	case 3: cout << "The file was saved as: " << endl;
		cout << "Successfully saved." << endl;
		break;
	case 4: cout << "The following commands are supported: " << endl;
		cout << "Close			closes the currently opened file" << endl;
		cout << "Save			saves the currently open file" << endl;
		cout << "Save as			saves the currently open file in  <file>" << endl;
		cout << "Help			prints this information" << endl;
		cout << "Exit			exits the program" << endl;
		break;
	case 5: cout << "Exiting the program..." << endl;
		break;
	default: cout << "Not a valid choice" << endl;
		break;
	}
}

//Съобщение, ако сме успяли да запазим информацията във файл.
void printSuccessMessage(const char* filePath)
{
	cout << endl;
	cout << "Successfully saved content in file: " << filePath << endl;
}

//Съобщение, ако не сме успяли да запазим информацията във файл.
void printErrorMessage(const char* filePath)
{
	cerr << endl;
	cerr << "There was a problem opening file with name: " << filePath << endl;
}

//Open file.
void openFile()
{
	const char* filePath = "myFile.txt";

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

//Save file
void saveProductInfoInFile(const char* outputFilePath, Product product)
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

void saveAsProductToFile(const char* filePath, Product* products, int numberOfProducts)
{
	ofstream outputFileStream;
	outputFileStream.open(filePath, ios::out);
	if (outputFileStream.is_open())
	{
		for (int i = 0; i < numberOfProducts; i++) {
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

int main()
{

	const char* outputFilePath = "myFile.txt";
	Product product;
	vector<Space>spaces = createSpaces();
	Store store = Store(spaces);

	//saveProductInfoInFile(outputFilePath, product);
	//testProduct();
	//testLocation();
	//testSpace();
	//testStore();
	//print();
	//showStartMenu();
	//showAdvancedMenu();
	//openFile();
	//saveProductInfoInFile();
	//Product* product = new Product();
	//saveAsProductToFile(outputFilePath, &product, 3);
	testISODate();

	

	return 0;
}