#pragma once

#include <cmath>

struct vec2
{
	float x;
	float y;

	vec2()
		: x(0.0f), y(0.0f)
	{
	}

	vec2(float x, float y)
		: x(x), y(y)
	{
	}

	float length() const
	{
		return std::sqrt(x * x + y * y);
	}

	vec2 normalize() const
	{
		float l = length();
		return
		{
			this->x / l,
			this->y / l
		};
	}

	float dot(const vec2& other) const
	{
		return this->x * other.x + this->y * other.y;
	}

	vec2& operator+=(const vec2& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	friend vec2 operator+(vec2 lhs, const vec2& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	vec2& operator-=(const vec2& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}

	friend vec2 operator-(vec2 lhs, const vec2& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

	vec2& operator*=(float rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		return *this;
	}

	friend vec2 operator*(vec2 lhs, float rhs)
	{
		lhs *= rhs;
		return lhs;
	}
};
