#pragma once

#include "Obiect.h"

class Munte : public Obiect
{
private:
	glf _sizeX, _sizeY, _sizeZ;
	glf _angle;

	static Texture* texture;

public:

	Munte(glf x, glf y, glf z, glf sizeX, glf sizeY, glf sizeZ, colortype color, glf angle) : Obiect(x, y, z, color) {
		_sizeX = sizeX;
		_sizeY = sizeY;
		_sizeZ = sizeZ;
		_angle = angle;
		if(texture == NULL)
		{
			texture = new Texture("resources/mountain-2-transparent.png", true);
		}
	}

	void render()
	{
		glColor(_color);

		GLfloat amb[] = { 0.2f, 0.4f, 0.4f, 1.0f };
		GLfloat diff[] = { 0.4f, 0.6f, 1.6f, 1.0f };
		GLfloat spec[] = { 0.3f, 0.3f, 0.3f, 1.0f };
		setMaterialProperties(amb, diff, spec);
		texture->bind();

		glDepthMask(GL_FALSE);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMatrixMode(GL_MODELVIEW);


		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glRotatef(_angle, 0, 1, 0);

		glBegin(GL_QUADS);

		glTexCoord2f(0, 1);
		glVertex3f( - _sizeX / 2, 0,  - _sizeZ / 2);
		
		glTexCoord2f(1, 1);
		glVertex3f( - _sizeX / 2, 0, _sizeZ / 2);

		glTexCoord2f(1, 0);
		glVertex3f( + _sizeX / 2, _sizeY, _sizeZ / 2);

		glTexCoord2f(0, 0);
		glVertex3f( + _sizeX / 2, _sizeY, - _sizeZ / 2);
		glTranslatef(-_position.x, -_position.y, -_position.z);
		
		glEnd();
		glPopMatrix();


		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);


		texture->unbind();

		// texture->bind();
		// glBegin(GL_TRIANGLE_FAN);
		//
		// glTexCoord2f(0, 0);
		// glVertex3f(_position.x, _position.y + _sizeY, _position.z);
		//
		// glTexCoord2f(1, 1);
		// glVertex3f(_position.x - _sizeX / 2, _position.y, _position.z - _sizeZ / 2);
		//
		// glTexCoord2f(0, 1);
		// glVertex3f(_position.x + _sizeX / 2, _position.y, _position.z - _sizeZ / 2);
		//
		// glTexCoord2f(1, 0);
		// glVertex3f(_position.x + _sizeX / 2, _position.y, _position.z + _sizeZ / 2);
		//
		// glEnd();
		//
		// texture->unbind();

		// texture->bind();
		//
		// glBegin(GL_TRIANGLE_FAN);
		// glTexCoord2f(0, 0);
		// glVertex3f(_position.x, _position.y + _sizeY, _position.z);
		//
		// glTexCoord2f(1, 1);
		// glVertex3f(_position.x + _sizeX / 2, _position.y, _position.z + _sizeZ / 2);
		//
		//
		// glTexCoord2f(0, 1);
		// glVertex3f(_position.x - _sizeX / 2, _position.y, _position.z + _sizeZ / 2);
		//
		// glTexCoord2f(1, 0);
		// glVertex3f(_position.x - _sizeX / 2, _position.y, _position.z - _sizeZ / 2);
		//
		// glEnd();
		// texture->unbind();
		
	}

};

Texture* Munte::texture = NULL;
