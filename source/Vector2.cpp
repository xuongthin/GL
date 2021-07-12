#include "Vector2.h"

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(const Vector2 & vector)
{
	x = vector.x;
	y = vector.y;
}

Vector2::Vector2(double x, double y)
{
	this->x = x;
	this->y = y;
}

double Vector2::Distance(Vector2 first, Vector2 second)
{
	Vector2 direction = second - first;
	//double distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	double distance = direction.length();
	return distance;
}

double Vector2::PointToLine(Vector2 point, Vector2 startLine, Vector2 endLine)
{
	double A = point.x - startLine.x;
	double B = point.y - startLine.y;
	double C = endLine.x - startLine.x;
	double D = endLine.y - startLine.y;

	double dot = A * C + B * D;
	double length_sqr = C * C + D * D;
	double param = -1.0;

	if (length_sqr != 0)
		param = dot / length_sqr;

	double xx, yy;

	xx = startLine.x + param * C;
	yy = startLine.y + param * D;

	double dx = point.x - xx;
	double dy = point.y - yy;

	return sqrt(dx * dx + dy * dy);
}

double Vector2::PointToLine(Vector2 point, double a, double b, double c)
{
	double distance = abs(a * point.x + b * point.y + c) / Vector2(a, b).length();
	return distance;
}

bool Vector2::CheckTwoSegmentIntersect(Vector2 s1, Vector2 e1, Vector2 s2, Vector2 e2)
{
	if (max(s1.x, e1.x) < min(s2.x, e2.x)) return false;
	if (min(s1.x, e1.x) > max(s2.x, e2.x)) return false;

	if (max(s1.y, e1.y) < min(s2.y, e2.y)) return false;
	if (min(s1.y, e1.y) > max(s2.y, e2.y)) return false;

	bool segment1CutLine2 = !CheckTwoPointWithLine(s1, e1, s2, e2);

	bool segment2CutLine1 = !CheckTwoPointWithLine(s2, e2, s1, e1);

	return segment1CutLine2 && segment2CutLine1;
}

bool Vector2::CheckTwoPointWithLine(Vector2 p1, Vector2 p2, Vector2 sL, Vector2 eL)
{
	double i = (p1.x - sL.x) / (eL.x - sL.x) - (p1.y - sL.y) / (eL.y - sL.y);
	double j = (p2.x - sL.x) / (eL.x - sL.x) - (p2.y - sL.y) / (eL.y - sL.y);
	return i * j >= 0;
}

Vector2 Vector2::SimpleVelocityAfterCollision(Vector2 direction, double mess1, Vector2 velocity1, double mess2, Vector2 velocity2)
{
	direction.Normalize();
	if (CosBetweenTwoVectors(velocity1 , velocity2) < 0 && CosBetweenTwoVectors(velocity1, direction) < 0) return velocity1;

	Vector2 velocity = (velocity1 * (mess1 - mess2) + velocity2 * mess2 * 2) / (mess1 + mess2);
	return velocity;
}

Vector2 Vector2::VelocityAfterCollision(Vector2 direction, double mess1, Vector2 velocity1, double mess2, Vector2 velocity2)
{
	/*double delta1 = velocity1.angle();
	double delta2 = velocity2.angle();

	double v1 = velocity1.length();
	double v2 = velocity2.length();

	double vx = (v1 * cos(delta1 - contactAngle) * (mess1 - mess2) + 2 * mess2 * v2 * cos(delta2 - contactAngle)) * cos(contactAngle) / (mess1 + mess2) + v1 * sin(delta1 - contactAngle) * cos(contactAngle + PI/2);
	double vy = (v1 * cos(delta1 - contactAngle) * (mess1 - mess2) + 2 * mess2 * v2 * cos(delta2 - contactAngle)) * sin(contactAngle) / (mess1 + mess2) + v1 * sin(delta1 - contactAngle) * sin(contactAngle + PI/2);
*/
	if (CosBetweenTwoVectors(velocity1, velocity2) < 0 && CosBetweenTwoVectors(velocity1, direction) < 0) return velocity1;

	Vector2 velocity = velocity1 - direction * 2 * mess2 / (mess1 + mess2) * Dot(velocity1 - velocity2, direction) / Dot(direction, direction);
	return velocity;
}

Vector2 Vector2::VelocityAfterCollision(Vector2 velocity, Vector2 normalSurface, double bounce)
{
	if (CosBetweenTwoVectors(velocity, normalSurface) > 0) return velocity;
	
	double cos = abs(Vector2::CosBetweenTwoVectors(velocity, normalSurface));
	Vector2 addition = normalSurface * velocity.length() * cos * 2;
	Vector2 result = velocity + addition;
	return result * bounce;
}

Vector2 Vector2::NormalFromLineToPoint(Vector2 point, Vector2 startLine, Vector2 endLine)
{
	double A = point.x - startLine.x;
	double B = point.y - startLine.y;
	double C = endLine.x - startLine.x;
	double D = endLine.y - startLine.y;

	double dot = A * C + B * D;
	double length_sqr = C * C + D * D;
	double param = -1.0;

	if (length_sqr != 0)
		param = dot / length_sqr;

	double xx, yy;

	if (param < 0) {
		xx = startLine.x;
		yy = startLine.y;
	}
	else if (param > 1) {
		xx = endLine.x;
		yy = endLine.y;
	}
	else {
		xx = startLine.x + param * C;
		yy = startLine.y + param * D;
	}

	double dx = point.x - xx;
	double dy = point.y - yy;

	Vector2 result = Vector2(dx, dy);
	result.Normalize();

	return result;
}

Vector2 Vector2::Projection(Vector2 vector, Vector2 direction)
{
	double len = vector.length();
	double cos = CosBetweenTwoVectors(vector, direction);
	direction.Normalize();
	return direction * len * cos;
}

double Vector2::Dot(Vector2 v1, Vector2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

double Vector2::CosBetweenTwoVectors(Vector2 first, Vector2 second)
{
	double cos = first.x * second.x + first.y * second.y;
	cos = cos / (first.length() * second.length());
	return cos;
}

double Vector2::angle()
{
	Vector2 temp = Vector2(x, y);
	temp.Normalize();
	return atan2(y, x);
}

double Vector2::length()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

Vector2 Vector2::normalize()
{
	Vector2 temp = Vector2(x, y);
	temp.Normalize();
	return temp;
}

Vector2 Vector2::Normalize()
{
	double len = length();

	if (len == 0) return *this;

	x /= len;
	y /= len;

	return *this;
}

Vector2 Vector2::Projection(Vector2 direction)
{
	double cos = CosBetweenTwoVectors(*this, direction);
	double len = length() * cos;
	*this = direction.Normalize() * len;
	return *this;
}

double Vector2::distanceToSegment(Vector2 startLine, Vector2 endLine)
{
	Vector2 point = Vector2(x, y);

	double A = point.x - startLine.x;
	double B = point.y - startLine.y;
	double C = endLine.x - startLine.x;
	double D = endLine.y - startLine.y;

	double dot = A * C + B * D;
	double length_sqr = C * C + D * D;
	double param = -1.0;

	if (length_sqr != 0)
		param = dot / length_sqr;

	double xx, yy;

	if (param < 0) {
		xx = startLine.x;
		yy = startLine.y;
	}
	else if (param > 1) {
		xx = endLine.x;
		yy = endLine.y;
	}
	else {
		xx = startLine.x + param * C;
		yy = startLine.y + param * D;
	}

	double dx = point.x - xx;
	double dy = point.y - yy;

	return sqrt(dx * dx + dy * dy);
}

Vector2 Vector2::operator+(const Vector2 & addition)
{
	Vector2 temp;
	temp.x = x + addition.x;
	temp.y = y + addition.y;
	return temp;
}

Vector2 Vector2::operator-(const Vector2 & subtraction)
{
	Vector2 temp;
	temp.x = x - subtraction.x;
	temp.y = y - subtraction.y;
	return temp;
}

Vector2 Vector2::operator*(double multiplication)
{
	Vector2 temp;
	temp.x = x * multiplication;
	temp.y = y * multiplication;
	return temp;
}

Vector2 Vector2::operator/(double division)
{
	Vector2 temp;
	temp.x = x / division;
	temp.y = y / division;
	return temp;
}

bool Vector2::operator==(const Vector2 & comparator)
{
	return abs(x - comparator.x) < 0.001 && abs(y - comparator.y) < 0.001;
}

Vector2 Vector2::operator+=(const Vector2 & addition)
{
	x += addition.x;
	y += addition.y;
	return *this;
}

Vector2 Vector2::operator-=(const Vector2 & subtraction)
{
	x -= subtraction.x;
	y -= subtraction.y;
	return *this;
}


Vector2::~Vector2()
{
}
