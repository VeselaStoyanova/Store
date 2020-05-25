#include <iostream>
#include <fstream>
#include "Product.h"
#include "Location.h"
#include "Store.h"
#include "Space.h"
#include "Common.h"
#include "ISODate.h"
#include "Tests.h"
#include "CommandsExecutor.h"
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
    showMenu();
	return 0;
}