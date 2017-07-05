#include "stdafx.h"
#include "Record.h"


Record::Record()
{
}
Record::Record(std::string firmName, std::string postalCode, std::string city, std::string street, std::string contactPerson, std::string mail, std::string phone)
{
	this->firmName = firmName;
	this->postalCode = postalCode;
	this->city = city;
	this->street = street;
	this->contactPerson = contactPerson;
	this->mail = mail;
	this->phone = phone;
}

Record::~Record()
{
}

std::string Record::toString()
{
	return firmName + "|" + postalCode + "|" + city + "|" + street + "|" + contactPerson + "|" + mail + "|" + phone;
}
