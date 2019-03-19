#if defined(__APPLE__)

#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>

#else

#include <GL/glut.h>

#endif

#define USE_MATH_DEFINES_
#include <cmath>
#include <iostream>

#include "../include/omath.h"
#include "../include/player.h"
#include "../include/bullet.h"

using namespace std;

int Player::size = 10;
double Player::thrust = 0.0001;
double Player::torque = 0.003;

Player::Player(int frustumSize) {
	size *= frustumSize/400.0;

	h = 3.141592*0.5; //set heading to point up (pi/2)
	hv = 0;

	l.push_back(frustumSize/2); //location, velocity, and acceleration
	l.push_back(size * 5);
	v.assign(2,0);
	a.assign(2,0);

	r = 1;
	g = 0;
	b = 0;

	score = 0;

	propelling = false;
}

void Player::move(int frustumSize) {
	h += hv;

	v[0] += a[0];
	v[1] += a[1];

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

void Player::rotate(double angle) {
	hv = angle;
}

void Player::propel(double power) {
	propelling = true;
	a[0] = cos(h) * power;
	a[1] = sin(h) * power;
}

void Player::control(unsigned char key) {
	switch (key) {
	//left
	case 'A':
	case 'a':
		rotate(torque);
		a.assign(2,0);
		break;

	//up
	case 'W':
	case 'w':
		propel(thrust);
		hv = 0;
		break;

	//right
	case 'D':
	case 'd':
		rotate(-torque);
		a.assign(2,0);
		break;

	//down
	case 'S':
	case 's':
		propel(-thrust);
		hv = 0;
		break;
	}
}

void Player::stop(unsigned char key) {
	switch (key) {
	//left or right
	case 'A':
	case 'a':
	case 'D':
	case 'd':
		hv = 0;
		break;

	//up or down
	case 'W':
	case 'w':
	case 'S':
	case 's':
		propelling = false;
		a.assign(2,0);
		break;
	}
}

//fire bullet
Bullet Player::shoot() {
	vector<double> bl;
	bl.push_back(l[0] + cos(h)*size);
	bl.push_back(l[1] + sin(h)*size);

	return Bullet(bl,h);
}

bool Player::collide(Enemy *e) {
	vector<double> difference = e->getL();
	difference[0] -= l[0];
	difference[1] -= l[1];

	float distance = sqrt(difference[0]*difference[0] + difference[1]*difference[1]);
	if (distance < size+Enemy::size) {
		e->die();
		return true;
	}
	else {
		return false;
	}
}

void Player::display(int frustumSize) {
	glPushMatrix();

	glTranslated(l[0],l[1],0);
	glRotated(h*OMath::rad2deg - 90.0,0,0,1);
	glScaled(size,size,1);

	glColor3f(r,g,b);
	glBegin(GL_POLYGON);
		glVertex2f(0,1);
		glVertex2f(0.5,-0.5);
		glVertex2f(0,-0.25);
		glVertex2f(-0.5,-0.5);
	glEnd();

	if (propelling) {
		glColor3f(1,1,1);
		glBegin(GL_POLYGON);
			glVertex2f(0,-0.8);
			glVertex2f(0.2,-1);
			glVertex2f(0,-1.2);
			glVertex2f(-0.2,-1);
		glEnd();
	}

	glPopMatrix();
}

void Player::reset(int frustumSize) {
	l[0] = frustumSize/2;
	l[1] = size * 5;

	v.assign(2,0);
	a.assign(2,0);
	score = 0;
	h = 3.141592*0.5;
	hv = 0;
	propelling = false;
}