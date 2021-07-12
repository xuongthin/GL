#pragma once
#include "Object.h"
#include "Plane.h"

class Circle :
	public Object
{
public:
	float m_radius;

	Circle();
	Circle(Vector2 position, double radius = 1, double mess = 1.0f, Vector2 velocity = Vector2());
	~Circle();
	void Render();

	bool CheckCollider(Circle* other);
	bool CheckCollider(Plane* plane);

	bool CheckCollider(Vector2 startPoint, Vector2 endPoint);
	bool ContainPoint(Vector2 point);
};

