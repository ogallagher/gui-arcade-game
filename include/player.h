/*

Owen Gallagher
17 March 2019
Computer Graphics

Class to display the player's avatar and keep track of related info.

*/

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "bullet.h"

using namespace std;

class Player {
private:
	static double thrust;
	static double torque;

	double h; //heading
	double hv; //delta heading
	vector<double> l; //location
	vector<double> v; //velocity
	vector<double> a; //acceleration
	float r,g,b;
	
	bool propelling;

public:
	static int size;
	int score;

	Player(int frustumSize);

	vector<double> getL() {return l;};
	
	void move(int frustumSize);
	void rotate(double angle);
	void propel(double power);
	void control(unsigned char key);
	void stop(unsigned char key);
	Bullet shoot(); //returns heading of the bullet
	bool collide(Enemy *e);
	void display(int frustumSize);
	void reset(int frustumSize);
};

#endif