#include <iostream>
#include<gl/freeglut.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "Obiect.h"
#include "Pamant.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "Lac.h"

using namespace std;

// angle of rotation for the camera direction
float angle = M_PI / 2;
// actual vector representing the camera's direction
float lx = sin(angle), lz = -cos(angle);
// XZ position of the camera
float x = -60.0f, z = 0.0f;



Pamant* pamant;
Lac* lac;

void construiesteScena() {
	pamant = new Pamant(-500, 0, -500, 1000, 1000);
	lac = new Lac({0, 0.1f, 0}, 20, { 51, 51, 255 });
}


void init(void)
{
	glClearColor(0.001f, 0.53f, 0.98f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	//glOrtho(-20.0, 1500, 0.0, 900.0, -1.0, 1.0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);

	construiesteScena();

	glEnable(GL_TEXTURE_2D);

}


void changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 300.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


void drawSnowMan() {

	glColor3f(0, 0, 0);

	// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.5f, 20, 20);

}



void renderScene(void) {

	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, 20.0f, z,
		x + lx, 20.0f, z + lz,
		0.0f, 1.0f, 0.0f);

	pamant->render();
	lac->render();

	// Draw 36 SnowMen
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i * 10.0, 0, j * 10.0);
			drawSnowMan();
			glPopMatrix();
		}

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{

	switch (key) {
	case 'l':
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;

	}
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 10.0f;

	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.1f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}
}


int main(int argc, char** argv) {

	srand(time(NULL));

	// init GLUT and create window

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1600, 900);
	glutCreateWindow("Proiect 3D - Pe balta cu FMI");

	init();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}