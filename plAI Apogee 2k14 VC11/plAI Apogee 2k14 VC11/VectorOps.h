#pragma once
#include <SFML\Graphics.hpp>

namespace sf
{
	class VectorOps
	{
	public:
		static float Magnitude(Vector2f v);
		static float MagnitudeSquared(Vector2f v);
		static float Dot(Vector2f v1, Vector2f v2);
		static float Cross(Vector2f v1, Vector2f v2);
		static float AngleBetween(Vector2f v1, Vector2f v2);
		static Vector2f Normalise(Vector2f v);
		static Vector2f RotateAnticlockwise(Vector2f v, float angle);
	};
};

