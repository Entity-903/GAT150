#pragma once

#include <box2d/include/box2d/box2d.h>

namespace kiko
{
	class ContactListener : public b2ContactListener
	{
	public:
		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;
	};
}