/*

Owen Gallagher
17 March 2019
Computer Graphics

*/

#ifndef BULLET_H
#define BULLET_H

#include <vector>

#include "enemy.h"

using namespace std;

class Bullet {
private:
	static double speed;
	static int length;

	vector<double> l;
	vector<double> v;
	
public:
	static int size;

	Bullet(vector<double> l, double h);
	Bullet(int x, int y, double h);

	vector<double> getL() {return l;};

	void setV(double heading);
	void move();
	bool collide(Enemy *e); //returns true if there is a collision
	bool display(int frustumSize); //returns false if invisible
};

#endif