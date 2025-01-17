#pragma once
#include <iostream>
#include "Product.h"
#include "Location.h"
#include "ISODate.h"
#include "Space.h"
#include "Store.h"

using namespace std;

void testProduct();
void testLocation();
void testSpace();
void testStore();
void testISODate();
void saveProductInfoInFile(string outputFilePath, Product product);
void saveAsProductToFile(string filePath, Product* products, int numberOfProducts);
void testAuditStatement();
void testPrint();
void openFile(string filePath);
void printSuccessMessage(string filePath);
void printErrorMessage(string filePath);