#include "Circle.h"

Circle::Circle()
{
	m_Name = "Circle";
}

Circle::Circle(Vector2 position, double radius, double mess, Vector2 velocity)
{
	m_Name = "Circle";

	m_radius = radius;
	//m_Mess = PI * radius * radius;
	m_Mess = 1;

	//m_Position = position;
	SetPosition(position);
	//m_Velocity = velocity;
	SetVelocity(velocity);
}

Circle::~Circle()
{

}

void Circle::Render()
{
	VideoDriver::GetInstance()->DrawCircle(m_Position.x, m_Position.y, m_radius);
	//VideoDriver::GetInstance()->DrawCircle(m_PositionX, m_PositionY, m_radius);
}



bool Circle::CheckCollider(Circle * other)
{
	Vector2 thisCenter = Vector2(m_Position.x, m_Position.y);

	Vector2 othersCenter = Vector2(other->m_Position.x, other->m_Position.y);

	Vector2 direction = othersCenter - thisCenter;

	double distance = direction.length();

	if (distance <= m_radius + other->m_radius)
	{
		// tach roi
		double d = m_radius + other->m_radius - distance;
		Move((Vector2() - direction).Normalize() * d / 2);
		other->Move(direction.normalize() * d / 2);

		double contactAngle = direction.angle();
		
		SetVelocity(Vector2::VelocityAfterCollision(Vector2() - direction, m_Mess, m_Velocity, other->m_Mess, other->m_Velocity));
		other->SetVelocity(Vector2::VelocityAfterCollision(direction, other->m_Mess, other->m_Velocity, m_Mess, m_Velocity));
		return true;
	}

	return false;
}

bool Circle::CheckCollider(Plane * plane)
{
	Vector2 startPoint = plane->GetStartPoint();
	Vector2 endPoint = plane->GetEndPoint();

	Vector2 center = Vector2(m_Position.x, m_Position.y);
	double distance = center.distanceToSegment(startPoint, endPoint);

	if (distance <= m_radius)
	{
		Vector2 forceDirection = Vector2::NormalFromLineToPoint(center, startPoint, endPoint);

		// tach roi
		double d = m_radius - distance;
		Move(forceDirection.normalize() * d);

		m_Velocity = Vector2::VelocityAfterCollision(m_Velocity, forceDirection, 0.2);
		return true;
	}

	return false;
}

bool Circle::CheckCollider(Vector2 startPoint, Vector2 endPoint)
{
	Vector2 center = Vector2(m_Position.x, m_Position.y);
	double distance = center.distanceToSegment(startPoint, endPoint);
	return distance <= m_radius;
}

bool Circle::ContainPoint(Vector2 point)
{
	Vector2 direction = point - Vector2(m_Position.x, m_Position.y);
	float distance = direction.length();
	return distance <= m_radius;
}
