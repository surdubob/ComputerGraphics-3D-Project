#include <iostream>
#include<gl/freeglut.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "Obiect.h"
#include "Pamant.h"
#include <cstring>

#define _USE_MATH_DEFINES
#include <math.h>

#include "Camera.h"
#include "Lac.h"

using namespace std;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f;

vector<uc> activeKeys;

Camera* gameCamera;

Pamant* pamant;
Lac* lac;

void construiesteScena() {
	gameCamera = new Camera(0, 20, 0, 0, 0);
	lac = new Lac({ 0, 0, 0 }, 200, { 13, 51, 128 });
	pamant = new Pamant(-500, 0, -500, 1000, 1000, lac->getLakeSpline());
	
}


void init(void)
{
	glClearColor(0.001f, 0.53f, 0.98f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	//glOrtho(-20.0, 1500, 0.0, 900.0, -1.0, 1.0);

	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glShadeModel(GL_FLAT);

	construiesteScena();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

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
	gluPerspective(45.0f, ratio, 0.1f, 500.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}



void renderScene(void) {

	// Clear Color and Depth Buffers

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	gameCamera->update();

	pamant->render();
	lac->render();



	glutSwapBuffers();

	float currentFrame = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}


void keyUp(uc key, int xx, int yy)
{
	if (isalnum(key))
	{
		activeKeys.erase(remove(activeKeys.begin(), activeKeys.end(), key));
	}
}

void keyDown(uc key, int xx, int yy)
{
	if (isalnum(key))
	{
		activeKeys.push_back(tolower(key));
	}
}

bool isKeyPressed(uc key)
{
	if (isalnum(key))
	{
		return find(activeKeys.begin(), activeKeys.end(), key) != activeKeys.end();
	}
	return false;
}

void updateLogic()
{
	if (isKeyPressed('w'))
	{
		gameCamera->moveCamera(0, 10 * deltaTime);
	}
	if (isKeyPressed('a'))
	{
		gameCamera->panCamera(-0.1f * deltaTime);
	}
	if (isKeyPressed('s'))
	{
		gameCamera->moveCamera(0, -10 * deltaTime);
	}
	if (isKeyPressed('d'))
	{
		gameCamera->panCamera(0.1f * deltaTime);
	}
	if (isKeyPressed('p'))
	{
		gameCamera->tiltCamera(0.001f * deltaTime);
	}
	if (isKeyPressed('l'))
	{
		gameCamera->tiltCamera(-0.001f * deltaTime);
	}
	if (isKeyPressed(27))
	{
		exit(0);
	}
		

	glutPostRedisplay();
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

	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(updateLogic);
	glutKeyboardUpFunc(keyUp);
	glutKeyboardFunc(keyDown);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}