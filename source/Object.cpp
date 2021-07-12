#include "Object.h"


Object::Object()
{
}

Object::~Object()
{
}

double Object::GetMess()
{
	return m_Mess;
}

Vector2 Object::GetPosition()
{
	return m_Position;
}

void Object::SetPosition(Vector2 position)
{
	m_PreviousPosition = position;
	m_Position = position;
}

Vector2 Object::GetVelocity()
{
	return m_Velocity;
}

void Object::SetVelocity(Vector2 velocity)
{
	if (!m_isLooked)
		m_Velocity = velocity;
}

void Object::Lock()
{
	m_isLooked = true;
	m_PreviousPosition = m_Position;
}

void Object::Unlock()
{
	m_isLooked = false;
}

void Object::Move(Vector2 movement)
{
	m_PreviousPosition = m_Position;
	m_Position += movement;
	m_SumForce = Vector2();
}

void Object::AddForce(Vector2 force)
{
	m_SumForce += force;
}

void Object::Render()
{
	printf("rendering... \n");
}

void Object::Update(float frameTime)
{
	if (m_isLooked)
	{
		if (frameTime > 0.001)
		{
			m_Velocity = (m_Position - m_PreviousPosition) / frameTime;
		}
		m_PreviousPosition = m_Position;
		return;
	}

	if (!m_isStatic)
	{
		/*if (m_RefreshDeltaVelocity)
		{
			m_DeltaVelocity = m_Velocity * frameTime;
			m_RefreshDeltaVelocity = false;
		}
		else 
		{
			m_DeltaVelocity = m_Position - m_PreviousPosition;
		}

		m_PreviousPosition = m_Position;

		if (!(m_SumForce == Vector2() ))
		{
			m_Position += m_SumForce / m_Mess * frameTime * frameTime;
			m_SumForce = Vector2();
		}

		m_Position += m_DeltaVelocity + Vector2(0, ms_Gravity) * frameTime * frameTime;*/
		m_PreviousPosition = m_Position;
		m_Position += m_Velocity * frameTime;
		m_Velocity += Vector2(0, ms_Gravity) * frameTime;

		if (!(m_SumForce == Vector2()))
		{
			m_Velocity += m_SumForce / m_Mess * frameTime;
			m_SumForce = Vector2();
		}
	}
}

void Object::CollideHandle()
{
	m_Position = m_PreviousPosition;
}

void Object::CollideHandle(std::string direction)
{
	if (direction == "horizontal")
		m_Position.x = m_PreviousPosition.x;
	else if (direction == "vertical")
		m_Position.y = m_PreviousPosition.y;
}

void Object::CollideHandle(Vector2 direction, double amount)
{
	m_Position += direction * amount;
}

void Object::CollideHandle(double othersMess, Vector2 othersVelocity)
{
	m_Velocity = ( m_Velocity * (m_Mess - othersMess) + othersVelocity * 2 * othersMess ) / (m_Mess + othersMess);
}

//bool Object::CheckCollider(std::vector<Object*> objects)
//{
//	if (m_isStatic) return;
//
//	bool collide = false;
//
//	for (int i = 0; i < objects.size() - 1; i++)
//	{
//		Object* obj = objects.at(i);
//		if (obj != this)
//		{
//			if (obj->GetName() == "Circle")
//			{
//				Circle* other = (Circle*) obj;
//				CheckCollider(other);
//			}
//			else if (obj->GetName() == "Rect")
//			{
//				Rect* other = (Rect*) obj;
//				CheckCollider(other);
//			}
//			else if (obj->GetName() == "Plane")
//			{
//				Plane* other = (Plane*) obj;
//				CheckCollider(other);
//			}
//		}
//	}
//}
//
//bool Object::CheckCollider(Circle * circle)
//{
//	if (m_Name == "Circle")
//	{
//		Circle* main = (Circle*) this;
//		main->CheckCollider(circle);
//	}
//	else if (m_Name == "Rect")
//	{
//		Rect* main = (Rect*) this;
//		main->CheckCollider(circle);
//	}
//}
//
//bool Object::CheckCollider(Rect * rect)
//{
//	if (m_Name == "Circle")
//	{
//		Circle* main = (Circle*) this;
//		main->CheckCollider(rect);
//	}
//	else if (m_Name == "Rect")
//	{
//		Rect* main = (Rect*) this;
//		main->CheckCollider(rect);
//	}
//}
//
//bool Object::CheckCollider(Plane * plane)
//{
//	if (m_Name == "Circle")
//	{
//		Circle* main = (Circle*) this;
//		main->CheckCollider(plane);
//	}
//	else if (m_Name == "Rect")
//	{
//		Rect* main = (Rect*) this;
//		main->CheckCollider(plane);
//	}
//}
