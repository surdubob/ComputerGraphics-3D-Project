#pragma once
#include "Obiect.h"
#include "Texture.h"


class Casa : public Obiect
{
private:
	glf _w, _l, _angle;

	int roofTex, wallTex, doorTex;

	static Texture* roofTexture1, *roofTexture2, * wallTexture1, *wallTexture2, *wallTexture3, * doorTexture1, * doorTexture2, *windowTexture1, *windowTexture2;

public:
	Casa(Point3D position, glf width, glf length, glf angle) : Obiect(position.x, position.y, position.z)
	{
		_w = width;
		_l = length;
		_angle = angle;

		if(roofTexture1 == NULL)
		{
			roofTexture1 = new Texture("resources/roof2.png");
			roofTexture2 = new Texture("resources/roof3.png");
			wallTexture1 = new Texture("resources/woodwall.png");
			wallTexture2 = new Texture("resources/woodwall2.png");
			wallTexture3 = new Texture("resources/brickwall.png");
			doorTexture1 = new Texture("resources/door1.png");
			doorTexture2 = new Texture("resources/door2.png");
			windowTexture1 = new Texture("resources/windows.png");
			windowTexture2 = new Texture("resources/closed-window.jpg");
		}

		roofTex = rand() % 2;
		wallTex = rand() % 3;
		doorTex = rand() % 2;
	}

	void render()
	{
		GLfloat amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		GLfloat diff[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		GLfloat spec[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		setMaterialProperties(amb, diff, spec);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMatrixMode(GL_MODELVIEW);

		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glPushMatrix();
		glRotatef(_angle, 0, 1, 0);

		//inceput pereti
		switch (wallTex)
		{
		case 0:
			wallTexture1->bind();
			break;
		case 1:
			wallTexture2->bind();
			break;
		case 2:
			wallTexture3->bind();
			break;
		}

		glBegin(GL_QUADS);

		glTexCoord2f(0, 0);
		glVertex3f(-_w / 2, 0, -_l / 2);

		glTexCoord2f(2, 0);
		glVertex3f(_w / 2, 0, -_l / 2);

		glTexCoord2f(2, 1);
		glVertex3f(_w / 2, 40, -_l / 2);

		glTexCoord2f(0, 1);
		glVertex3f(-_w / 2, 40, -_l / 2);
		

		glTexCoord2f(0, 0);
		glVertex3f(_w / 2, 0, -_l / 2);

		glTexCoord2f(2, 0);
		glVertex3f(_w / 2, 0, _l / 2);

		glTexCoord2f(2, 1);
		glVertex3f(_w / 2, 40, _l / 2);

		glTexCoord2f(0, 1);
		glVertex3f(_w / 2, 40, -_l / 2);


		glTexCoord2f(0, 0);
		glVertex3f(-_w / 2, 0, _l / 2);

		glTexCoord2f(2, 0);
		glVertex3f(_w / 2, 0, _l / 2);

		glTexCoord2f(2, 1);
		glVertex3f(_w / 2, 40, _l / 2);

		glTexCoord2f(0, 1);
		glVertex3f(-_w / 2, 40, _l / 2);


		glTexCoord2f(0, 0);
		glVertex3f(-_w / 2, 0, -_l / 2);

		glTexCoord2f(2, 0);
		glVertex3f(-_w / 2, 0, _l / 2);

		glTexCoord2f(2, 1);
		glVertex3f(-_w / 2, 40, _l / 2);

		glTexCoord2f(0, 1);
		glVertex3f(-_w / 2, 40, -_l / 2);

		glEnd();

		glBegin(GL_TRIANGLES);

		glTexCoord2f(0, 0);
		glVertex3f(-_w / 2, 40, - _l / 2);

		glTexCoord2f(1, 0);
		glVertex3f(-_w / 2, 40, _l / 2);
		
		glTexCoord2f(0.5, 0.5);
		glVertex3f(-_w / 2, 60, 0);


		glTexCoord2f(0, 0);
		glVertex3f(_w / 2, 40, -_l / 2);

		glTexCoord2f(1, 0);
		glVertex3f(_w / 2, 40, _l / 2);

		glTexCoord2f(0.5, 0.5);
		glVertex3f(_w / 2, 60, 0);

		glEnd();

		switch (wallTex)
		{
		case 0:
			wallTexture1->unbind();
			break;
		case 1:
			wallTexture2->unbind();
			break;
		case 2:
			wallTexture3->unbind();
			break;
		} // terminare pereti


		switch (roofTex) // inceput acoperis
		{
		case 0:
			roofTexture1->bind();
			break;
		case 1:
			roofTexture2->bind();
			break;
		}

		glf pantaAcoperis = 20 / (_l / 2), cosoroaba = 10.0f;

		glBegin(GL_QUADS);

		glTexCoord2f(0, 1);
		glVertex3f(-_w / 2 - 10, 40 - cosoroaba * sin(atan(pantaAcoperis)),  - _l / 2 - cosoroaba * cos(atan(pantaAcoperis)));

		glTexCoord2f(0, 0);
		glVertex3f(-_w / 2 - 10, 60, 0);

		glTexCoord2f(2, 0);
		glVertex3f(_w / 2 + 10, 60, 0);

		glTexCoord2f(2, 1);
		glVertex3f(_w / 2 + 10, 40 - cosoroaba * sin(atan(pantaAcoperis)), -_l / 2  - cosoroaba * cos(atan(pantaAcoperis)));

		glEnd();

		glBegin(GL_QUADS);

		glTexCoord2f(0, 1);
		glVertex3f(-_w / 2 - 10, 40 - cosoroaba * sin(atan(pantaAcoperis)), _l / 2 + cosoroaba * cos(atan(pantaAcoperis)));

		glTexCoord2f(0, 0);
		glVertex3f(-_w / 2 - 10, 60, 0);

		glTexCoord2f(2, 0);
		glVertex3f(_w / 2 + 10, 60, 0);

		glTexCoord2f(2, 1);
		glVertex3f(_w / 2 + 10, 40 - cosoroaba * sin(atan(pantaAcoperis)), _l / 2 + cosoroaba * cos(atan(pantaAcoperis)));

		glEnd();

		switch (roofTex) // sfarsit acoperis
		{
		case 0:
			roofTexture1->unbind();
			break;
		case 1:
			roofTexture2->unbind();
			break;
		}

		switch (doorTex) // inceput usa
		{
		case 0:
			doorTexture1->bind();
			break;
		case 1:
			doorTexture2->bind();
			break;
		}

		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex3f(-_w / 2 - 1, 0, -10);

		glTexCoord2f(1, 1);
		glVertex3f(-_w / 2 - 1, 0, 10);

		glTexCoord2f(1, 0);
		glVertex3f(-_w / 2 - 1, 35, 10);

		glTexCoord2f(0, 0);
		glVertex3f(-_w / 2 - 1, 35, -10);


		glTexCoord2f(0, 1);
		glVertex3f(_w / 2 + 1, 0, -10);

		glTexCoord2f(1, 1);
		glVertex3f(_w / 2 + 1, 0, 10);

		glTexCoord2f(1, 0);
		glVertex3f(_w / 2 + 1, 35, 10);

		glTexCoord2f(0, 0);
		glVertex3f(_w / 2 + 1, 35, -10);
		glEnd();

		switch (doorTex) // sfarsit usa
		{
		case 0:
			doorTexture1->unbind();
			break;
		case 1:
			doorTexture2->unbind();
			break;
		}

		// inceput geamuri
		
		windowTexture1->bind();
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex3f( - 45, 10, -_l / 2 - 0.1);

		glTexCoord2f(1, 1);
		glVertex3f( -15, 10, -_l / 2 - 0.1);

		glTexCoord2f(1, 0);
		glVertex3f( -15, 30, -_l / 2 - 0.1);

		glTexCoord2f(0, 0);
		glVertex3f(-45, 30, -_l / 2 - 0.1);
		

		glTexCoord2f(0, 1);
		glVertex3f(45, 10, -_l / 2 - 0.1);

		glTexCoord2f(1, 1);
		glVertex3f(15, 10, -_l / 2 - 0.1);

		glTexCoord2f(1, 0);
		glVertex3f(15, 30, -_l / 2 - 0.1);

		glTexCoord2f(0, 0);
		glVertex3f(45, 30, -_l / 2 - 0.1);
		
		glEnd();
		windowTexture1->unbind();
		// sfarsit geamuri
		windowTexture2->bind();
		glBegin(GL_QUADS);
		glTexCoord2f(0, 1);
		glVertex3f(-45, 10, _l / 2 + 0.1);

		glTexCoord2f(1, 1);
		glVertex3f(-15, 10, _l / 2 + 0.1);

		glTexCoord2f(1, 0);
		glVertex3f(-15, 30, _l / 2 + 0.1);

		glTexCoord2f(0, 0);
		glVertex3f(-45, 30, _l / 2 + 0.1);


		glTexCoord2f(0, 1);
		glVertex3f(45, 10, _l / 2 + 0.1);

		glTexCoord2f(1, 1);
		glVertex3f(15, 10, _l / 2 + 0.1);

		glTexCoord2f(1, 0);
		glVertex3f(15, 30, _l / 2 + 0.1);

		glTexCoord2f(0, 0);
		glVertex3f(45, 30, _l / 2 + 0.1);

		glEnd();
		windowTexture2->unbind();

		
		glPopMatrix();
		glPopMatrix();

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
	}
	
};


Texture* Casa::roofTexture1 = NULL;
Texture* Casa::roofTexture2 = NULL;
Texture* Casa::wallTexture1 = NULL;
Texture* Casa::wallTexture2 = NULL;
Texture* Casa::wallTexture3 = NULL;
Texture* Casa::doorTexture1 = NULL;
Texture* Casa::doorTexture2 = NULL;
Texture* Casa::windowTexture1 = NULL;
Texture* Casa::windowTexture2 = NULL;