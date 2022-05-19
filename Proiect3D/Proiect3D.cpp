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
#include "Copac.h"
#include "Iarba.h"
#include "Lac.h"
#include "Light.h"
#include "Munte.h"
#include "Peste.h"
#include "Soare.h"

using namespace std;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f;

vector<uc> activeKeys;

Camera* gameCamera;

Pamant* pamant;
Lac* lac;
Soare* soare;

vector<Munte*> munti;

vector<Copac*> copaci;
vector<Peste*> pesti;
Light* g_SunLight, *lumina2, * lumina3, *lumina4;

vector<Iarba*> ierburi;

void construiesteScena() {
	gameCamera = new Camera(0, 20, 0, 0, 0);
	lac = new Lac({ 0, 0, 0 }, 200, { 13, 51, 128 });
	pamant = new Pamant(-1000, 0, -1000, 2000, 2000, lac->getLakeSpline());
	soare = new Soare({0, 600, 0}, 50);

	for (glf i = 0; i <= 2 * M_PI; i += 0.2)
	{
		munti.push_back(new Munte(1000 * cos(i), 0, 1000 * sin(i), 1, 200, 300, { 255, 255, 255 }, -i * 180 / M_PI));
	}

	for(glf i = 0; i <= 2 * M_PI; i += 0.6)
	{
		munti.push_back(new Munte(800 * cos(i), 0, 800 * sin(i), 100, 200, 300, { 255, 255, 255 }, -i * 180 / M_PI));
	}

	for(glf i = 0; i <= 2 * M_PI; i += 0.15)
	{
		copaci.push_back(new Copac((500 + rand() % 200) * cos(i), 0, (500 + rand() % 200) * sin(i)));
	}

	// pesti.push_back(new Peste({30, 0, 0}, 20, 0, 0.1, {200, 150, 150}));

	g_SunLight = new Light(GL_LIGHT0, color4(0.2, 0.2, 0.2, 1), color4(0.8, 0.8, 0.8, 1), color4(1, 1, 1, 1), float4(100, 100, 0, 1), float3(1, 0, 0));
	lumina2 = new Light(GL_LIGHT1, color4(0.2, 0.2, 0.2, 1), color4(0.8, 0.8, 0.8, 1), color4(1, 1, 1, 1), float4(-100, 100, 0, 1), float3(-1, 0, 0));
	lumina3 = new Light(GL_LIGHT2, color4(0.2, 0.2, 0.2, 1), color4(0.8, 0.8, 0.8, 1), color4(1, 1, 1, 1), float4(0, 100, -100, 1), float3(0, 0, 1));
	lumina4 = new Light(GL_LIGHT3, color4(0.2, 0.2, 0.2, 1), color4(0.8, 0.8, 0.8, 1), color4(1, 1, 1, 1), float4(0, 100, 100, 1), float3(0, 0, -1));
	for (int i = 0; i < 8000; i++)
	{
		glf randomAngle = degreesToRadians(rand() % 360);
		ierburi.push_back(new Iarba({250.0f * cos(randomAngle) + (rand() % 200) * cos(randomAngle), 0, 250 * sin(randomAngle) + (rand() % 200) * sin(randomAngle)}, 2 + rand() % 2));
	}
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
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
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
	gluPerspective(45.0f, ratio, 0.1f, 1500.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	gameCamera->update();

	glEnable(GL_LIGHT0);

	g_SunLight->Activate();
	lumina2->Activate();
	lumina3->Activate();
	lumina4->Activate();

	pamant->render();
	
	soare->render();

	for(int i = 0 ; i < munti.size(); i++)
	{
		munti[i]->render();
	}
	for (int i = 0; i < copaci.size(); i++)
	{
		copaci[i]->render();
	}
	for (int i = 0; i < pesti.size(); i++)
	{
		pesti[i]->render();
	}

	for(int i = 0; i < ierburi.size(); i++)
	{
		ierburi[i]->render();
	}

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
	if (key == 27)
	{
		exit(0);
	}
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

glf lastFishSpawn = 0;

void updateLogic()
{
	if (isKeyPressed('w'))
	{
		gameCamera->moveCamera(0, 2 * deltaTime);
	}
	if (isKeyPressed('a'))
	{
		gameCamera->panCamera(-0.1f * deltaTime);
	}
	if (isKeyPressed('s'))
	{
		gameCamera->moveCamera(0, -2 * deltaTime);
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

	if(glutGet(GLUT_ELAPSED_TIME) - lastFishSpawn > 4000)
	{
		pesti.push_back(Peste::generateRandomFish());
		lastFishSpawn = glutGet(GLUT_ELAPSED_TIME);
	}

	for(int i = 0; i < pesti.size(); i++)
	{
		pesti[i]->update();
		if (abs(pesti[i]->getX()) > 250 || abs(pesti[i]->getY()) > 250)
		{
			Peste* p = pesti[i];
			pesti.erase(pesti.begin() + i);
			delete p;
		}
	}

	


	glutPostRedisplay();
}


int main(int argc, char** argv) {

	srand(time(NULL));

	// init GLUT and create window

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
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