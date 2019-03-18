/*

Owen Gallagher
7 March 2019
Computer Graphics

Submission for the 2D OpenGL arcade game.
This file is the program executable.

*/

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <ctime>

#include "../include/player.h"
#include "../include/bullet.h"
#include "../include/enemy.h"

#include "../include/button.h"

using namespace std;

#define INIT_PAUSE 30

int windowWidth = 400;
int windowHeight = 400;
int viewportSize = windowWidth;
int frustumSize = viewportSize;

const int SCREEN_START = 0;
const int SCREEN_PLAY = 1;
const int SCREEN_OVER = 2;
int screen; //keeps track of current game state

time_t then = time(NULL);
time_t now = then;
int timer = 0;
float pause = INIT_PAUSE; //time between enemy spawns

Player player(frustumSize);
vector<Bullet> bullets;
vector<Enemy> enemies;
Button buttonStart(0,frustumSize-50,frustumSize,50,"start");
Button buttonAgain(0,0,frustumSize,50,"again");

void newEnemy() {
	float h = (rand() % 1000)/1000.0 * 3.141592654 * 2;
	int r = frustumSize/2;
	int x = r + cos(h) * (r + Enemy::size);
	int y = r + sin(h) * (r + Enemy::size);

	Enemy e(x,y,&player);

	double rx = player.getL()[0];
	double ry = player.getL()[1];

	rx -= x;
	ry -= y;

	double mag = sqrt(rx*rx + ry*ry);
	rx /= mag;
	ry /= mag;

	e.setV(rx,ry);

	enemies.push_back(e);
}

void reset() {
	player.reset(frustumSize);
	enemies.clear();
	bullets.clear();

	timer = 0;
	pause = INIT_PAUSE;
	now = time(NULL);
	then = now; 

	cout << "New game" << endl;
}

void onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	int elen = enemies.size();
	int blen = bullets.size();
	bool collided = false;

	switch (screen) {
		case SCREEN_START:
			//draw title
		
			//draw start button
			buttonStart.display(frustumSize);
			break;
			
		case SCREEN_PLAY:
			//update and draw bullets
			for (int i=0; i<blen; i++) {
				bullets[i].move();

				if (!bullets[i].display(frustumSize)) {
					bullets.erase(bullets.begin()+i);
					blen--;
					i--;
				}
				else {
					collided = false;

					for (int j=0; j<elen && !collided; j++) {
						if (bullets[i].collide(&enemies[j])) {
							collided = true;

							bullets.erase(bullets.begin()+i);
							blen--;
							i--;
						}
					}
				}
			}
	
			//update and draw player
			player.move(frustumSize);
			collided = false;
			for (int j=0; j<elen && !collided; j++) {
				if (player.collide(&enemies[j])) {
					collided = true;

					screen = SCREEN_OVER;
					cout << "Final score: " << player.score << endl << endl;
				}
			}

			player.display(frustumSize);
	
			//update and draw enemies and update score
			for (int i=0; i<elen; i++) {
				if (enemies[i].move(frustumSize)) {
					enemies[i].display(frustumSize);
				}
				else {
					player.score++;
					cout << "Score: " << player.score << endl;
					enemies.erase(enemies.begin()+i);
					i--;
					elen--;
				}
			}

			//create new enemies
			now = time(NULL);
			timer += difftime(now,then);
			then = now;
			if (timer > pause || elen == 0) {
				newEnemy();

				timer = 0;
				
				if (pause > 0.5) {
					pause *= 0.9;
				}
			}
	
			//print score
			break;
		
		case SCREEN_OVER:
			//draw game over
		
			//draw again button
			buttonAgain.display(frustumSize);
		
			//print score
			
			break;
			
		default:
			break; //do nothing
	}

	glFlush();

	glutPostRedisplay();
}

void onReshape(int w, int h) {
	//update window dimensions
	windowWidth = w;
	windowHeight = h;

	//viewport matches window
	glViewport(0,0,w,h);

	//clipping volume maintains aspect ratio and central position
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	int frustumCenter = frustumSize/2;

	if (w<h) {
		int adjusted = (double)h/(double)w*frustumCenter;
		gluOrtho2D(0, frustumSize, frustumCenter- adjusted, frustumCenter + adjusted);
	}
	else {
		int adjusted = (double)w/(double)h*frustumCenter;
		gluOrtho2D(frustumCenter - adjusted, frustumCenter + adjusted, 0, frustumSize);
	}

	glMatrixMode(GL_MODELVIEW);
}

//handle clicks for widget select detection
void onClick(int button, int status, int x, int y) {
	if (status == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			if (screen == SCREEN_START) {
				if (buttonStart.click()) {
					screen = SCREEN_PLAY;
				}
			}
			else if (screen == SCREEN_OVER) {
				if (buttonAgain.click()) {
					reset();
					screen = SCREEN_PLAY;
				}
			}
		}
	}
}

//handle mouse movement for widget hover detection
void onHover(int x, int y) {
	y = windowHeight - y - 9;

	if (windowHeight < windowWidth) {
		x = (x - (windowWidth-windowHeight)/2.0) / windowHeight * frustumSize;
		y = frustumSize * y/windowHeight;
	}
	else {
		x = frustumSize * x/windowWidth;
		y = (y - (windowHeight-windowWidth)/2.0) / windowWidth * frustumSize;
	}

	if (screen == SCREEN_START) {
		buttonStart.hover(x,y);
	}
	else if (screen == SCREEN_OVER) {
		buttonAgain.hover(x,y);
	}
}

//handle key presses
void onKeyDown(unsigned char key, int x, int y) {
	if (screen == SCREEN_PLAY) {
		player.control(key);
	}
}

void onKeyUp(unsigned char key, int x, int y) {
	if (screen == SCREEN_PLAY) {
		if (key == ' ') { //fire bullet
			bullets.push_back(player.shoot());
		}
		else {
			player.stop(key);
		}
	}
}

void initGraphics() {
	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(0.0,0.0,0.0);

	glMatrixMode(GL_PROJECTION);
	glViewport(0,0,viewportSize,viewportSize);
	glLoadIdentity();
	gluOrtho2D(0,frustumSize,0,frustumSize);
	glMatrixMode(GL_MODELVIEW);
}

void initWindow(int argc, char **argv) {
	//glut window
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitWindowPosition(100.0,100.0);
	glutCreateWindow("Owen Arcade Game");

	//glut event handlers
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onReshape);
	glutMouseFunc(onClick);
	glutPassiveMotionFunc(onHover);
	glutKeyboardFunc(onKeyDown);
	glutKeyboardUpFunc(onKeyUp);
}

int main(int argc, char **argv) {
	initWindow(argc,argv);

	initGraphics();

	screen = SCREEN_START;
	cout << "Directions:" << endl
		 << "\tTo start, click the gray button at the top (ideally it\'ll have a START label)" << endl
		 << "\tTo control your ship, use WASD keys, and SPACE to shoot" << endl
		 << "\tStay alive as long as possible without hitting enemies" << endl;

	cout << "glutMainLoop()" << endl;

	newEnemy();

	glutMainLoop();

	return 0;
}