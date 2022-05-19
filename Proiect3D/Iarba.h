#pragma once
#include "Obiect.h"


class Iarba : public Obiect
{
private:
	glf size;

	static Texture* tex;
public:
	Iarba(Point3D position, glf s) : Obiect(position.x, position.y, position.z)
	{
		this->size = s;

		if (tex == NULL)
		{
			tex = new Texture("resources/grass.png", true);
		}
	}

	void render()
	{
		GLfloat amb[] = { 0.1f, 0.3f, 0.1f, 1.0f };
		GLfloat diff[] = { 0.0f, 0.1f, 0.0f, 1.0f };
		GLfloat spec[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		glMaterialf(GL_FRONT_AND_BACK, GL_EMISSION, 0.0f);

		setMaterialProperties(amb, diff, spec);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMatrixMode(GL_MODELVIEW);

		tex->bind();
		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glBegin(GL_QUADS);

		glTexCoord2f(1, 1);
		glVertex3f(-size, 0, 0);

		glTexCoord2f(1, 0);
		glVertex3f(-size, size, 0);

		glTexCoord2f(0, 0);
		glVertex3f(size, size, 0);

		glTexCoord2f(0, 1);
		glVertex3f(size, 0, 0);
		glEnd();

		glTranslatef(-_position.x, -_position.y, -_position.z);
		glPopMatrix();

		tex->unbind();


		// tex->bind();
		//
		//
		// glPushMatrix();
		//
		// glTranslatef(_position.x, _position.y, _position.z);
		// glRotatef(90, 0, 1, 0);
		// glBegin(GL_QUADS);
		//
		// glTexCoord2f(1, 1);
		// glVertex3f(-size, 0, 0);
		//
		// glTexCoord2f(1, 0);
		// glVertex3f(-size, size, 0);
		//
		// glTexCoord2f(0, 0);
		// glVertex3f(+size, size, 0);
		//
		// glTexCoord2f(0, 1);
		// glVertex3f(+size, 0, 0);
		// glEnd();
		//
		// glTranslatef(-_position.x, -_position.y, -_position.z);
		// glPopMatrix();
		//
		// tex->unbind();
		

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
	}

	static int cmp(Iarba* i1, Iarba *i2)
	{
		return i1->getX() * i1->getX() + i1->getY() * i1->getY() > i2->getX() * i2->getX() + i2->getY() * i2->getY();
	}
};

Texture* Iarba::tex = NULL;