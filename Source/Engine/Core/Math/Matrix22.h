#pragma once

#include "Vector2.h"

namespace kiko
{
	class Matrix22
	{
	public:
		vec2 rows[2];
		// [row][column]
		// rows[0] = vec2{ 0, 0 }
		// rows[1] = vec2{ 0, 0 }

		Matrix22() = default;
		Matrix22(const vec2& row1, const vec2& row2)
		{
			rows[0] = row1;
			rows[1] = row2;
		}

		vec2  operator [] (size_t index) const { return rows[index]; }
		vec2& operator [] (size_t index) { return rows[index]; }

		vec2 operator * (const vec2& v);
		Matrix22 operator * (const Matrix22& mx);

		static Matrix22 CreateScale(const vec2& scale);
		static Matrix22 CreateScale(float scale);
		static Matrix22 CreateRotation(float radians);

		static Matrix22 CreateIdentity();
	};

	inline vec2 Matrix22::operator*(const vec2& v)
	{
		// | a b |   | x | 
		// | c d | * | y |

		vec2 result;
		result.x = rows[0][0] * v.x + rows[0][1] * v.y;
		result.y = rows[1][0] * v.x + rows[1][1] * v.y;

		return result;
	}

	inline Matrix22 Matrix22::operator*(const Matrix22& mx)
	{
		// | a b |   | e f |    | ? ? |
		// | c d | * | g h | =  | ? ? |

		Matrix22 result;
		result[0][0] = rows[0][0] * mx[0][0] + rows[0][1] * mx[1][0];
		result[0][1] = rows[0][0] * mx[0][1] + rows[0][1] * mx[1][1];
		result[1][0] = rows[1][0] * mx[0][0] + rows[1][1] * mx[1][0];
		result[1][1] = rows[1][0] * mx[0][1] + rows[1][1] * mx[1][1];

		return result;
	}

	inline Matrix22 Matrix22::CreateIdentity()
	{
		return
		{   // Matrix22
			{ 1, 0 }, // vec2
			{ 0, 1 }  // vec2
		};
	}


	inline Matrix22 Matrix22::CreateScale(const vec2& scale)
	{
		return
		{   // Matrix22
			{ scale.x, 0.0f }, // vec2
			{ 0.0f, scale.y }  // vec2
		};
	}

	inline Matrix22 Matrix22::CreateScale(float scale)
	{
		return
		{   // Matrix22
			{ scale, 0.0f }, // vec2
			{ 0.0f, scale }  // vec2
		};
	}

	inline Matrix22 Matrix22::CreateRotation(float radians)
	{
		float c = cos(radians);
		float s = sin(radians);

		return
		{   // Matrix22
			{ c, -s }, // vec2
			{ s, c }  // vec2
		};
	}
	using mat2 = Matrix22;
}