#pragma once

#include "Vector2.h"
#include "Matrix22.h"

namespace kiko
{

	class Transform
	{
	public:
		vec2 position;
		float rotation = 0;
		float scale = 1;

	public:
		Transform() = default;

		Transform(const vec2& position, float rotation, float scale = 1) :
			position{ position },
			rotation{ rotation },
			scale{ scale }
		{}

		mat2 GetMatrix() const
		{
			mat2 ms = mat2::CreateScale(scale);
			mat2 mr = mat2::CreateRotation(rotation);

			//mat2 mx = ms * mr;

			return ms * mr;
		}
	};
}