#pragma once
#include "Object.h"
#include "Circle.h"

class Rect :
	public Object
{
public:
	double m_SizeX;
	double m_SizeY;

	Rect();
	Rect(Vector2 position, Vector2 size = Vector2(1, 1), double mess = 1.0, Vector2 velocity = Vector2());
	~Rect();
	void Render();

	bool CheckCollider(Circle* circle);
	bool CheckCollider(Rect* other);
	bool CheckCollider(Plane* plane);

	bool ContainPoint(Vector2 pointer);
};

