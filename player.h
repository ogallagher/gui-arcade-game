#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
	double x;
	double y;
	float r;
	float g;
	float b;

public:
	Player();
	
	void display(int frustumSize);
};

#endif