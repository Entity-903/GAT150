#pragma once
#include "MathUtils.h"
#include <cstdint>
#include <iostream>
#include <string>

namespace kiko
{
	class Color
	{
	public:
		float r, g, b, a;

	public:
		Color() : r(0), g(0), b(0), a(0) {}
		Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

		static uint8_t ToInt(float c) { return static_cast<uint8_t>(Clamp(c, 0.0f, 1.0f) * 255); }
	};

	inline std::istream& operator >> (std::istream& stream, Color& color)
	{
		std::string line;
		std::getline(stream, line);

		// line = { ##, ##, ## }
		// Red
		std::string str = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
		color.r = std::stof(str);

		line = line.substr(line.find(",") + 1);

		// Green
		str = line.substr(0, line.find(","));
		color.g = std::stof(str);

		// Blue
		str = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
		color.b = std::stof(str);

		// Alpha
		color.a = 1;

		return stream;
	}
}