#include "VectorOps.h"
#include <math.h>

using namespace sf;

float VectorOps::Magnitude(Vector2f v)
{
	return sqrt(VectorOps::MagnitudeSquared(v));
}

float VectorOps::MagnitudeSquared(Vector2f v)
{
	return v.x*v.x + v.y*v.y;
}

float VectorOps::Dot(Vector2f v1, Vector2f v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

float VectorOps::Cross(Vector2f v1, Vector2f v2)
{
	return v1.x*v2.y - v2.x*v1.y;
}

float VectorOps::AngleBetween(Vector2f v1, Vector2f v2)
{
	float cosTheta = Dot(v1, v2) / (Magnitude(v1)*Magnitude(v2));
	return acos(cosTheta);
}

Vector2f VectorOps::Normalise(Vector2f v)
{
	return v / Magnitude(v);
}

Vector2f VectorOps::RotateAnticlockwise(Vector2f v, float angle)
{
	float sinTheta = sin(angle);
	float cosTheta = cos(angle);
	return Vector2f(v.x*cosTheta + v.y*sinTheta, -v.x*sinTheta + v.y*cosTheta);
}
