#ifndef _RAU_H_
#define _RAU_H_

#include "Obiect.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Bezier.h"

class Lac : public Obiect
{
private:

	Point3D _startPos;
	glf _meanRadius;

	CRSpline *spline;

public:

	Lac(Point3D startPos, glf meanRadius, colortype color) : Obiect(startPos.x, startPos.y, startPos.z, color)
	{
		_startPos = startPos;
		_meanRadius = meanRadius; 

		spline = new CRSpline();

		for (float i = 0; i <= 2 * M_PI + 0.1; i += 0.5)
		{
			spline->AddSplinePoint({ _startPos.x + cos(i) * _meanRadius + (cos(i) * _meanRadius * (rand() % 100) / 100), _startPos.y, _startPos.z + sin(i) * _meanRadius + (sin(i) * _meanRadius * (rand() % 100) / 100) });
		}
		spline->AddSplinePoint(spline->GetNthPoint(0));
		spline->AddSplinePoint(spline->GetNthPoint(1));
	}

	void render()
	{
		glColor(_color);

		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(_startPos.x, _startPos.y, _startPos.z);
		for(float t = 0; t <= 1; t += 0.01)
		{
			vec3 pct = spline->GetInterpolatedSplinePoint(t);
			glVertex3f(pct.x, pct.y, pct.z);
		}

		glEnd();

	}

};

#endif
