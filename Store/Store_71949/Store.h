#pragma once
#include <iostream>
#include <vector> 
#include "Product.h"
#include "Location.h"
#include "Space.h"

using namespace std;
class Store
{
private:
	vector<Product> products;
	vector<Space> spaces;

public:
	Store();
	void add();
	void enterName(Product &product);
	void enterExpiryDate(Product &product);
	void enterDateOfReceipt(Product& product);
	void enterNameOfManufacturer(Product &product);
	void enterUnit(Product &product);
	void enterAvailableQuantity(Product& product);
	Store(vector<Space>spaces);

	friend ostream& operator<<(ostream& output, const Store& store);
	friend istream& operator>>(istream& input, Store& store);
};

