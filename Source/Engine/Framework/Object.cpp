#include "Object.h"

namespace kiko
{
	bool Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);

		return true;
	}
}