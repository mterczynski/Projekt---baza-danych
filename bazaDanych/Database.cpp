#include "stdafx.h"
#include "Database.h"
#include "Record.h"
#include "Console.h"
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>


void split(std::string str, std::string splitBy, std::vector<std::string>& tokens)
{
	/* Store the original string in the array, so we can loop the rest
	* of the algorithm. */
	tokens.push_back(str);

	// Store the split index in a 'size_t' (unsigned integer) type.
	size_t splitAt;
	// Store the size of what we're splicing out.
	size_t splitLen = splitBy.size();
	// Create a string for temporarily storing the fragment we're processing.
	std::string frag;
	// Loop infinitely - break is internal.
	while (true)
	{
		/* Store the last string in the vector, which is the only logical
		* candidate for processing. */
		frag = tokens.back();
		/* The index where the split is. */
		splitAt = frag.find(splitBy);
		// If we didn't find a new split point...
		if (splitAt == std::string::npos)
		{
			// Break the loop and (implicitly) return.
			break;
		}
		/* Put everything from the left side of the split where the string
		* being processed used to be. */
		tokens.back() = frag.substr(0, splitAt);
		/* Push everything from the right side of the split to the next empty
		* index in the vector. */
		tokens.push_back(frag.substr(splitAt + splitLen, frag.size() - (splitAt + splitLen)));
	}
}

Database::Database()
{
}

Database::~Database()
{
}
Database::Database(std::string path)
{
	this->path = path;
}
void Database::removeAll(Console * console)
{
	this->records.clear();
	this->overwrite();
	this->loadFromFile();
	console->clear();
	console->setColor("green", "black");
	std::cout << "Pomyslnie usunieto wszystkie rekordy" << std::endl;
	console->setColor("white", "black");
	_getch();
}
void Database::overwrite()
{
	// Clear file
	std::ofstream ofs;
	ofs.open(path, std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	// Append to file
	std::ofstream file;
	file.open(path, std::ios_base::app);
	for (int i = 0; i < records.size(); i++)
	{
		file << records.at(i).toString();
		file << std::endl;
		_getch();
	}
}
void Database::loadFromFile()
{
	std::ifstream file;
	std::string line;
	file.open(path);

	while (std::getline(file, line))
	{
		std::string segment;
		std::vector<std::string> seglist;
		
		split(line, "|", seglist);

		Record * record = new Record(seglist.at(0), seglist.at(1), seglist.at(2), seglist.at(3), seglist.at(4), seglist.at(5), seglist.at(6));

		records.push_back(*record);
	}
}
void Database::reload()
{
	records.clear();
	this->loadFromFile();
}
void Database::select(Console * console, std::string fieldName, std::string value)
{
	if (records.size() > 0)
	{
		std::vector <Record> tempRecords(records); // create a copy of existing records
		if (fieldName == "Nazwa firmy")
		{
			for (int i = 0; i < tempRecords.size(); i++)
			{
				Record record = tempRecords.at(i);
				if (record.firmName != value)
				{
					tempRecords.erase(tempRecords.begin() + i);
					i = 0;
				}
			}
			if (tempRecords.size()>0 && tempRecords.at(0).firmName != value)
			{
				std::vector <Record> empty;
				tempRecords = empty;
			}
		}
		else if (fieldName == "Kod pocztowy")
		{
			for (int i = 0; i < tempRecords.size(); i++)
			{
				Record record = tempRecords.at(i);
				if (record.postalCode != value)
				{
					tempRecords.erase(tempRecords.begin() + i);
					i = 0;
				}
			}
			if (tempRecords.size()>0 && tempRecords.at(0).postalCode != value)
			{
				std::vector <Record> empty;
				tempRecords = empty;
			}
		}
		else if (fieldName == "Miasto")
		{
			for (int i = 0; i < tempRecords.size(); i++)
			{
				Record record = tempRecords.at(i);
				if (record.city != value)
				{
					tempRecords.erase(tempRecords.begin() + i);
					i = 0;
				}
			}
			if (tempRecords.size()>0 && tempRecords.at(0).city != value)
			{
				std::vector <Record> empty;
				tempRecords = empty;
			}
		}
		else if (fieldName == "Ulica")
		{
			for (int i = 0; i < tempRecords.size(); i++)
			{
				Record record = tempRecords.at(i);
				if (record.street != value)
				{
					tempRecords.erase(tempRecords.begin() + i);
					i = 0;
				}
			}
			if (tempRecords.size()>0 && tempRecords.at(0).street != value)
			{
				std::vector <Record> empty;
				tempRecords = empty;
			}
		}
		else if (fieldName == "Osoba do kontaktu")
		{
			for (int i = 0; i < tempRecords.size(); i++)
			{
				Record record = tempRecords.at(i);
				if (record.contactPerson != value)
				{
					tempRecords.erase(tempRecords.begin() + i);
					i = 0;
				}
			}
			if (tempRecords.size()>0 && tempRecords.at(0).contactPerson != value)
			{
				std::vector <Record> empty;
				tempRecords = empty;
			}
		}
		else if (fieldName == "Mail")
		{
			for (int i = 0; i < tempRecords.size(); i++)
			{
				Record record = tempRecords.at(i);
				if (record.mail != value)
				{
					tempRecords.erase(tempRecords.begin() + i);
					i = 0;
				}
			}
			if (tempRecords.size()>0 && tempRecords.at(0).mail != value)
			{
				std::vector <Record> empty;
				tempRecords = empty;
			}
		}
		else if (fieldName == "Telefon")
		{
			for (int i = 0; i < tempRecords.size(); i++)
			{
				Record record = tempRecords.at(i);
				if (record.phone != value)
				{
					tempRecords.erase(tempRecords.begin() + i);
					i = 0;
				}
			}
			if (tempRecords.size()>0 && tempRecords.at(0).phone != value)
			{
				std::vector <Record> empty;
				tempRecords = empty;
			}
		}
		else
		{
			console->clear();
			console->setColor("red", "black");
			std::cout << "Nie ma kolumny o takiej nazwie.";
			console->setColor("white", "black");
			return;
		}
		if (tempRecords.size() == 0)
		{
			console->clear();
			console->setColor("yellow", "black");
			std::cout << "Nic nie znaleziono.";
			console->setColor("white", "black");
		}
		std::cout << tempRecords.size();
		records = tempRecords;
		selectAll(console);
	}
	else
	{
		console->clear();
		console->setColor("yellow", "black");
		std::cout << "Nic nie znaleziono.";
		console->setColor("white", "black");
	}
}
void Database::selectAll(Console * console)
{
	console->clear();
	console->setFontSize(20);
	console->showConsoleCursor(true);
	console->setColor("green", "black");
	std::cout << "Liczba rekordow: " << records.size() << std::endl;
	console->setColor("white", "black");
	if (records.size() > 0)
	{
		std::string fieldNames[7] = { "Nazwa firmy","Kod pocztowy","Miasto","Ulica","Osoba do kontaktu","Mail","Telefon" };
		int maxSizes[7] = {
			fieldNames[0].length(),
			fieldNames[1].length(),
			fieldNames[2].length(),
			fieldNames[3].length(),
			fieldNames[4].length(),
			fieldNames[5].length(),
			fieldNames[6].length()
		};
		for (int i = 0; i < records.size(); i++)
		{
			//std::cout << records.at(i).toString() << std::endl;
			int sizes[7];
			Record record = records.at(i);
			sizes[0] = record.firmName.length();
			sizes[1] = record.postalCode.length();
			sizes[2] = record.city.length();
			sizes[3] = record.street.length();
			sizes[4] = record.contactPerson.length();
			sizes[5] = record.mail.length();
			sizes[6] = record.phone.length();
			for (int j = 0; j < 7; j++)
			{
				if (sizes[j] > maxSizes[j])
				{
					maxSizes[j] = sizes[j];
				}
			}
		}
		// head line
		for (int i = 0; i < 7; i++)
		{
			std::cout << "+";
			for (int j = 0; j < maxSizes[i]; j++)
			{
				std::cout << "-";
			}
		}
		std::cout << "+"; 
		// end of head line
		std::cout << std::endl;
		// names
		for (int i = 0; i < 7; i++) 
		{
			int toFill = maxSizes[i] - fieldNames[i].length();
			std::cout << "|";
			for (int j = 0; j < toFill/2; j++)
			{
				std::cout << " ";
			}
			std::cout << fieldNames[i];
			if (toFill % 2 == 1)
				toFill += 1;
			for (int j = 0; j < toFill/2; j++)
			{
				std::cout << " ";
			}
		}
		std::cout << "|";
		// end of names
		std::cout << std::endl;
		// line
		for (int i = 0; i < 7; i++)
		{
			std::cout << "+";
			for (int j = 0; j < maxSizes[i]; j++)
			{
				std::cout << "-";
			}
		}
		std::cout << "+";
		std::cout << std::endl;
		//end of line
		// data
		for (int i = 0; i < records.size(); i++) // dla ka¿dego rekordu
		{
			int toFill;
			Record record = records.at(i);

			toFill = maxSizes[0] - record.firmName.length();
			std::cout << "|";
			for (int j = 0; j < toFill / 2; j++)
			{
				std::cout << " ";
			}
			std::cout << record.firmName;
			if (toFill % 2 == 1)
				toFill += 1;
			for (int j = 0; j < toFill / 2; j++)
			{
				std::cout << " ";
			}

			toFill = maxSizes[1] - record.postalCode.length();
			std::cout << "|";
			for (int j = 0; j < toFill / 2; j++)
			{
				std::cout << " ";
			}
			std::cout << record.postalCode;
			if (toFill % 2 == 1)
				toFill += 1;
			for (int j = 0; j < toFill / 2; j++)
			{
				std::cout << " ";
			}

			toFill = maxSizes[2] - record.city.length();
			std::cout << "|";
			for (int j = 0; j < toFill / 2; j++)
			{
				std::cout << " ";
			}
			std::cout << record.city;
			if (toFill % 2 == 1)
				toFill += 1;
			for (int j = 0; j < toFill / 2; j++)
			{
				std::cout << " ";
			}

			toFill = maxSizes[3] - record.street.length();
			std::cout << "|";
			for (int j = 0; j < toFill / 2; j++)
			{
				std::cout << " ";
			}
			std::cout << record.street;
			if (toFill % 2 == 1)
				toFill += 1;
			for (int j = 0; j < toFill / 2; j++)
			{
				std::cout << " ";
			}

			toFill = maxSizes[4] - record.contactPerson.length();
			std::cout << "|";
			for (int j = 0; j < toFill / 2; j++)
			{
				std::cout << " ";
			}
			std::cout << record.contactPerson;
			if (toFill % 2 == 1)
				toFill += 1;
			for (int j = 0; j < toFill / 2; j++)
			{
				std::cout << " ";
			}

			toFill = maxSizes[5] - record.mail.length();
			std::cout << "|";
			for (int j = 0; j < toFill / 2; j++)
			{
				std::cout << " ";
			}
			std::cout << record.mail;
			if (toFill % 2 == 1)
				toFill += 1;
			for (int j = 0; j < toFill / 2; j++)
			{
				std::cout << " ";
			}

			toFill = maxSizes[6] - record.phone.length();
			std::cout << "|";
			for (int j = 0; j < toFill / 2; j++)
			{
				std::cout << " ";
			}
			std::cout << record.phone;
			if (toFill % 2 == 1)
				toFill += 1;
			for (int j = 0; j < toFill / 2; j++)
			{
				std::cout << " ";
			}
			std::cout << "|";
			std::cout << std::endl;
			// line
			for (int i = 0; i < 7; i++)
			{
				std::cout << "+";
				for (int j = 0; j < maxSizes[i]; j++)
				{
					std::cout << "-";
				}
			}
			std::cout << "+";
			std::cout << std::endl;
			//end of line
		}
		// end of data

		_getch();
	}
	else
	{
		_getch();
	}
}
void Database::insert(Console * console)
{
	std::string firmName;
	std::string postalCode;
	std::string city;
	std::string street;
	std::string contactPerson;
	std::string mail;
	std::string phone;

	console->clear();
	console->showConsoleCursor(true);

	std::cout << "Podaj nazwe firmy:";
	std::getline(std::cin, firmName);
	std::cout << "Podaj kod pocztowy:";
	std::getline(std::cin, postalCode);
	std::cout << "Podaj miasto:";
	std::getline(std::cin, city);
	std::cout << "Podaj ulice:";
	std::getline(std::cin, street);
	std::cout << "Podaj osobe do kontaktu:";
	std::getline(std::cin, contactPerson);
	std::cout << "Podaj adres e-mail:";
	std::getline(std::cin, mail);
	std::cout << "Podaj numer telefonu:";
	std::getline(std::cin, phone);
	
	std::cout << "Pomyslnie wprowadzono dane" << std::endl;
	_getch();

	Record * record = new Record(firmName, postalCode, city, street, contactPerson, mail, phone);

	std::ofstream file;
	file.open(path, std::ios_base::app);

	file << record->toString();
	file << std::endl;
}
void Database::remove(Console * console, std::string fieldName, std::string value)
{
	int howMuchRemoved = 0;
	std::vector <Record> tempRecords(records); // create a copy of existing records
	if (fieldName == "Nazwa firmy")
	{
		for (int i = 0; i < tempRecords.size(); i++)
		{
			Record record = tempRecords.at(i);
			if (record.firmName == value)
			{
				tempRecords.erase(tempRecords.begin() + i);
				howMuchRemoved++;
				i = 0;
			}
		}
		
		if (tempRecords.size() >0 && tempRecords.at(0).firmName == value)
		{
			tempRecords.erase(tempRecords.begin() + 1);
			howMuchRemoved++;
		}
	}
	else if (fieldName == "Kod pocztowy")
	{
		for (int i = 0; i < tempRecords.size(); i++)
		{
			Record record = tempRecords.at(i);
			if (record.postalCode == value)
			{
				tempRecords.erase(tempRecords.begin() + i);
				i = 0;
				howMuchRemoved++;
			}
		}
		if (tempRecords.size() >0 && tempRecords.at(0).postalCode == value)
		{
			tempRecords.erase(tempRecords.begin() + 1);
			howMuchRemoved++;
		}
	}
	else if (fieldName == "Miasto")
	{
		for (int i = 0; i < tempRecords.size(); i++)
		{
			Record record = tempRecords.at(i);
			if (record.city == value)
			{
				tempRecords.erase(tempRecords.begin() + i);
				i = 0;
				howMuchRemoved++;
			}
		}
		if (tempRecords.size() >0 && tempRecords.at(0).city == value)
		{
			tempRecords.erase(tempRecords.begin() + 1);
			howMuchRemoved++;
		}
	}
	else if (fieldName == "Ulica")
	{
		for (int i = 0; i < tempRecords.size(); i++)
		{
			Record record = tempRecords.at(i);
			if (record.street == value)
			{
				tempRecords.erase(tempRecords.begin() + i);
				i = 0;
				howMuchRemoved++;
			}
		}
		if (tempRecords.size() >0 && tempRecords.at(0).street == value)
		{
			tempRecords.erase(tempRecords.begin() + 1);
			howMuchRemoved++;
		}
	}
	else if (fieldName == "Osoba do kontaktu")
	{
		for (int i = 0; i < tempRecords.size(); i++)
		{
			Record record = tempRecords.at(i);
			if (record.contactPerson == value)
			{
				tempRecords.erase(tempRecords.begin() + i);
				i = 0;
				howMuchRemoved++;
			}
		}
		if (tempRecords.size() >0 && tempRecords.at(0).contactPerson == value)
		{
			tempRecords.erase(tempRecords.begin() + 1);
			howMuchRemoved++;
		}
	}
	else if (fieldName == "Mail")
	{
		for (int i = 0; i < tempRecords.size(); i++)
		{
			Record record = tempRecords.at(i);
			if (record.mail == value)
			{
				tempRecords.erase(tempRecords.begin() + i);
				i = 0;
				howMuchRemoved++;
			}
		}
		if (tempRecords.size() >0 && tempRecords.at(0).mail == value)
		{
			tempRecords.erase(tempRecords.begin() + 1);
			howMuchRemoved++;
		}
	}
	else if (fieldName == "Telefon")
	{
		for (int i = 0; i < tempRecords.size(); i++)
		{
			Record record = tempRecords.at(i);
			if (record.phone == value)
			{
				tempRecords.erase(tempRecords.begin() + i);
				i = 0;
				howMuchRemoved++;
			}
		}
		if (tempRecords.size() >0 && tempRecords.at(0).phone == value)
		{
			tempRecords.erase(tempRecords.begin() + 1);
			howMuchRemoved++;
		}
	}
	else
	{
		console->clear();
		console->setColor("red", "black");
		std::cout << "Nie ma kolumny o takiej nazwie.";
		console->setColor("white", "black");
		return;
	}
	console->clear();
	console->setColor("yellow", "black");
	std::cout << "Liczba usunietych rekordow: "<<howMuchRemoved;
	console->setColor("white", "black");
	records = tempRecords;
	overwrite();
}
