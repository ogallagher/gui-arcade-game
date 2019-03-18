#include <GL/glut.h>

#include "../include/bullet.h"

int Bullet::size = 5;
double Bullet::speed = 0.16;
int Bullet::length = 10;

Bullet::Bullet(vector<double> l, double h) {
	v.assign(2,0);

	this->l = l;
	
	setV(h);
}

Bullet::Bullet(int x, int y, double h) {
	v.assign(2,0);

	l[0] = x;
	l[1] = y;

	setV(h);
}

void Bullet::setV(double heading) {
	v[0] = cos(heading) * speed;
	v[1] = sin(heading) * speed;
}

void Bullet::move() {
	l[0] += v[0];
	l[1] += v[1];
}

bool Bullet::collide(Enemy *e) {
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

bool Bullet::display(int frustumSize) {
	if (l[0] < 0 || l[0] > frustumSize || l[1] < 0 || l[1] > frustumSize) {
		return false;
	}
	
	glPushMatrix();

	glTranslated(l[0],l[1],0);
	glRotated(0,0,0,1);
	glScaled(size,size,1);

	glColor3f(1,1,1);
	glBegin(GL_LINES);
		glVertex2f(-v[0]/speed * 1, -v[1] / speed * 1);
		glVertex2f(v[0] / speed * 1, v[1] / speed * 1);
	glEnd();

	glPopMatrix();

	return true;
}