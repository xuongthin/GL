#include "Rect.h"

Rect::Rect()
{
	m_Name = "Rect";
}

Rect::Rect(Vector2 position, Vector2 size, double mess, Vector2 velocity)
{
	m_Name = "Rect";

	m_SizeX = size.x;
	m_SizeY = size.y;
	//m_Mess = size.x * size.y;
	m_Mess = 1;

	SetPosition(position);
	//m_Position = position;
	SetVelocity(velocity);
	//m_Velocity = velocity;
}

Rect::~Rect()
{
	
}

void Rect::Render()
{
	VideoDriver::GetInstance()->FillRect(m_Position.x - m_SizeX / 2, m_Position.y - m_SizeY / 2, m_SizeX, m_SizeY);
}

bool Rect::CheckCollider(Circle * circle)
{
	Vector2 edges[4]; // LT RT RB LB
	edges[0] = Vector2(m_Position.x - m_SizeX / 2, m_Position.y - m_SizeY / 2);
	edges[1] = Vector2(m_Position.x + m_SizeX / 2, m_Position.y - m_SizeY / 2);
	edges[2] = Vector2(m_Position.x + m_SizeX / 2, m_Position.y + m_SizeY / 2);
	edges[3] = Vector2(m_Position.x - m_SizeX / 2, m_Position.y + m_SizeY / 2);

	for (int i = 0; i < 4; i++)
	{
		if (circle->CheckCollider(edges[i], edges[(i + 1) % 4]))
		{
			Vector2 directionFromVertexToCircle = Vector2::NormalFromLineToPoint(circle->GetPosition() ,edges[i], edges[(i + 1) % 4]);
			Vector2 directionFromCircleToRect = circle->GetPosition() - m_Position;
			SetVelocity(Vector2::SimpleVelocityAfterCollision(directionFromCircleToRect, m_Mess, m_Velocity, circle->GetMess(), circle->GetVelocity()));
			circle->SetVelocity(Vector2::SimpleVelocityAfterCollision(directionFromVertexToCircle, circle->GetMess(), circle->GetVelocity(), m_Mess, m_Velocity));
			return true;
		}
	}

	return false;
}

bool Rect::CheckCollider(Rect * other)
{
	//Vector2 thisEdges[4]; // LT RT LB RB
	//thisEdges[0] = Vector2(m_Position.x - m_SizeX / 2, m_Position.y - m_SizeY / 2);
	//thisEdges[1] = Vector2(m_Position.x + m_SizeX / 2, m_Position.y - m_SizeY / 2);
	//thisEdges[2] = Vector2(m_Position.x - m_SizeX / 2, m_Position.y + m_SizeY / 2);
	//thisEdges[3] = Vector2(m_Position.x + m_SizeX / 2, m_Position.y + m_SizeY / 2);

	//Vector2 othersEdges[4];

	//othersEdges[0] = Vector2(other->m_Position.x - other->m_SizeX / 2, other->m_Position.y - other->m_SizeY / 2);
	//othersEdges[1] = Vector2(other->m_Position.x + other->m_SizeX / 2, other->m_Position.y - other->m_SizeY / 2);
	//othersEdges[2] = Vector2(other->m_Position.x - other->m_SizeX / 2, other->m_Position.y + other->m_SizeY / 2);
	//othersEdges[3] = Vector2(other->m_Position.x + other->m_SizeX / 2, other->m_Position.y + other->m_SizeY / 2);

	//bool collide = false;

	//for (int i = 0; i < 4; i++)
	//{
	//	if (other->ContainPoint(thisEdges[i]))
	//	{
	//		collide = true;
	//	}
	//}

	//for (int i = 0; i < 4; i++)
	//{
	//	if (this->ContainPoint(othersEdges[i]))
	//	{
	//		collide = true;
	//	}
	//}

	//if (collide)
	//{
	//	Vector2 direction = other->m_Position - m_Position;
	//	//double amount = direction.length() - Vector2(m_SizeX, m_SizeY).length() / 2 - Vector2(other->m_SizeX, other->m_SizeY).length() / 2;
	//	//if (abs(direction.x) > abs(direction.y))
	//	//{
	//	//	if (direction.x > 0)
	//	//		direction = Vector2(1, 0);
	//	//	else 
	//	//		direction = Vector2(-1, 0);
	//	//}
	//	//else
	//	//{
	//	//	if (direction.y > 0)
	//	//		direction = Vector2(0, 1);
	//	//	else
	//	//		direction = Vector2(0, -1);
	//	//}		

	//	//AddForce(direction * amount);
	//	//other->AddForce(direction * (-amount));

	//	SetVelocity(Vector2::SimpleVelocityAfterCollision(direction, m_Mess, m_Velocity, other->m_Mess, other->m_Velocity));
	//	other->SetVelocity(Vector2::SimpleVelocityAfterCollision(Vector2() - direction, other->m_Mess, other->m_Velocity, m_Mess, m_Velocity));
	//}

	//return collide;

	Vector2 direction = other->m_Position - m_Position;

	if (abs(direction.x) <= (m_SizeX + other->m_SizeX) / 2 && abs(direction.y) <= (m_SizeY + other->m_SizeY) / 2)
	{
		double dx = (m_SizeX + other->m_SizeX) / 2 - direction.x;
		double dy = (m_SizeY + other->m_SizeY) / 2 - direction.y;

		Vector2 movement;
		//movement.

		//Move();

		return true;
	}

	return false;
}

bool Rect::CheckCollider(Plane * plane)
{
	Vector2 startPoint = plane->GetStartPoint();
	Vector2 endPoint = plane->GetEndPoint();

	Vector2 edges[4]; // LT RT RB LB
	edges[0] = Vector2(m_Position.x - m_SizeX / 2, m_Position.y - m_SizeY / 2);
	edges[1] = Vector2(m_Position.x + m_SizeX / 2, m_Position.y - m_SizeY / 2);
	edges[2] = Vector2(m_Position.x + m_SizeX / 2, m_Position.y + m_SizeY / 2);
	edges[3] = Vector2(m_Position.x - m_SizeX / 2, m_Position.y + m_SizeY / 2);
	
	for (int i = 0; i < 4; i++) 
	{
		if (Vector2::CheckTwoSegmentIntersect(startPoint, endPoint, edges[i], edges[(i + 1) % 4]))
		{			
			Vector2 direction = Vector2::NormalFromLineToPoint(m_Position, startPoint, endPoint);
			m_Velocity = Vector2::VelocityAfterCollision(m_Velocity, direction, 0.2);
			return true;
		}
	}

	return false;
}

bool Rect::ContainPoint(Vector2 pointer)
{
	bool axisX = m_Position.x - m_SizeX / 2 <= pointer.x && pointer.x <= m_Position.x + m_SizeX / 2;
	bool axixY = m_Position.y - m_SizeY / 2 <= pointer.y && pointer.y <= m_Position.y + m_SizeY / 2;
	return axisX && axixY;
}
