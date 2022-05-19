#ifndef _PAMANT_H_
#define _PAMANT_H_

#include <iostream>
#include <gl/freeglut.h>
#include <algorithm>
#include "Bezier.h"
#include "Obiect.h"
#include "Texture.h"
#include <ctype.h>

#include "Light.h"
using namespace std;


class Pamant : public Obiect {
private:
	GLfloat _sizeX, _sizeZ;

	Texture *texture;

	CRSpline* lakeSpline;

	glf lakeX = FLT_MAX, lakeZ = FLT_MAX, lakeMaxX = FLT_MIN, lakeMaxZ = FLT_MIN;

public:

	Pamant(glf x, glf y, glf z, glf sizeX, glf sizeZ, CRSpline *lake) : Obiect(x, y, z) {
		_sizeX = sizeX;
		_sizeZ = sizeZ;
		_color = { 100, 180, 100 };
		texture = new Texture("resources/grass-texture.png");
		lakeSpline = lake;

		for (float t = 0; t <= 1; t += 0.01)
		{
			vec3 pct = lakeSpline->GetInterpolatedSplinePoint(t);
			if(lakeX > pct.x)
			{
				lakeX = pct.x;
			}

			if (lakeZ > pct.z)
			{
				lakeZ = pct.z;
			}

			if (lakeMaxX < pct.x)
			{
				lakeMaxX = pct.x;
			}

			if (lakeMaxZ < pct.z)
			{
				lakeMaxZ = pct.z;
			}
		}
		// cout << lakeX << " " << lakeZ << " " << lakeMaxX << " " << lakeMaxZ << endl;

	}

	void drawRect(vec3 pct1, vec3 pct2)
	{
		texture->bind();
		glBegin(GL_QUADS);

		glTexCoord2f(8, 8);
		glVertex3f(pct1.x, pct1.y, pct1.z);

		glTexCoord2f(8, 0.0);
		glVertex3f(pct2.x, pct1.y, pct1.z);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(pct2.x, pct1.y, pct2.z);

		glTexCoord2f(0.0, 8);
		glVertex3f(pct1.x, pct1.y, pct2.z);

		glEnd();
		texture->unbind();
	}

	void render() {
		glColor(_color);
		GLfloat amb[] = { 0.0f, 0.3f, 0.1f, 1.0f };
		GLfloat diff[] = { 0.0f, 0.6f, 0.2f, 1.0f };
		GLfloat spec[] = { 0.0f, 0.0f, 0.0f, 1.0f };

		setMaterialProperties(amb, diff, spec);
		// glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.4f);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		texture->bind();
		glBegin(GL_QUADS);

		glTexCoord2f(8.0, 8.0);
		glVertex3f(_position.x, _position.y, _position.z);

		glTexCoord2f(8.0, 0.0);
		glVertex3f(lakeX, _position.y, _position.z);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(lakeX, _position.y, _position.z + _sizeZ);

		glTexCoord2f(0.0, 8.0);
		glVertex3f(_position.x, _position.y, _position.z + _sizeZ);

		glEnd();
		texture->unbind();

		texture->bind();
		glBegin(GL_QUADS);

		glTexCoord2f(8.0, 8.0);
		glVertex3f(lakeMaxX, _position.y, _position.z + _sizeZ);

		glTexCoord2f(8.0, 0.0);
		glVertex3f(lakeMaxX, _position.y, lakeMaxZ);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(lakeX, _position.y, lakeMaxZ);

		glTexCoord2f(0.0, 8.0);
		glVertex3f(lakeX, _position.y, _position.z + _sizeZ);

		glEnd();
		texture->unbind();

		texture->bind();
		glBegin(GL_QUADS);

		glTexCoord2f(8.0, 8.0);
		glVertex3f(lakeMaxX, _position.y, _position.z);

		glTexCoord2f(8.0, 0.0);
		glVertex3f(lakeMaxX, _position.y, _position.z + _sizeZ);

		glTexCoord2f(0.0, 0.0);
		glVertex3f(_position.x + _sizeX, _position.y, _position.z + _sizeZ);

		glTexCoord2f(0.0, 8.0);
		glVertex3f(_position.x + _sizeX, _position.y, _position.z);

		glEnd();
		texture->unbind();

		texture->bind();
		glBegin(GL_QUADS);
		
		glTexCoord2f(8.0, 8.0);
		glVertex3f(lakeX, _position.y, _position.z);
		
		glTexCoord2f(8.0, 0.0);
		glVertex3f(lakeX, _position.y, lakeZ);
		
		glTexCoord2f(0.0, 0.0);
		glVertex3f(lakeMaxX, _position.y, lakeZ);
		
		glTexCoord2f(0.0, 8.0);
		glVertex3f(lakeMaxX, _position.y, _position.z);
		
		glEnd();
		texture->unbind();


		glf step = 0.001;
		int latestEdge = 1;

		for (glf t = 0; t <= 1; t += step)
		{
			vec3 pct1 = lakeSpline->GetInterpolatedSplinePoint(t);
			vec3 pct2 = lakeSpline->GetInterpolatedSplinePoint(t + step);
			glColor(_color);

			int edge = closestEdge(pct1);

			if(edge == 1)
			{
				if (latestEdge != edge)
				{
					int ledge = closestEdge(lakeSpline->GetInterpolatedSplinePoint(t));
					drawRect(pct1, {lakeMaxX, pct1.y, lakeMaxZ});
				}
				latestEdge = 1;
				texture->bind();
				glBegin(GL_QUADS);

				glTexCoord2f(0.5, 0.5);
				glVertex3f(pct1.x, pct1.y, pct1.z);

				glTexCoord2f(0.5, 0.0);
				glVertex3f(pct1.x, pct1.y, lakeMaxZ);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(pct2.x, pct1.y, lakeMaxZ);

				glTexCoord2f(0.0, 0.5);
				glVertex3f(pct2.x, pct2.y, pct2.z);

				glEnd();
				texture->unbind();
			}
			else if (edge == 2)
			{
				if (latestEdge != edge)
				{
					int ledge = closestEdge(lakeSpline->GetInterpolatedSplinePoint(t));
					drawRect(pct1, { lakeX, pct1.y, lakeMaxZ });
				}
				latestEdge = 2;
				texture->bind();
				glBegin(GL_QUADS);

				glTexCoord2f(0.5, 0.5);
				glVertex3f(pct1.x, pct1.y, pct1.z);

				glTexCoord2f(0.5, 0.0);
				glVertex3f(lakeX, pct1.y, pct1.z);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(lakeX, pct1.y, pct2.z);

				glTexCoord2f(0.0, 0.5);
				glVertex3f(pct2.x, pct2.y, pct2.z);

				glEnd();
				texture->unbind();
			}
			else if (edge == 3)
			{
				if (latestEdge != edge)
				{
					int ledge = closestEdge(lakeSpline->GetInterpolatedSplinePoint(t));
					drawRect(pct1, { lakeX, pct1.y, lakeZ });
				}
				latestEdge = 3;
				texture->bind();
				glBegin(GL_QUADS);

				glTexCoord2f(0.5, 0.5);
				glVertex3f(pct1.x, pct1.y, pct1.z);

				glTexCoord2f(0.5, 0.0);
				glVertex3f(pct1.x, pct1.y, lakeZ);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(pct2.x, pct1.y, lakeZ);

				glTexCoord2f(0.0, 0.5);
				glVertex3f(pct2.x, pct2.y, pct2.z);

				glEnd();
				texture->unbind();
			}
			else if (edge == 4)
			{
				if (latestEdge != edge)
				{
					int ledge = closestEdge(lakeSpline->GetInterpolatedSplinePoint(t));
					drawRect(pct1, { lakeMaxX, pct1.y, lakeZ });
				}
				latestEdge = 4;
				texture->bind();
				glBegin(GL_QUADS);

				glTexCoord2f(0.5, 0.5);
				glVertex3f(pct1.x, pct1.y, pct1.z);

				glTexCoord2f(0.5, 0.0);
				glVertex3f(lakeMaxX, pct1.y, pct1.z);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(lakeMaxX, pct1.y, pct2.z);

				glTexCoord2f(0.0, 0.5);
				glVertex3f(pct2.x, pct2.y, pct2.z);

				glEnd();
				texture->unbind();
			}

			

		}

	}

	glf distancePointEdge(vec3 pct, Point A, Point B)
	{
		return abs((B.x - A.x) * (A.y - pct.z) - (A.x - pct.x) * (B.y - A.y)) / sqrt((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
	}

	int closestEdge(vec3 pct)
	{
		glf d1 = distancePointEdge(pct, {lakeX, lakeMaxZ}, {lakeMaxX, lakeMaxZ});
		glf d2 = distancePointEdge(pct, { lakeX, lakeZ }, { lakeX, lakeMaxZ });
		glf d3 = distancePointEdge(pct, { lakeX, lakeZ }, { lakeMaxX, lakeZ });
		glf d4 = distancePointEdge(pct, { lakeMaxX, lakeZ }, { lakeMaxX, lakeMaxZ });
		glf m = min({ d1, d2, d3, d4 });
		if (m == d1)
		{
			return 1;
		}
		if (m == d2)
		{
			return 2;
		}
		if (m == d3)
		{
			return 3;
		}
		if (m == d4)
		{
			return 4;
		}
	}
};

#endif

