#include <iostream>
#include <fstream>
#include <cstdlib>
#include "ComandsExecutor.h"
#include "Store.h"

using namespace std;

void showHelp() {
	cout << endl;
	cout << "The following commands are supported:" << endl;
	cout << "Open <path>		opens an existing file or creates a new file" << endl;
	cout << "Help			prints this information" << endl;
	cout << "Exit			exits the program" << endl;
	cout << endl;
}

void showAdvancedHelp()
{
	cout << endl;
	cout << "The following commands are supported: " << endl;
	cout << "Close			closes the currently opened file" << endl;
	cout << "Save			saves the currently open file" << endl;
	cout << "Save as			saves the currently open file in  <file>" << endl;
	cout << "Help			prints this information" << endl;
	cout << "Exit			exits the program" << endl;
	cout << endl;
}

//Функция, чрез която задаваме колко място има в склада
vector<Space> createSpaces()
{
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

void print(Store& store)
{
	store.print();
	/*Location* location = new Location(1, 3, 5);
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
	location->printLocation();*/
}

//Open file.
void openFileWithStore(string filePath, Store& storeToFill)
{
	ifstream inputFileStream;
	inputFileStream.open(filePath, ios::in);

	if (inputFileStream.is_open())
	{
		inputFileStream >> storeToFill;
	}
	else 
	{
		vector<Space>spaces = createSpaces();
		storeToFill = Store(spaces);
	}
}

void saveStoreInFile(Store& store, string filePath) 
{
	ofstream outputFileStream;
	outputFileStream.open(filePath, ios::out);
	if (outputFileStream.is_open())
	{
		outputFileStream << store;
	}
}

bool isCommandOpen(string choice) {
	return choice.size() > 5 && choice.substr(0, 5).compare("open ") == 0;
}



//Когато започваме ще можем да отворим файл, да видим какви команди поддържа програмата и да излезнем от програмата.
string showStartMenu()
{
	cout << "Enter one of the following options:" << endl;
	string choice;
	do
	{
		cout << "open <path to file>" << endl;
		cout << "help" << endl;
		cout << "exit" << endl;
		getline(cin, choice);
	}

	while (!isCommandOpen(choice) && choice.compare("help") != 0 && choice.compare("exit") != 0);

	return choice;
}

//Когато сме в даден файл ще можем да го затворим, да запишем промените във файла в същия файл,
//да запишем промените в друг файл, да видим какви команди поддържа програмата и да излезнем от програмата.
string showAdvancedMenu()
{
	cout << "Enter one of the following options: " << endl;
	string choice;
	do
	{
		cout << "close" << endl;
		cout << "save" << endl;
		cout << "save as" << endl;
		cout << "help" << endl;
		cout << "exit" << endl;
		cout << "print" << endl;
		cout << "add" << endl;
		cout << "remove" << endl;
		cout << "log <from> <to>" << endl;
		cout << "clean" << endl;
		getline(cin, choice);
	}

	while (choice.compare("close") != 0 && choice.compare("save") != 0 && choice.compare("save as") != 0
		&& choice.compare("help")  != 0 && choice.compare("exit") != 0 && choice.compare("print") != 0
		&& choice.compare("add") != 0 && choice.compare("remove") != 0 && choice.compare("log") != 0
		&& choice.compare("clean") != 0);

	return choice;
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

//Open file.
void openFile(string filePath)
{
	//const char* filePath = "myFile.txt";
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

string showParticularMenu(bool isFileOpen) {
	if (!isFileOpen) {
		return showStartMenu();
	}
	else {
		return showAdvancedMenu();
	}
}

void showMenu() {

	bool isFileOpen = false;
	Store store;
	string filePath;

	string choice;

	while (choice.compare("exit") != 0) {
		choice = showParticularMenu(isFileOpen);

		if (isCommandOpen(choice))
		{
			filePath = choice.substr(5, choice.size() - 5);
			bool isFileNameOnlyIntervals = filePath.find_first_not_of(' ') != std::string::npos;
			if (isFileNameOnlyIntervals) {

			}

			cout << "Open file." << endl;
			openFileWithStore(filePath, store);
			isFileOpen = true;
		}
		else if (choice.compare("help") == 0)
		{
			showHelp();
		}
		else if (choice.compare("exit") == 0)
		{
			cout << "Exiting the program..." << endl;
			//	exit(0);
		}
		else if (choice.compare("close") == 0)
		{
			cout << "Successfully closed file." << endl;
			isFileOpen = false;
		}
		else if (choice.compare("save") == 0)
		{
			saveStoreInFile(store, filePath);
			cout << "Successfully saved file." << endl;
			isFileOpen = false;
		}

		else if (choice.compare("save as") == 0)
		{
			getline(cin, filePath);
			saveStoreInFile(store, filePath);
			cout << "Successfully saved file." << endl;
			isFileOpen = false;
		}

		else if (choice.compare("help") == 0)
		{
			showAdvancedHelp();
		}

		else if (choice.compare("print") == 0)
		{
			print(store);
		}

		else if (choice.compare("add") == 0)
		{
			store.add();
		}

		else if (choice.compare("remove") == 0)
		{
			cout << "The product was removed." << endl;
			cout << "Trqbva da napisha funkciqta" << endl;
		}

		else if (choice.compare("log") == 0)
		{
			cout << "LOG FROM TO" << endl;
			cout << "Trqbva da napisha funkciqta" << endl;
		}

		else if (choice.compare("clean") == 0)
		{
			store.clean();
		}

		else
		{
			cout << "Not a valid choice." << endl;
		}
	}
}

