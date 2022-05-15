#pragma once
#include "Obiect.h"
#include "Texture.h"

class Copac : public Obiect
{
private:

	static Texture* brad, * stejar, * mesteacan;
	int type;
	glf size;

public:

	Copac(glf x, glf y, glf z) : Obiect(x, y, z)
	{
		if (brad == NULL)
		{
			brad = new Texture("resources/brad.png", true);
			stejar = new Texture("resources/stejar.png", true);
			mesteacan = new Texture("resources/mesteacan.png", true);
		}
		_color = {200, 200, 200};
		type = rand() % 3;
		size = 80 + rand() % 20;
	}

	void render()
	{
		glColor(_color);

		glDepthMask(GL_FALSE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMatrixMode(GL_MODELVIEW);

		if(type == 0)
		{
			brad->bind();
		}
		else if(type == 1)
		{
			stejar->bind();
		}
		else
		{
			mesteacan->bind();
		}

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glBegin(GL_QUADS);

		glTexCoord2f(1, 1);
		glVertex3f(- size / 4, 0, 0);

		glTexCoord2f(1, 0);
		glVertex3f(- size / 4,  size, 0);

		glTexCoord2f(0, 0);
		glVertex3f( size / 4, size, 0);

		glTexCoord2f(0, 1);
		glVertex3f(size / 4, 0, 0);
		glEnd();

		glTranslatef(-_position.x, -_position.y, -_position.z);
		glPopMatrix();
		if (type == 0)
		{
			brad->unbind();
		}
		else if (type == 1)
		{
			stejar->unbind();
		}
		else
		{
			mesteacan->unbind();
		}

		if (type == 0)
		{
			brad->bind();
		}
		else if (type == 1)
		{
			stejar->bind();
		}
		else
		{
			mesteacan->bind();
		}

		glPushMatrix();
		
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(90, 0, 1, 0);
		glBegin(GL_QUADS);

		glTexCoord2f(1, 1);
		glVertex3f( - size / 4, 0, 0);

		glTexCoord2f(1, 0);
		glVertex3f( - size / 4, size, 0);

		glTexCoord2f(0, 0);
		glVertex3f( + size / 4,  size, 0);

		glTexCoord2f(0, 1);
		glVertex3f( + size / 4, 0, 0);
		glEnd();

		glTranslatef(-_position.x, -_position.y, -_position.z);
		glPopMatrix();
		if (type == 0)
		{
			brad->unbind();
		}
		else if (type == 1)
		{
			stejar->unbind();
		}
		else
		{
			mesteacan->unbind();
		}

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);


	}


};

Texture* Copac::brad = NULL;
Texture* Copac::stejar = NULL;
Texture* Copac::mesteacan = NULL;
