#include <GL/glut.h>
#include <iostream>

#include "../include/button.h"

using namespace std;

Button::Button(int x, int y, int w, int h, string text) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->text = text;
	this->hovered = false;
	
	const int tlen = text.length();
	unsigned char *chars = new unsigned char[tlen];
	for (int i=0; i<tlen; i++) {
		chars[i] = text.at(i);
	}

	//tw = glutBitmapLength(GLUT_BITMAP_8_BY_13,chars);
	cout << "(" << text.c_str() << ") button.width = " << tw << endl;
}

void Button::hover(int mX, int mY) {
	if (mX >= x && mX <= x+w && mY >= y && mY <= y+h) {
		hovered = true;
	}
	else {
		hovered = false;
	}

	//cout << "hover check: " << x << "<" << mX << "<" << x+w << "," << y << "<" << mY << "<" << y+h << endl;
}

bool Button::click() {
	return hovered;
}

void Button::display(int frustumSize) {
	//rectangle
	if (hovered) {
		glColor3f(0.5,0.5,0.5);
	}
	else {
		glColor3f(0.2,0.2,0.2);
	}
	glRectd(x, y, x+w, y+h);//x1,y1,x2,y2
	
	//text
	//glRasterPos2f(0,0);
	//glColor3f(0,0,0);
	//
	//int tlen = text.length();
	//for (int i=0; i<tlen; i++) {
	//	glutBitmapCharacter(GLUT_BITMAP_8_BY_13,text[i]);
	//}
}