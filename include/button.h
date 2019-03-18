/*

Owen Gallagher
17 March 2019
Computer Graphics

Class for a GUI button

*/

#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>

using namespace std;

class Button {
private:
	int x;
	int y;
	int w;
	int h;
	string text;
	int tw;
	bool hovered;
	
public:
	Button(int x, int y, int w, int h, string text);
	void hover(int mX, int mY); //sets whether the button is touched
	bool click(); //returns true if clicked
	void display(int frustumSize);
};

#endif