#pragma once

#include "Obiect.h"


class Camera
{
private:
	glf _x, _y, _z;
	glf _angleX, _angleY;

	glf targetX, targetY = 0, targetZ;

	float startTime = 0;
	float endTime = 0;
	bool moveRunning = false;
	int signX = 1, signZ = 1, angleSign = 0;

	float targetAngleX, angleStartTime, angleEndTime;
	bool panRunning = false;

public:

	Camera(glf x, glf y, glf z, glf angleX, glf angleY)
	{
		_x = x;
		_y = y;
		_z = z;
		_angleX = angleX;
		_angleY = angleY;
		targetAngleX = _angleX;
		angleStartTime = 0;
	}

	void update()
	{

		if(moveRunning)
		{
			_x = _x + ((abs(_x - targetX) / (endTime - startTime)) * cos(_angleX + signZ * M_PI));
			_z = _z + ((abs(_z - targetZ) / (endTime - startTime)) * sin(_angleX + signZ * M_PI));

			if (glutGet(GLUT_ELAPSED_TIME) > endTime)
			{
				moveRunning = false;
			}
		}

		if(panRunning)
		{
			_angleX += angleSign * abs(_angleX - targetAngleX) / (angleEndTime - angleStartTime);
			if (glutGet(GLUT_ELAPSED_TIME) > angleEndTime)
			{
				panRunning = false;
			}
		}
		gluLookAt(_x, _y, _z, _x + cos(_angleX), _y + _angleY, _z + sin(_angleX), 0, 1, 0);
	}

	void moveCamera(glf xOffset, glf zOffset)
	{
		moveRunning = true;
		startTime = glutGet(GLUT_ELAPSED_TIME);
		endTime = startTime + (abs(abs(zOffset) * cos(_angleX)) + abs(abs(zOffset) * sin(_angleX)));
		targetX =  _x + zOffset * cos(_angleX);
		targetZ =  _z + zOffset * sin(_angleX);

		if(zOffset < 0)
		{
			signZ = -1;
		}
		else
		{
			signZ = 0;
		}
	}

	void panCamera(glf angleOffset)
	{
		if (angleOffset < 0)
		{
			angleSign = -1;
		}
		else
		{
			angleSign = 1;
		}
		targetAngleX = _angleX + angleOffset;
		angleStartTime = glutGet(GLUT_ELAPSED_TIME);
		panRunning = true;
		angleEndTime = angleStartTime + abs(angleOffset) * M_PI * 50;
	}

	void tiltCamera(glf angleOffset) {
		_angleY += angleOffset;
	}

	GLfloat getX() const
	{
		return _x;
	}

	GLfloat getY() const
	{
		return _y;
	}

	GLfloat getZ() const
	{
		return _z;
	}

	GLfloat getAngleX() const
	{
		return _angleX;
	}

	GLfloat getAngleY() const
	{
		return _angleY;
	}

};
