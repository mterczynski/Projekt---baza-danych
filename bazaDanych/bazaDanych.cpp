// bazaDanych.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Console.h"
#include "Database.h"
#include <conio.h>
#include <iostream>
#include <string>

//using namespace std;

void renderMenu(std::string menu[], int selectedIndex, Console * console)
{
	int menuSize = sizeof(menu) / sizeof(*menu);

	std::cout << menuSize;
	//system("cls");

	for (int i = 0; i < menuSize; i++)
	{
		if (i == selectedIndex)
		{
			console->setColor("cyan", "darkblue");
			std::cout << menu[i] << std::endl;
			console->setColor("white", "black");
		}
		else
		{
			std::cout << menu[i] << std::endl;
		}
	}
} // not working

int main()
{

	/*HANDLE buff = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD sizeOfBuff;
	sizeOfBuff.X = 10;
	sizeOfBuff.Y = 150;
	SetConsoleScreenBufferSize(buff, sizeOfBuff);*/
	HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int width = 600;
	int height = 300;
	SMALL_RECT r;
	COORD      c;
	r.Left =
		r.Top = 0;
	r.Right = width - 1;
	r.Bottom = height - 1;
	SetConsoleWindowInfo(hConOut, TRUE, &r);

	c.X = width;
	c.Y = height;
	SetConsoleScreenBufferSize(hConOut, c);

	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) { SetWindowPos(hwnd, 0, 0, 0, 1500, 600, SWP_SHOWWINDOW | SWP_NOMOVE); }




	Console * console = new Console();
	Database * db = new Database("plik.txt");
	db->loadFromFile();

	int selectedIndex = 0;
	int menuSize = 5;
	std::string fieldNames[7] = { "Nazwa firmy","Kod pocztowy","Miasto","Ulica","Osoba do kontaktu","Mail","Telefon" };
	std::string options[] = {"","","","",""};

	options[0] = "Dodaj nowy wpis";
	options[1] = "Wyszukaj";
	options[2] = "Usun dane";
	options[3] = "Wyswietl wszystko";
	options[4] = "Usun wszystko";

	console->showConsoleCursor(false);
	console->setFontSize(40);

	for (int i = 0; i < menuSize; i++)
	{
		if (i == selectedIndex)
		{
			console->setColor("cyan", "darkblue");
			std::cout << options[i] << std::endl;
			console->setColor("white", "black");
		}
		else
		{
			std::cout << options[i] << std::endl;
		}
	}
	while (true)
	{
		switch (_getch())
		{
		case 13: // Enter
			std::cout << "Wcisnieto enter" << std::endl;
			switch (selectedIndex)
			{
			case 0:
				db->insert(console);
				break;
			case 1:
			{
				console->clear();
				console->setFontSize(25);
				console->showConsoleCursor(true);
				std::string fieldName;
				std::string value;

				std::cout << "[";
				for (int i = 0; i < 6; i++)
				{
					std::cout << fieldNames[i] << ",";
				}
				std::cout << fieldNames[6];
				std::cout << "]";
				std::cout << std::endl;

				console->setColor("yellow", "black");
				std::cout << "Przyklad: Wyswietl dane gdzie Osoba do kontaktu";
				std::cout << std::endl;
				console->setColor("white", "black");

				std::cout << "Wyswietl dane gdzie ";
				std::getline(std::cin, fieldName);
				console->clear();

				console->setColor("yellow", "black");
				std::cout << "Przyklad: Wyswietl dane gdzie Osoba do kontaktu = Jan Kowalski";
				std::cout << std::endl;
				console->setColor("white", "black");

				std::cout << "Wyswietl dane gdzie "<< fieldName<<" = ";
				std::getline(std::cin, value);
				db->select(console, fieldName, value);

				_getch();
				break;
			}
			case 2: 
			{
				console->clear();
				console->setFontSize(25);
				console->showConsoleCursor(true);
				std::string fieldName;
				std::string value;

				std::cout << "[";
				for (int i = 0; i < 6; i++)
				{
					std::cout << fieldNames[i] << ",";
				}
				std::cout << fieldNames[6];
				std::cout << "]";
				std::cout << std::endl;

				console->setColor("yellow", "black");
				std::cout << "Przyklad: Usun dane gdzie Osoba do kontaktu";
				std::cout << std::endl;
				console->setColor("white", "black");

				std::cout << "Usun dane gdzie ";
				std::getline(std::cin, fieldName);
				console->clear();

				console->setColor("yellow", "black");
				std::cout << "Przyklad: Usun dane gdzie Osoba do kontaktu = Jan Kowalski";
				std::cout << std::endl;
				console->setColor("white", "black");

				std::cout << "Usun dane gdzie " << fieldName << " = ";
				std::getline(std::cin, value);
				db->remove(console, fieldName, value);

				_getch();
				break;
			}
			case 3:
			{
				db->selectAll(console);
				break;
			}	
			case 4:
			{
				db->removeAll(console);
				break;
			}
				
		}
			console->clear();
			console->showConsoleCursor(false);
			console->setFontSize(40);
			selectedIndex = 0;
			db->reload();
			for (int i = 0; i < menuSize; i++)
			{
				if (i == selectedIndex)
				{
					console->setColor("cyan", "darkblue");
					std::cout << options[i] << std::endl;
					console->setColor("white", "black");
				}
				else
				{
					std::cout << options[i] << std::endl;
				}
			}
			break;
		case 224: // Special
			switch (_getch())
			{
			case 72: // Arrow Up
				selectedIndex--;
				if (selectedIndex < 0)
					selectedIndex = menuSize - 1;
				console->setCursor(0, 0);
				for (int i = 0; i < menuSize; i++)
				{
					if (i == selectedIndex)
					{
						console->setColor("cyan", "darkblue");
						std::cout << options[i] << std::endl;
						console->setColor("white", "black");
					}
					else
					{
						std::cout << options[i] << std::endl;
					}
				}
				break;
				break;
			case 80: // Arrow Down
				selectedIndex++;
				if (selectedIndex > menuSize-1)
					selectedIndex = 0;
				console->setCursor(0, 0);
				for (int i = 0; i < menuSize; i++)
				{
					if (i == selectedIndex)
					{
						console->setColor("cyan", "darkblue");
						std::cout << options[i] << std::endl;
						console->setColor("white", "black");
					}
					else
					{
						std::cout << options[i] << std::endl;
					}
				}
				break;
			}
		}
	}
	
	_getch();
	delete console;
    return 0;
}

