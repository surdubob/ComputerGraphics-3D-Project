#pragma once
#include "Obiect.h"

class Barca : public Obiect
{
private:
	Texture* tex;

public:
	Barca(Point3D position) : Obiect(position.x, position.y, position.z)
	{
		tex = new Texture("resources/woodwall.png");
	}

	void render()
	{
		GLfloat amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		GLfloat diff[] = { 0.4f, 0.1f, 0.1f, 1.0f };
		GLfloat spec[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0f);

		setMaterialProperties(amb, diff, spec);

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);

		tex->bind();
		glBegin(GL_QUAD_STRIP);
		glTexCoord2f(0, 0);
		glVertex3f(20, 0, 0);
		glTexCoord2f(0, 1);
		glVertex3f(32, 10, 0);

		for (glf x = 19; x >= -19; x -= 0.5)
		{
			glTexCoord2f(0, 0);
			glVertex3f(x, 0, 0);
			glTexCoord2f(0, 1);
			glVertex3f(x, 10, - x * x / 100 + 20);
		}
		glTexCoord2f(0, 0);
		glVertex3f(-19, 0, 0);
		glTexCoord2f(0, 1);
		glVertex3f(-19, 10, 0);
		glEnd();

		tex->unbind();
		tex->bind();

		glBegin(GL_QUAD_STRIP);
		glTexCoord2f(0, 0);
		glVertex3f(20, 0, 0);
		glTexCoord2f(0, 1);
		glVertex3f(32, 10, 0);

		for (glf x = 19; x >= -19; x -= 0.5)
		{
			glTexCoord2f(0, 0);
			glVertex3f(x, 0, 0);
			glTexCoord2f(0, 1);
			glVertex3f(x, 10, x * x / 100 - 20);
		}

		glTexCoord2f(0, 0);
		glVertex3f(-19, 0, 0);
		glTexCoord2f(0, 1);
		glVertex3f(-19, 10, 0);

		glEnd();
		tex->unbind();

		glPopMatrix();
	}
	
};
