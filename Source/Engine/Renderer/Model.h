#pragma once
#include "Core/Core.h"
#include "Framework/Resource/ResourceManager.h"
#include <vector>

namespace kiko
{
	class Renderer;

	class Model : public Resource
	{
	public:
		Model() = default;
		Model(const std::vector<vec2>& points) : m_points{ points } {}

		bool Create(std::string filename, ...);
		bool Load(const std::string& filename);

		void Draw(Renderer& renderer, const Transform& transform);

		float GetRadius();

	private:
		std::vector<vec2> m_points;
		Color m_color;
		float m_radius = 0;
	};
}