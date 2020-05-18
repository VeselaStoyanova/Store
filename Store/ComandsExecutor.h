#pragma once
#include <iostream>
#include "Store.h"
#include "Space.h"
using namespace std;

void showMenu();
void showHelp();
void showAdvancedHelp();
string showParticularMenu(bool isFileOpen);
vector<Space> createSpaces();
void print(Store& store);
void openFileWithStore(string filePath, Store& storeToFill);
void saveStoreInFile(Store& store, string filePath);
string showStartMenu();
string showAdvancedMenu();
void printSuccessMessage(string filePath);
void printErrorMessage(string filePath);
void openFile(string filePath);
bool isCommandOpen(string choice);

