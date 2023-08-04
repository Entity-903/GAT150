#pragma once
#include "Framework/Resource/Resource.h"
#include "Core/Vector2.h"

struct SDL_Texture;

namespace kiko
{
	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		virtual bool Create(std::string filename, ...) override;

		bool Load(const std::string& filename, class Renderer& renderer);
		vec2 GetSize();

		friend class Renderer;
	private:
		SDL_Texture* m_texture = nullptr;

		// Inherited via Resource
	};
}