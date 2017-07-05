#pragma once
#include <iostream>
#include <string.h>
#include <Windows.h>
class Console
{
private:
	COORD cursorPos = { 0,0 };
	int color = 0;
	int arrowMaring = 21;
public:
	Console() {};
	~Console() {};
//getters:
	int getColor();
	COORD getCursorPos();
//setters:
	void setColor(int);
	void setColor(std::string font, std::string background);
	void setCursor(int, int);
	void setCursor(COORD pos);
	void setFontSize(int);
//others:
	void colorInfo();
	void showConsoleCursor(bool showFlag);
	void clear();
	void drawRect(COORD, int, int, std::string);
};

