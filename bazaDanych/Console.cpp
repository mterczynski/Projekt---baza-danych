#include "stdafx.h"
#include "Console.h"
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <cwchar>

//----------- Getters: -------------------------------
int Console::getColor()
{
	return this->color;
};
COORD Console::getCursorPos()
{
	return this->cursorPos;
}
//----------- Setters: -------------------------------
void Console::setColor(int c)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, c);
	this->color = c;
}
void Console::setColor(std::string font, std::string background)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::string colors[] = { "black", "darkblue","darkgreen","darkcyan","darkred","darkmagenta","olive","grey","darkgrey","blue","green","cyan","red","magenta","yellow","white" };
	int fontIndex = -1;
	int backgroundIndex = -1;
	for (int i = 0; i < 16; i++)
	{
		if (font == colors[i])
		{
			fontIndex = i;
		}
		if (background == colors[i])
		{
			backgroundIndex = i;
		}
	}
	this->color = fontIndex + 16 * backgroundIndex;
	SetConsoleTextAttribute(hOut, fontIndex + 16 * backgroundIndex);
}
void Console::setCursor(int x, int y)
{
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}
void Console::setCursor(COORD pos)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}
void Console::setFontSize(int fontSize) 
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = fontSize;            // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_MEDIUM;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
//----------- Others: -------------------------------
void Console::colorInfo()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 255; i++)
	{
		SetConsoleTextAttribute(hOut, i);
		std::cout << i << std::endl;
	}
}
void Console::showConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
void Console::clear()
{
	system("cls");
}
void Console::drawRect(COORD pos, int width, int height, std::string bgColor)
{
	int oldColor = this->getColor();
	this->setColor(bgColor, bgColor);
	this->setCursor(pos);
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	this->setColor(oldColor);
}



