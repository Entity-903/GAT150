#pragma once
#include <string>

namespace kiko
{
	class Object
	{
	public :
		Object() = default;
		Object(const std::string& name) : m_name{ name } {}
		virtual ~Object() { OnDestroy(); }

		virtual bool Initialize() { return true; };
		virtual void OnDestroy() {};

	protected:
		std::string m_name;
	};
}