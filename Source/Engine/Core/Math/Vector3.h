#pragma once
#include <cmath>
#include <sstream>

namespace kiko
{
	class Vector3
	{
	public:
		float x, y;

	public:
		Vector3() : x{ 0 }, y{ 0 } {}
		Vector3(float v) : x{ v }, y{ v } {}
		Vector3(float x, float y) : x{ x }, y{ y } {}
		Vector3(int x, int y) : x{ (float)x }, y{ (float)y } {}

		Vector3 operator + (const Vector3& v) const { return Vector3(x + v.x, y + v.y); }
		Vector3 operator - (const Vector3& v) const { return Vector3(x - v.x, y - v.y); }
		Vector3 operator * (const Vector3& v) const { return Vector3(x * v.x, y * v.y); }
		Vector3 operator / (const Vector3& v) const { return Vector3(x / v.x, y / v.y); }

		Vector3 operator + (float s) const { return Vector3(x + s, y + s); }
		Vector3 operator - (float s) const { return Vector3(x - s, y - s); }
		Vector3 operator * (float s) const { return Vector3(x * s, y * s); }
		Vector3 operator / (float s) const { return Vector3(x / s, y / s); }

		Vector3& operator += (const Vector3& v) { x += v.x; y += v.y; return *this; }
		Vector3& operator -= (const Vector3& v) { x -= v.x; y -= v.y; return *this; }
		Vector3& operator *= (const Vector3& v) { x *= v.x; y *= v.y; return *this; }
		Vector3& operator /= (const Vector3& v) { x /= v.x; y /= v.y; return *this; }

		float LengthSqr() const { return (x * x) + (y * y); }
		float Length() const { return std::sqrt(LengthSqr()); }

		inline float DistanceSqr(const Vector3& v) const { return (v - *this).LengthSqr(); }
		inline float Distance(const Vector3& v) const { return (v - *this).Length(); }

		Vector3 Normalized() const { return *this / Length(); }
		void Normalize() { *this /= Length(); }

		static float Dot(const Vector3& v1, const Vector3& v2);
	};

	// get the dot product beteen v1 and v2 https://www.falstad.com/dotproduct/
	inline float Vector3::Dot(const Vector3& v1, const Vector3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	using vec3 = Vector3;
}