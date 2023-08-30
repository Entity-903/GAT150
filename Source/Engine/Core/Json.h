#pragma once
#include "rapidjson/include/rapidjson/document.h"
#include "Core/Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Rect.h"
#include <string>
#include <vector>

#define READ_DATA(value, data) kiko::Json::Read(value, #data, data)
#define READ_DATA_REQUIRED(value, data) kiko::Json::Read(value, #data, data, true)
#define READ_NAME_DATA(value, name, data) kiko::Json::Read(value, name, data)
#define READ_NAME_DATA_REQUIRED(value, name, data) kiko::Json::Read(value, name, data, true)
#define HAS_DATA(value, data) value.HasMember(#data)
#define GET_DATA(value, data) value[#data]

namespace kiko
{
	class Json
	{
	public:
		static bool Load(const std::string& filename, rapidjson::Document& document);
		static bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, vec2& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, Color& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, Rect& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, std::vector<int>& data, bool required = false);
	};

	using json_t = rapidjson::Value;
}