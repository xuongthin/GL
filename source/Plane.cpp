#include "Plane.h"

Plane::Plane()
{
	m_Name = "Plane";
}

Plane::Plane(Vector2 startPoint, Vector2 endPoint)
{
	m_Name = "Plane";

	//m_Position = (startPoint + endPoint) / 2;
	Vector2 position = (startPoint + endPoint) / 2;
	SetPosition(position);

	double height = abs(startPoint.y - endPoint.y);
	double width = abs(startPoint.x - endPoint.x);

	if (height > width) {
		m_SizeX = 1;
		m_SizeY = height;
	}
	else {
		m_SizeX = width;
		m_SizeY = 1;
	}

	/*m_Velocity = Vector2();*/
	SetVelocity(Vector2());
	m_isStatic = true;
}

Plane::~Plane()
{
}

Vector2 Plane::GetStartPoint()
{
	return Vector2(m_Position.x - m_SizeX / 2, m_Position.y - m_SizeY / 2);
}

Vector2 Plane::GetEndPoint()
{
	return Vector2(m_Position.x + m_SizeX / 2, m_Position.y + m_SizeY / 2);
}

void Plane::Render()
{
	VideoDriver::GetInstance()->DrawRect(m_Position.x - m_SizeX / 2, m_Position.y - m_SizeY / 2, m_SizeX, m_SizeY);
	//VideoDriver::GetInstance()->DrawRect(m_PositionX + 10, m_PositionY + 10, abs(m_EndPointX - m_PositionX) + 10, abs(m_EndPointY - m_PositionY) + 10);
}
