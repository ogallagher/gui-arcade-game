#include <GL/glut.h>

#include "player.h"

Player::Player() {
	x = 0;
	y = 0;
	r = 1;
	g = 0;
	b = 0;
}

void Player::display(int frustumSize) {
	glColor3f(r,g,b);
	glBegin(GL_POLYGON);
		glVertex2f(frustumSize/8,frustumSize/8);
		glVertex2f(3*frustumSize/8,frustumSize/8);
		glVertex2f(3*frustumSize/8,3*frustumSize/8);
		glVertex2f(frustumSize/8,3*frustumSize/8);
	glEnd();
}