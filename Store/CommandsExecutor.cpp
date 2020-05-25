#include <iostream>
#include <fstream>
#include <cstdlib>
#include "CommandsExecutor.h"
#include "Store.h"

using namespace std;

void showHelp() 
{
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
	cout << "Save As			saves the currently open file in  <file>" << endl;
	cout << "Help			prints this information" << endl;
	cout << "Exit			exits the program" << endl;		
	cout << "Print			prints information for the current products in the store" << endl;
	cout << "Add			adds new product in the store" << endl;
	cout << "Remove			removes a product from the store" << endl;
	cout << "Log <from> <to>  prints information for the changes in availability" << endl;
	cout << "Clean			clears the store of all expired products" << endl;
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

//Функция print
//Извежда информация за наличните продукти в склада.
void print(Store& store)
{
	store.print();
}

//Отваряне на файл
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

//Запазване във файл.
void saveStoreInFile(Store& store, string filePath) 
{
	ofstream outputFileStream;
	outputFileStream.open(filePath, ios::out);

	if (outputFileStream.is_open())
	{
		outputFileStream << store;
	}
}

bool isCommandOpen(string choice)
{
	return choice.size() > 5 && choice.substr(0, 5).compare("open ") == 0;
}

bool isFileSavedAs(string choice)
{
	return choice.size() > 8 && choice.substr(0, 8).compare("save as ") == 0;
}

bool isCommandLogFromTo(string choice)
{
	string sampleDates = "log 0000-00-00 0000-00-00";
	float commandLength = sampleDates.size();
	return choice.size() == commandLength && choice.substr(0, 4).compare("log ") == 0;
}

//Когато започваме ще можем да отворим файл, да видим какви команди поддържа програмата и да излезнем от програмата.
string showStartMenu()
{
	cout << "Enter one of the following options:" ;
	string choice;

	do
	{
		cout << endl;
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
	cout << endl;
	cout << "Enter one of the following options: ";
	string choice;

	do
	{
		cout << endl;
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
		cout << endl;
	}

	while (choice.compare("close") != 0 && choice.compare("save") != 0 && !isFileSavedAs(choice)
		&& choice.compare("help")  != 0 && choice.compare("exit") != 0 && choice.compare("print") != 0
		&& choice.compare("add") != 0 && choice.compare("remove") != 0 && !isCommandLogFromTo(choice)
		&& choice.compare("clean") != 0);

	return choice;
}

//Функцията log <from> <to>.
//Извежда спаравка за всички промени в наличносттаа в периода от дата <from> до дата <to>.
void logFromTo(string choice, Store& store)
{
	// Примерен потребителски вход - log 2020-02-02 2021-05-05

	//Конструираме fromDate от стринг
	string fromDateString = choice.substr(4, 10);
	ISODate fromDate;
	fromDate.constructDate(fromDateString);

	//Конструираме toDate от стринг
	string toDateString = choice.substr(15, 10);
	ISODate toDate;
	toDate.constructDate(toDateString);

	store.logFromTo(fromDate, toDate, store);
}

//Проверяваме дали имаме отворен файл.
//Ако нямаме, показваме showStartMenu.
//Ако имаме, показваме showAdvancedMenu.
string showParticularMenu(bool isFileOpen) 
{
	if (!isFileOpen) 
	{
		return showStartMenu();
	}

	else 
	{
		return showAdvancedMenu();
	}
}

void showMenu()
{
	bool isFileOpen = false;
	Store store;
	string filePath;
	string choice;

	//Проверяваме дали командата ни е exit.
	while (choice.compare("exit") != 0)
	{
		choice = showParticularMenu(isFileOpen);

		if (isCommandOpen(choice))
		{
			filePath = choice.substr(5, choice.size() - 5);

			//Проверяваме дали името на файла се състои само от интервали
			bool isFileNameNotOnlyIntervals = filePath.find_first_not_of(' ') != std::string::npos;

			if (isFileNameNotOnlyIntervals)
			{
				cout << "Open file." << endl;
				openFileWithStore(filePath, store);
				isFileOpen = true;
			}

			else
			{
				cout << "Error, not a valid name!" << endl;
			}

		}

		else if (isFileOpen == false && choice.compare("help") == 0)
		{
			showHelp();
		}

		else if (isFileOpen == true && choice.compare("help") == 0)
		{
			showAdvancedHelp();
		}

		else if (choice.compare("exit") == 0)
		{
			cout << "Exiting the program..." << endl;
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

		else if (isFileSavedAs(choice))
		{
			filePath = choice.substr(8, choice.size() - 8);
			saveStoreInFile(store, filePath);
			cout << "Successfully saved another file." << endl;
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
			store.remove();
		}

		else if (isCommandLogFromTo(choice))
		{
			logFromTo(choice, store);
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

