#pragma once
#include <string>
class Record
{
public:
	Record();
	Record(std::string firmName, std::string postalCode, std::string city, std::string street, std::string contactPerson, std::string mail, std::string phone);
	~Record();

	std::string firmName;
	std::string postalCode;
	std::string city;
	std::string street;
	std::string contactPerson;
	std::string mail;
	std::string phone;

	std::string toString();
};

