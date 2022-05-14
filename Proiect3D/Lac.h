#ifndef _RAU_H_
#define _RAU_H_

#include <gl/freeglut.h>
#include "Obiect.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Lac : public Obiect
{
private:

	Point3D _startPos;
	glf _meanRadius;

public:

	Lac(Point3D startPos, glf meanRadius, colortype color) : Obiect(startPos.x, startPos.y, startPos.z, color)
	{
		_startPos = startPos;
		_meanRadius = meanRadius;
	}

	void render()
	{
		glColor(_color);

		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(_startPos.x, _startPos.y, _startPos.z);

		for(float i = 0 ; i <= 2 * M_PI + 0.1; i += 0.1)
		{
			glVertex3f(_startPos.x + cos(i) * _meanRadius, _startPos.y, _startPos.z + sin(i) * _meanRadius);
		}

		glEnd();

	}

};

#endif
