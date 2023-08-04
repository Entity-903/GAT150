#include "Font.h"
#include "Core/Logger.h"
#include <SDL2-2.28.0/include/SDL_ttf.h>

kiko::Font::Font(const std::string& filename, int fontSize)
{
	Load(filename, fontSize);
}

kiko::Font::~Font()
{
	if (!m_ttfFont) TTF_CloseFont(m_ttfFont);
}

bool kiko::Font::Create(std::string filename, ...)
{
	va_list args;

	va_start(args, filename);
	int fontSize = va_arg(args, int);
	va_end(args);

	return Load(filename, fontSize);
}

bool kiko::Font::Load(const std::string& filename, int fontSize)
{
	m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);
	if (!m_ttfFont)
	{
		WARNING_LOG("Failed to open font: " << filename);
		return false;
	}

	return true;
}

