#include <iostream>
#include<gl/freeglut.h>

#include <vector>
#include <time.h>
#include <stdlib.h>
#include "SOIL.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

// angle of rotation for the camera direction
float angle = M_PI / 2;
// actual vector representing the camera's direction
float lx = sin(angle), lz = -cos(angle);
// XZ position of the camera
float x = -60.0f, z = 0.0f;


#define uc unsigned char
#define glf GLfloat
#define colortype vector<uc>

void glColor(uc r, uc g, uc b) {
	glColor3ub(r, g, b);
}

void glColor(uc r, uc g, uc b, uc a) {
	glColor4ub(r, g, b, a);
}

void glColor(vector<uc> col) {
	glColor3ub(col[0], col[1], col[2]);
}

struct Point3D {
	float x, y, z;
};

class Obiect {
protected:
	Point3D _position;
	colortype _color = { 0, 0, 0 };

public:
	Obiect() {
		_position = { 0, 0, 0 };
	}

	Obiect(GLfloat x, GLfloat y, GLfloat z) {
		_position = { x, y, z };
	}

	Obiect(GLfloat x, GLfloat y, GLfloat z, colortype color) {
		_position = { x, y, z };
		_color[0] = color[0];
		_color[1] = color[1];
		_color[2] = color[2];
	}

	virtual void render() = 0;

	void setX(GLfloat x) {
		_position.x = x;
	}

	void setY(GLfloat y) {
		_position.y = y;
	}

	GLfloat getX() {
		return _position.x;
	}

	GLfloat getY() {
		return _position.y;
	}

	GLfloat getZ() {
		return _position.z;
	}

	void setColor(uc r, uc g, uc b) {
		_color = { r, g, b };
	}

	void setColor(colortype color) {
		_color = color;
	}
};


class Pamant : public Obiect {
private:
	GLfloat _sizeX, _sizeZ;

	unsigned char* textureImage;
	int textureWidth, textureHeight;
	GLuint textureIndex;
public:

	Pamant(glf x, glf y, glf z, glf sizeX, glf sizeZ) : Obiect(x, y, z) {
		_sizeX = sizeX;
		_sizeZ = sizeZ;
		_color = { 100, 180, 100 };
	}

	void render() {
		glColor(_color);

		glBindTexture(GL_TEXTURE_2D, textureIndex);

		glBegin(GL_QUADS);
		
		glTexCoord2f(8.0, 8.0); 
		glVertex3f(_position.x, _position.y, _position.z);

		glTexCoord2f(8.0, 0.0);
		glVertex3f(_position.x + _sizeX, _position.y, _position.z);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(_position.x + _sizeX, _position.y, _position.z + _sizeZ);

		glTexCoord2f(0.0, 8.0);
		glVertex3f(_position.x, _position.y, _position.z + _sizeZ);

		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void loadTexture()
	{
		
		glGenTextures(1, &textureIndex);
		glBindTexture(GL_TEXTURE_2D, textureIndex);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


		textureImage = SOIL_load_image("resources/grass-texture.png", &textureWidth, &textureHeight, 0, SOIL_LOAD_RGB);

		if(textureImage)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage);
		}
		else
		{
			cout << "Failed to load texture" << std::endl;
		}
		
		SOIL_free_image_data(textureImage);
	}

};

struct mvec2 {
	float x, y;
	mvec2()
	{
		x = y = 0;
	}
	mvec2(float x, float y) : x(x), y(y) {}
};

mvec2 operator + (mvec2 a, mvec2 b) {
	return mvec2(a.x + b.x, a.y + b.y);
}

mvec2 operator - (mvec2 a, mvec2 b) {
	return mvec2(a.x - b.x, a.y - b.y);
}

mvec2 operator * (float s, mvec2 a) {
	return mvec2(s * a.x, s * a.y);
}

class Rau : public Obiect
{
private:

	vector<vector<glf>> controlPoints;
	vector<vector<glf>> centerLinePoints;
	Point3D _startPos;
	int _nrPoints, *c;

	void bezierCoefficients(int n, int* c)
	{
		int k, i;
		for (k = 0; k <= n; k++)
		{
			c[k] = 1;
			for (i = n; i >= k + 1; i--)
				c[k] *= i;
			for (i = n - k; i >= 2; i--)
				c[k] /= i;

		}
	}

	void computeBezier()
	{
		int k, n = 4;

		float x, y, u, blend;
		bezierCoefficients(n, c);


		for (u = 0; u < 1.0; u += 0.01)
		{
			x = 0; y = 0;
			for (k = 0; k < _nrPoints; k++)
			{
				blend = c[k] * pow(u, k) * pow(1 - u, n - k);
				x += controlPoints[k][0] * blend;
				y += controlPoints[k][1] * blend;
			}
			centerLinePoints.push_back({ x, y });
		}
	}

	mvec2 getBezierPoint(mvec2* points, int numPoints, float t) {
		mvec2* tmp = new mvec2[numPoints];
		memcpy(tmp, points, numPoints * sizeof(mvec2));
		int i = numPoints - 1;
		while (i > 0) {
			for (int k = 0; k < i; k++)
				tmp[k] = tmp[k] + t * (tmp[k + 1] - tmp[k]);
			i--;
		}
		mvec2 answer = tmp[0];
		delete[] tmp;
		return answer;
	}

	

public:

	Rau(Point3D startPos, int nrPoints, colortype color) : Obiect(startPos.x, startPos.y, startPos.z, color)
	{
		_startPos = startPos;
		_nrPoints = nrPoints;
		c = new int[_nrPoints];
		controlPoints = { {startPos.x, startPos.z} };
		centerLinePoints = { {startPos.x, startPos.z} };

		mvec2* pct = new mvec2[_nrPoints];
		pct[0] = { startPos.x, startPos.z };

		for (int i = 1; i < _nrPoints; i++)
		{
			glf zCoord = (rand() % 100 - 50) * 1.0f;
			controlPoints.push_back({ startPos.x + i * 50.0f, startPos.z + zCoord });
			pct[i] = { startPos.x + i * 50.0f, startPos.z + zCoord };
		}

		for (int i = 0; i < _nrPoints; i++)
		{
			mvec2 r = getBezierPoint(pct, _nrPoints, 1);
			centerLinePoints.push_back({r.x, r.y});
		}

		

		//computeBezier();


	}

	~Rau()
	{
		delete(c);
	}

	void render()
	{
		glColor(_color);

		glLineWidth(5);


		glBegin(GL_QUAD_STRIP);
		for (int i = 0; i < centerLinePoints.size(); i++)
		{
			glVertex3f(centerLinePoints[i][0], 0.1f, centerLinePoints[i][1] + 4);
			glVertex3f(centerLinePoints[i][0], 0.1f, centerLinePoints[i][1] - 4);
		}
		glEnd();
		glColor(255, 0, 0);

		glPointSize(5.0f);
		glBegin(GL_POINTS);
		for (int i = 0; i < controlPoints.size(); i++)
		{
			glVertex3f(controlPoints[i][0], 0.5f, controlPoints[i][1]);
		}
		glEnd();


	}

};

Pamant* pamant;
Rau* rau;

void construiesteScena() {
	pamant = new Pamant(-500, 0, -500, 1000, 1000);
	rau = new Rau({-500, 0.1f, 0}, 20, { 51, 51, 255 });
}

void loadTextures()
{
	pamant->loadTexture();
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

	loadTextures();
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
	rau->render();

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
	glutCreateWindow("Scena 3D cu oameni de zapada");

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