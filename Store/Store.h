#pragma once
#include <iostream>
#include <vector> 
#include "Product.h"
#include "Location.h"
#include "Space.h"
#include "AuditStatement.h"

using namespace std;
class Store
{
private:
	vector<Product> products;
	vector<Space> spaces;
	vector<AuditStatement> auditStatement;
	void removeProductFromSpace(Product product);

public:
	Store();
	void print();
	void add();
	void clean();
	const string currentDateTime();
	bool addLocation(Product& product);
	Space findSpaceByLocation(Location location);
	Space* findFirstAvailableSpace(Product product);
	void enterName(Product &product);
	void enterExpiryDate(Product &product);
	void enterDateOfReceipt(Product& product);
	void enterNameOfManufacturer(Product &product);
	void enterUnit(Product &product);
	void enterAvailableQuantity(Product& product);
	void enterComment(Product& product);
	Store(vector<Space>spaces);
	Store(vector<AuditStatement> auditStatement);

	friend ostream& operator<<(ostream& output, const Store& store);
	friend istream& operator>>(istream& input, Store& store);
};

