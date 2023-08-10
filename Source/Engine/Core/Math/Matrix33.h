#pragma once

#include "Vector3.h"
#include "Vector2.h"

namespace kiko
{
	class Matrix33
	{
	public:
		vec3 rows[3];
		// [row][column]
		// rows[0] = vec3{ 0, 0, 0 }
		// rows[1] = vec3{ 0, 0, 0 }
		// rows[2] = vec3{ 0, 0, 0 }

		Matrix33() = default;
		Matrix33(const vec3& row1, const vec3& row2, const vec3& row3)
		{
			rows[0] = row1;
			rows[1] = row2;
		}

		vec3  operator [] (size_t index) const { return rows[index]; }
		vec3& operator [] (size_t index) { return rows[index]; }

		vec3 operator * (const vec3& v);
		Matrix33 operator * (const Matrix33& mx);

		static Matrix33 CreateScale(const vec2& scale);
		static Matrix33 CreateScale(float scale);
		static Matrix33 CreateRotation(float radians);

		static Matrix33 CreateIdentity();
	};

	inline vec3 Matrix33::operator*(const vec3& v)
	{
		// | a b |   | x | 
		// | c d | * | y |

		vec3 result;
		result.x = rows[0][0] * v.x + rows[0][1] * v.y;
		result.x = rows[1][0] * v.x + rows[1][1] * v.y;

		return vec3();
	}

	inline Matrix33 Matrix33::operator*(const Matrix33& mx)
	{
		// | a b |   | e f |
		// | c d | * | g h |

		Matrix33 result;
		result[0][0] = rows[0][0] * mx[0][0] + rows[0][1] * mx[1][0];
		result[0][1] = rows[0][0] * mx[0][1] + rows[0][1] * mx[1][1];
		result[1][0] = rows[1][0] * mx[0][0] + rows[1][1] * mx[1][0];
		result[1][1] = rows[1][0] * mx[0][1] + rows[1][1] * mx[1][1];

		return result;
	}

	inline Matrix33 Matrix33::CreateIdentity()
	{
		return
		{   // Matrix33
			{ 1, 0, 0 },  // vec3
			{ 0, 1, 0 },  // vec3
			{ 0, 0, 1 }   // vec3
		};
	}


	inline Matrix33 Matrix33::CreateScale(const vec2& scale)
	{
		Matrix33 mx = CreateIdentity();
		mx[0][0] = scale.x;
		mx[1][1] = scale.y;

		return mx;
	}

	inline Matrix33 Matrix33::CreateScale(float scale)
	{
		Matrix33 mx = CreateIdentity();
		mx[0][0] = scale;
		mx[1][1] = scale;

		return mx;
	}

	inline Matrix33 Matrix33::CreateRotation(float radians)
	{
		Matrix33 mx = CreateIdentity();
		float c = cos(radians);
		float s = sin(radians);

		mx[0][0] = c; mx[0][1] = -s;
		mx[1][0] = s; mx[1][1] = c;

		return mx;
	}
	using mat3 = Matrix33;
}