#pragma once
#include "Obiect.h"

class Soare : public Obiect
{
private:
	glf _size;

public:
	Soare(Point3D position, glf size) : Obiect(position.x, position.y, position.z)
	{
		_size = size;
		_color = { 250, 250, 200 };
	}

	void render()
	{
		glColor(_color);

		glDisable(GL_LIGHTING);

		glPushMatrix();

		glTranslatef(_position.x, _position.y, _position.z);

		GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
		glutSolidSphere(_size, 20, 20);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}

};

