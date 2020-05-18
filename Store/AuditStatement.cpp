#include <iostream>
#include "AuditStatement.h"
#include "ISODate.h"

using namespace std;

void AuditStatement:: copy(const AuditStatement& other)
{
	this->operationType = other.operationType;
	this->product = other.product;
	this->operationDate = other.operationDate;
}

void AuditStatement::erase()
{
}

AuditStatement::AuditStatement()
{
	this->operationType = '/0';
	this->product = Product();
	this->operationDate = ISODate();
}

AuditStatement::AuditStatement(string operationType, Product product, ISODate operationDate)
{
	this->operationType = operationType;
	this->product = product;
	this->operationDate = operationDate;
}

AuditStatement::AuditStatement(const AuditStatement& other)
{
	this->copy(other);
}

AuditStatement& AuditStatement::operator=(const AuditStatement& other)
{
	if (this != &other)
	{
		this->copy(other);
	}

	return *this;
}

bool AuditStatement::operator==(const AuditStatement& other)
{
	return this->operationType == other.operationType &&
		this->product == other.product &&
		this->operationDate == other.operationDate;
}

AuditStatement::~AuditStatement()
{
	this->erase();
}

void AuditStatement::setOperationType(string operationType)
{
	this->operationType = operationType;
}

void AuditStatement::setProduct(Product product)
{
	this->product = product;
}

void AuditStatement::setOperationDate(ISODate operationDate)
{
	this->product = product;
}

string AuditStatement::getOperationType() const
{
	return this->operationType;
}

Product AuditStatement::getProduct() const
{
	return this->product;
}

ISODate AuditStatement::getOperationDate() const
{
	return this->operationDate;
}

ostream& operator<<(ostream& output, const AuditStatement& auditStatement)
{
	output << auditStatement.operationType << endl;
	output << auditStatement.product << endl;
	output << auditStatement.operationDate << endl;

	return output;
}

istream& operator>>(istream& input, AuditStatement& auditStatement)
{
	getline(input, auditStatement.operationType);
	input >> auditStatement.product;
	input >> auditStatement.operationDate;

	return input;
}

