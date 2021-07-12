#pragma once

#include <string>
#include <math.h>
#include <vector>
#include "videoDriver.h"
#include "Vector2.h"
//#include "Circle.h"
//#include "Rect.h"
//#include "Plane.h"

class Object
{
private:
	const double ms_Gravity = 20.0;
	bool m_RefreshDeltaVelocity = true;
	bool m_ApplyForce = false;
protected:
	Vector2 m_PreviousPosition;
	Vector2 m_Position;

	Vector2 m_Velocity;
	Vector2 m_DeltaVelocity;
	Vector2 m_SumForce;
	std::string m_Name;
	bool m_isStatic = false;
	double m_Mess;
	bool m_isLooked = false;
public:
	Object();
	virtual ~Object();
	double GetMess();
	Vector2 GetPosition();
	void SetPosition(Vector2);
	Vector2 GetVelocity();
	void SetVelocity(Vector2);
	void Lock();
	void Unlock();
	void Move(Vector2);
	void AddForce(Vector2);
	std::string GetName() { return m_Name; }
	virtual void Render();
	void Update(float frameTime);
	void CollideHandle();
	void CollideHandle(std::string);
	void CollideHandle(Vector2, double);
	void CollideHandle(double othersMess, Vector2 othersVelocity);
};

