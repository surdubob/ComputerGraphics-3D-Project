#ifndef _PAMANT_H_
#define _PAMANT_H_

#include <iostream>
#include <gl/freeglut.h>
#include "Obiect.h"
#include "Texture.h"

using namespace std;


class Pamant : public Obiect {
private:
	GLfloat _sizeX, _sizeZ;

	Texture *texture;

public:

	Pamant(glf x, glf y, glf z, glf sizeX, glf sizeZ) : Obiect(x, y, z) {
		_sizeX = sizeX;
		_sizeZ = sizeZ;
		_color = { 100, 180, 100 };
		texture = new Texture("resources/grass-texture.png");
	}

	void render() {
		glColor(_color);

		texture->bind();

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
		texture->unbind();
	}
};

#endif

