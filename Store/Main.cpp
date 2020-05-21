#include <iostream>
#include <fstream>
#include "Product.h"
#include "Location.h"
#include "Store.h"
#include "Space.h"
#include "Common.h"
#include "ISODate.h"
#include "Tests.h"
#include "ComandsExecutor.h"
using namespace std;

void tests()
{
	testProduct();
	testLocation();
	testSpace();
	testStore();
	testISODate();
	testAuditStatement();
}

int main()
{

	/*const char* outputFilePath = "myFile.txt";
	Product product;
	vector<Space>spaces = createSpaces();
	Store store = Store(spaces);*/
    showMenu();
	return 0;
}