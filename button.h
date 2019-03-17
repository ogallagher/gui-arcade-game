/*

Owen Gallagher
17 March 2019
Computer Graphics

Class for a GUI button

*/

#include <iostream>

class Button {
private:
	int x;
	int y;
	int w;
	int h;
	string text;
	//hovered
	
public:
	bool hover(int mX, int mY); //returns whether the button is touched
	bool click(int mX, int mY); //returns whether the button is clicked
};