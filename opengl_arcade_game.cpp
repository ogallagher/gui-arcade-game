/*

Owen Gallagher
7 March 2019
Computer Graphics

Submission for the 2D OpenGL arcade game.

*/

#include <GL/glut.h>
#include <iostream>

#include "player.h"

using namespace std;

int windowSize = 400;
int viewportSize = windowSize;
int frustumSize = viewportSize;

Player player;

void onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.4f,0.0f,0.8f);
	glBegin(GL_LINE_LOOP);
		glVertex2f(frustumSize/4,frustumSize/4);
		glVertex2f(3*frustumSize/4,frustumSize/4);
		glVertex2f(3*frustumSize/4,3*frustumSize/4);
		glVertex2f(frustumSize/4,3*frustumSize/4);
	glEnd();

	player.display(frustumSize);

	glFlush();

	cout << "onDisplay()" << endl;
}

void onReshape(int w, int h) {
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
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowSize,windowSize);
	glutInitWindowPosition(100.0,100.0);
	glutCreateWindow("Owen Arcade Game");
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onReshape);
}

int main(int argc, char **argv) {
	initWindow(argc,argv);

	initGraphics();

	cout << "glutMainLoop()" << endl;
	glutMainLoop();

	cout << "exit()" << endl;
	char dummy;
	cin >> dummy;
	return 0;
}