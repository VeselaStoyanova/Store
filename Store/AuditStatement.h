#pragma once
#include <iostream>
#include "Product.h"
#include "ISODate.h"

using namespace std;

class AuditStatement
{
private:
	string operationType;
	Product product;
	ISODate operationDate;

public:
	AuditStatement();
	AuditStatement(string operationType, Product product, ISODate operationDate);
	AuditStatement(const AuditStatement& other);
	AuditStatement& operator=(const AuditStatement& other);
	bool operator==(const AuditStatement& other);
	~AuditStatement();

	//Setters
	void setOperationType(string operationType);
	void setProduct(Product product);
	void setOperationDate(ISODate operationDate);

	//Getters
	string getOperationType() const;
	Product getProduct() const;
	ISODate getOperationDate() const;

	friend ostream& operator<<(ostream& output, const AuditStatement& auditStatement);
	friend istream& operator>>(istream& input, AuditStatement& auditStatement);
	void printAuditStatement();

private:
	void copy(const AuditStatement& other);
	void erase();
};
