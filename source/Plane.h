#pragma once
#include "Object.h"

class Plane :
	public Object
{
private:
	double m_SizeX;
	double m_SizeY;

	double m_EndPointX;
	double m_EndPointY;
public:
	Plane();
	Plane(Vector2 startPoint, Vector2 endPoint);
	~Plane();
	Vector2 GetStartPoint();
	Vector2 GetEndPoint();
	void Render();
};

