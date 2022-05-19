#pragma once
#include "Obiect.h"


class Iarba : public Obiect
{
private:
	glf _size;
public:
	Iarba(Point3D position, glf size) : Obiect(position.x, position.y, position.z)
	{
		_size = size;
	}

	void render()
	{
		GLfloat amb[] = { 0.0f, 0.1f, 0.0f, 1.0f };
		GLfloat diff[] = { 0.0f, 0.1f, 0.0f, 1.0f };
		GLfloat spec[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		glMaterialf(GL_FRONT_AND_BACK, GL_EMISSION, 0.0f);

		setMaterialProperties(amb, diff, spec);

		glBegin(GL_TRIANGLES);

		glVertex3f(_position.x - 0.3f, _position.y, _position.z);
		glVertex3f(_position.x + 0.3f, _position.y, _position.z);
		glVertex3f(_position.x, _position.y + _size, _position.z);

		glEnd();
	}

};
