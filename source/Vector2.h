#pragma once
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "videoDriver.h"

using namespace std;

class Vector2
{
public:
	double x;
	double y;

	Vector2();

	Vector2(const Vector2 &vector);

	Vector2(double x, double y);

	static double Distance(Vector2 first, Vector2 second);

	static double PointToLine(Vector2 point, Vector2 startLine, Vector2 endLine);

	static double PointToLine(Vector2 point, double a, double b, double c);

	static bool CheckTwoSegmentIntersect(Vector2 startSegment1, Vector2 endSegment1, Vector2 startSegment2, Vector2 endSegment2);

	static bool CheckTwoPointWithLine(Vector2 point1, Vector2 point2, Vector2 startLine, Vector2 endLine);
	
	static Vector2 SimpleVelocityAfterCollision(Vector2 direction, double mess1, Vector2 velocity1, double mess2, Vector2 velocity2);

	static Vector2 VelocityAfterCollision(Vector2 direction, double mess1, Vector2 velocity1, double mess2, Vector2 velocity2);

	static Vector2 VelocityAfterCollision(Vector2 velocity, Vector2 normalSurface, double bounce);

	static Vector2 NormalFromLineToPoint(Vector2 point, Vector2 startLine, Vector2 endLine);

	static Vector2 Projection(Vector2 vector, Vector2 direction);

	static double Dot(Vector2 v1, Vector2 v2);

	static double CosBetweenTwoVectors(Vector2 first, Vector2 second);

	double angle();

	double length();

	Vector2 normalize();

	Vector2 Normalize();

	Vector2 Projection(Vector2 direction);

	double distanceToSegment(Vector2 startLine, Vector2 endLine);

	Vector2 operator+ (const Vector2& addition);

	Vector2 operator- (const Vector2& subtraction);

	Vector2 operator* (double multiplication);

	Vector2 operator/ (double division);

	bool operator== (const Vector2& comparator);

	Vector2 operator+= (const Vector2& addition);

	Vector2 operator-= (const Vector2& subtraction);

	virtual ~Vector2();
};

