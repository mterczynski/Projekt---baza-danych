#pragma once
#include "Console.h"
#include "Record.h"
#include <fstream>
#include <vector>
class Database
{
private:
	std::string path;
	std::vector <Record> records;
public:
	Database();
	Database(std::string path);
	~Database();
	void removeAll(Console * console);
	void overwrite();
	void loadFromFile();
	void reload();
	void select(Console *, std::string fieldName, std::string value);
	void selectAll(Console *);
	void insert(Console *);
	void remove(Console *, std::string fieldName, std::string value);
};

