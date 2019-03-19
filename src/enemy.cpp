#if defined(__APPLE__)

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

#else

#include <GL/glut.h>

#endif

#include <iostream>

#include "../include/enemy.h"

int Enemy::size = 20;

Enemy::Enemy(int x, int y, Player *p) {
	l.assign(2,0);
	v.assign(2,0);
	speed = 0.03;
	dead = false;

	r = 1;
	g = 0.8;
	b = 0;

	l[0] = x;
	l[1] = y;
	player = p;
}

bool Enemy::move(int frustumSize) {
	if (dead) {
		return false;
	}
	else {
		l[0] += v[0];
		l[1] += v[1];

		if (l[0] < -size*2) {
			l[0] = frustumSize;
		}
		if (l[0] > frustumSize + size*2) {
			l[0] = 0;
		}
		if (l[1] < -size*2) {
			l[1] = frustumSize;
		}
		if (l[1] > frustumSize + size*2) {
			l[1] = 0;
		}
	}
	
	return true;
}

void Enemy::setV(double ux, double uy) {
	v[0] = ux * speed;
	v[1] = uy * speed;
}

void Enemy::die() {
	dead = true;
}

void Enemy::display(int frustumSize) {
	glPushMatrix();

	glTranslated(l[0],l[1],0);
	glRotated(0,0,0,1);
	glScaled(size,size,1);

	glColor3f(r,g,b);
	glBegin(GL_POLYGON);
		glVertex2f(0,1);
		glVertex2f(1,0);
		glVertex2f(0,-1);
		glVertex2f(-1,0);
	glEnd();

	glPopMatrix();
}