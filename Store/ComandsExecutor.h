#pragma once
#include <iostream>
#include "Store.h"
#include "Space.h"
using namespace std;

void showHelp();
void showAdvancedHelp();
vector<Space> createSpaces();
void print(Store& store);
void openFileWithStore(string filePath, Store& storeToFill);
void saveStoreInFile(Store& store, string filePath);
bool isCommandOpen(string choice);
bool isFileSavedAs(string choice);
string showStartMenu();
string showAdvancedMenu();
void printSuccessMessage(string filePath);
void printErrorMessage(string filePath);
void openFile(string filePath);
string showParticularMenu(bool isFileOpen);
void showMenu();