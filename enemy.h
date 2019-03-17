/*

Owen Gallagher
17 March 2019
Computer Graphics

Class representing enemy 

*/

#include <vector>

#include "player.h"

using namespace std;

class Enemy {
private:
	int x;
	int y;
	vector<double> v;
	
public:
	Enemy(int x, int y, vector<double> v);
	void move(Player &p);
	void destroy();
	void draw();
};