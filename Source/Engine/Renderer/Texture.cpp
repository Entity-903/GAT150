#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"
#include "SDL2-2.28.0/include/SDL_image.h"

namespace kiko
{
	Texture::~Texture()
	{
		if (m_texture) SDL_DestroyTexture(m_texture);
	}
	bool Texture::Load(const std::string& filename, Renderer& renderer)
	{
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface)
		{
			WARNING_LOG("No Surface Provided!")
			return false;
		}

		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
		if (!m_texture)
		{
			WARNING_LOG("No Texture Provided!");
			return false;
		}

		return true;
	}
	vec2 Texture::GetSize()
	{
		ASSERT_LOG(m_texture != NULL, "Texture is NULL!");
		SDL_Point point;
		SDL_QueryTexture(m_texture, NULL, NULL, &point.x, &point.y);

		return vec2( point.x, point.y );
	}
	bool Texture::Create(std::string filename, ...)
	{
		// va_list - Type to hold information about variable arguments
		va_list args;

		// va_start - Enables access to variadic function arguments
		va_start(args, filename);

		// va_arg - accesses the next variadic function arguments
		Renderer& renderer = va_arg(args, Renderer);

		// va_end - Ends traversal of the variadic function arguments
		va_end(args);

		return Load(filename, renderer);
	}
}