#include "Json.h"
#include "rapidjson/include/rapidjson/istreamwrapper.h"

#include "FileIO.h"
#include "Logger.h"
#include <sstream>


namespace kiko
{
	bool Json::Load(const std::string& filename, rapidjson::Document& document)
	{
		std::string buffer;
		if (!readFile(filename, buffer))
		{
			WARNING_LOG("Cannot open file: " << filename);
			return false;
		}

		std::stringstream stream(buffer);
		rapidjson::IStreamWrapper istream(stream);

		// Parse Stream to Json
		document.ParseStream(istream);
		if (!document.IsObject())
		{
			WARNING_LOG("Json File cannot be Parsed: " << filename);
			return false;
		}

		return true;
	}
	bool Json::Read(const rapidjson::Value& value, const std::string& name, int& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
		{
			if (required) ERROR_LOG("Cannot Read Required Json Data: " << name.c_str());
			return false;
		}

		data = value[name.c_str()].GetInt();

		return true;
	}
	bool Json::Read(const rapidjson::Value& value, const std::string& name, float& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber())
		{
			if (required) ERROR_LOG("Cannot Read Required Json Data: " << name.c_str());
			return false;
		}

		data = value[name.c_str()].GetFloat();

		return true;
	}
	bool Json::Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
		{
			if (required) ERROR_LOG("Cannot Read Required Json Data: " << name.c_str());
			return false;
		}

		data = value[name.c_str()].GetBool();

		return true;
	}
	bool Json::Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
		{
			if (required) ERROR_LOG("Cannot Read Required Json Data: " << name.c_str());
			return false;
		}

		data = value[name.c_str()].GetString();

		return true;
	}
	bool Json::Read(const rapidjson::Value& value, const std::string& name, vec2& data, bool required)
	{
		// Check if 'name' member exists and is an array with 2 elements
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
		{
			if (required) ERROR_LOG("Cannot Read Required Json Data: " << name.c_str());
			return false;
		}

		// Create Json Array Object
		auto& array = value[name.c_str()];
		// Get Array Values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid Json Data Type: " << name.c_str());
				return false;
			}

		data[i] = array[i].GetFloat();
		}

		return true;
	}
	bool Json::Read(const rapidjson::Value& value, const std::string& name, Color& data, bool required)
	{
		// Check if 'name' member exists and is an array with 4 elements
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
		{
			if (required) ERROR_LOG("Cannot Read Required Json Data: " << name.c_str());
			return false;
		}

		// Create Json Array Object
		auto& array = value[name.c_str()];
		// Get Array Values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid Json Data Type: " << name.c_str());
				return false;
			}

			data[i] = array[i].GetFloat();
		}

		return true;
	}
	bool Json::Read(const rapidjson::Value& value, const std::string& name, Rect& data, bool required)
	{
		// Check if 'name' member exists and is an array with 4 elements
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4)
		{
			if (required) ERROR_LOG("Cannot Read Required Json Data: " << name.c_str());
			return false;
		}

		// Create Json Array Object
		auto& array = value[name.c_str()];
		// Get Array Values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid Json Data Type: " << name.c_str());
				return false;
			}

			data[i] = array[i].GetInt();
		}

		return true;
	}
}