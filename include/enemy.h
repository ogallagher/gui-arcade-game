/*

Owen Gallagher
17 March 2019
Computer Graphics

Class representing enemy 

*/

#ifndef ENEMY_H
#define ENEMY_H

#include <vector>

//#include "player.h" this creates a circular dependency, so I can instead forward-declare player
class Player;

using namespace std;

class Enemy {
private:
	vector<double> l;
	vector<double> v;
	float r,g,b;
	Player *player;
	bool dead;
	double speed;
	
public:
	static int size;

	vector<double> getL() {return l;};

	Enemy(int x=0, int y=0, Player *p=nullptr);
	bool move(int frustumSize); //returns false if dead
	void setV(double x, double y); //given a unit vector
	void die();
	void display(int frustumSize);
};

#endif