#pragma once
#include "Framework/Actor.h"


namespace kiko
{
	class Weapon : public kiko::Actor
	{
	public:
		CLASS_DECLARATION(Weapon)
		
		bool Initialize() override;
		void Update(float dt) override;

		void OnCollision(kiko::Actor* actor);

	private:
		float speed = 0;
	};

}