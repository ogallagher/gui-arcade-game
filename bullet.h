/*

Owen Gallagher
17 March 2019
Computer Graphics

*/

#include <vector>

#include "enemy.h"

using namespace std;

class Bullet {
private:
	int x;
	int y;
	vector<double> v;
	
public:
	Bullet(int x, int y, vector<double> v);
	void move();
	void collide(Enemy &e);
	void draw();
};