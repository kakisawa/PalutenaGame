#pragma once

#include <cmath>

// 2éüå≥ÉxÉNÉgÉã
class Vec2
{
public:
	float x;
	float y;

public:
	Vec2()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vec2(float posX, float posY)
	{
		x = posX;
		y = posY;
	}
	// Vec2 = (Vec2 += Vec2)
	Vec2 operator+=(const Vec2& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}
	// Vec2 = Vec2 + Vec2
	Vec2 operator+(const Vec2& vec) const
	{
		Vec2 temp{ x + vec.x , y + vec.y };
		return temp;
	}

	// Vec2 = (Vec2 -= Vec2)
	Vec2 operator-=(const Vec2& vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	// Vec2 = Vec2 - Vec2
	Vec2 operator-(const Vec2& vec) const
	{
		Vec2 temp{ x - vec.x , y - vec.y };
		return temp;
	}

	// Vec2 = (Vec2 *= float)
	Vec2 operator*=(float scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}
	// Vec2 = Vec2 * float
	Vec2 operator*(float scale) const
	{
		Vec2 temp{ x * scale , y * scale };
		return temp;
	}

	// Vec2 = (Vec2 /= float)
	Vec2 operator/=(float scale)
	{
		x /= scale;
		y /= scale;
		return *this;
	}
	// Vec2 = Vec2 / float
	Vec2 operator/(float scale) const
	{
		Vec2 temp{ x / scale , y / scale };
		return temp;
	}

	// í∑Ç≥ÇÃéÊìæ
	float length()
	{
		return sqrtf((x * x) + (y * y));
	}

	// ê≥ãKâª Vec2 = Vec2.normalize()
	Vec2 normalize()
	{
		float len = length();
		if (len == 0)
		{
			return *this;
		}
		return (*this) / len;
	}
};