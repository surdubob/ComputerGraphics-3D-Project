#pragma once
#include "Obiect.h"


class Peste : public Obiect
{
private:

	glf _size,  _angle, _speed;
	
public:
	Peste(Point3D position, glf size, glf angle, glf speed, colortype color): Obiect(position.x, position.y, position.z, color)
	{
		_size = size;
		_angle = angle;
		_speed = speed;
	}

	void render()
	{
		glColor(_color);

		GLfloat amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		GLfloat diff[] = { 0.4f, 0.1f, 0.1f, 1.0f };
		GLfloat spec[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0f);

		setMaterialProperties(amb, diff, spec);
		glPushMatrix();
		glScalef(0.5, 0.5, 0.5);
		glPushMatrix();
		glTranslatef(_position.x, _position.y, _position.z);
		glPushMatrix();
		glRotatef(_angle, 0, 1, 0);

		glPushMatrix();
		glScalef(1, 0.4, 0.15);
		glutSolidSphere(_size, 80, 80);
		glPopMatrix();

		glPushMatrix(); // ochi stanga
		glTranslatef(_size - 4, 1, -1);
		GLfloat ambo[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		GLfloat diffo[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		GLfloat speco[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		setMaterialProperties(ambo, diffo, speco);
		glutSolidSphere(1, 16, 16);
		glPopMatrix();

		glPushMatrix(); // ochi dreapta
		glTranslatef(_size - 4, 1, 1);
		setMaterialProperties(ambo, diffo, speco);
		glutSolidSphere(1, 16, 16);
		glPopMatrix();

		glPushMatrix(); // gura
		glTranslatef(_size - 4, -2, 0);
		setMaterialProperties(ambo, diffo, speco);
		glBegin(GL_QUADS);
		glVertex3f(0, 0, -1.8f);
		glVertex3f(0, 0, 1.8f);
		glVertex3f(2.6f, -1, 0.8f);
		glVertex3f(2.6f, -1, -0.8f);
		glEnd();
		glPopMatrix();

		glPushMatrix(); // coada
		glTranslatef(-_size, 0, 0);
		setMaterialProperties(amb, diff, spec);
		glBegin(GL_QUADS);
		glVertex3f(-6.0f, 5, -2.5f);
		glVertex3f(-6.0f, 5, 2.5f);
		glVertex3f(3.0f, 2, 1.0f);
		glVertex3f(3.0f, 2, -1.0f);

		glVertex3f(-6.0f, -5, -2.5f);
		glVertex3f(-6.0f, -5, 2.5f);
		glVertex3f(3.0f, -2, 1.0f);
		glVertex3f(3.0f, -2, -1.0f);

		glVertex3f(-6.0f, -5, 2.5f);
		glVertex3f(-6.0f, 5, 2.5f);
		glVertex3f(3.0f, 2, -1.0f);
		glVertex3f(3.0f, -2, -1.0f);

		glVertex3f(-6.0f, -5, -2.5f);
		glVertex3f(-6.0f, 5, -2.5f);
		glVertex3f(3.0f, 2, -1.0f);
		glVertex3f(3.0f, -2, -1.0f);
		
		glVertex3f(-6.0f, -5, -2.5f);
		glVertex3f(-6.0f, -5, 2.5f);
		glVertex3f(-6.0f, 5, 2.5f);
		glVertex3f(-6.0f, 5, -2.5f);

		glEnd();
		glPopMatrix();

		glTranslatef(-_position.x, -_position.y, -_position.z);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		
	}

	void update()
	{
		_position.x += _speed * cos(degreesToRadians(_angle));
		_position.z += _speed * -sin(degreesToRadians(_angle));
	}

	static Peste* generateRandomFish()
	{
		glf randomAngle = (float)(rand() % 360);
		return new Peste({ 250.0f * -cos(degreesToRadians(randomAngle)), -20, 250.0f * sin(degreesToRadians(randomAngle)) }, 20, randomAngle, 0.1f, { 200, 150, 150 });
	}

	
};
