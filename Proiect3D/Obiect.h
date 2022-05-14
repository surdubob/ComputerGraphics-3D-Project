/*
 * Acest fisier contine declaratia si implementarea clasei Obiect, cat si declaratia unor tipuri globale de date si macrouri
 */
#ifndef _OBIECT_H_
#define _OBIECT_H_

#include<gl/freeglut.h>
#include <vector>

using namespace std;

#define uc unsigned char
#define glf GLfloat
#define colortype vector<uc>

void glColor(uc r, uc g, uc b) {
	glColor3ub(r, g, b);
}

void glColor(uc r, uc g, uc b, uc a) {
	glColor4ub(r, g, b, a);
}

void glColor(colortype col) {
	glColor3ub(col[0], col[1], col[2]);
}

struct Point {
	glf x, y;

	Point(){}

	Point(glf ics, glf igrec) : x(ics), y(igrec)
	{
		
	}
};

struct Point3D {
	glf x, y, z;
};

glf mat_solid[] = { 0.75, 0.75, 0.0, 1.0 };
glf mat_zero[] = { 0.0, 0.0, 0.0, 1.0 };
glf mat_transparent[] = { 0.0, 0.8, 0.8, 0.6 };
glf mat_emission[] = { 0.0, 0.3, 0.3, 0.6 };


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


#endif

