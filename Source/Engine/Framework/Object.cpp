#include "Object.h"

namespace kiko
{
	void Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);
	}
}