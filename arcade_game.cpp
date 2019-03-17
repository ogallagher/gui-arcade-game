/*

Owen Gallagher
17 March 2019
Computer Graphics

This is a draft of the part of the executable file that handles the game logic.

*/

#include <iostream>
#include <vector> //TODO: check this

#include "player.h"
#include "bullet.h"
#include "enemy.h"

#include "button.h"

using namespace std;

const int SCREEN_START = 0;
const int SCREEN_PLAY = 1;
const int SCREEN_OVER = 2;
int screen; //keeps track of current game state

Player player;
vector<Enemy> enemies;
vector<Bullet> bullets;

//callback for glut redraw event
void onDraw() {
	switch (screen) {
		case SCREEN_START:
			//draw title
		
			//draw start button
			break;
			
		case SCREEN_PLAY:
			//update and draw bullets
	
			//update and draw player
	
			//update and draw enemies
	
			//print score
			break;
		
		case SCREEN_OVER:
			//draw game over
		
			//draw again button
		
			//print score
			break;
			
		default:
			break; //do nothing
	}
}

//handle clicks to UI buttons START and AGAIN
void onClick(int mX, int mY) {
	
}

int main(/*standard args*/) {
	//init opengl
	
	//init glut
	
	//handle glut events (window resize, click, redraw, etc)
	
	screen = SCREEN_START;
	bullets = new vector<Bullet>();
	enemies = new vector<Enemy>();
	
	glutMainLoop();
	
	exit();
}