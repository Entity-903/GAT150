#pragma once

#include "Framework/Components/PhysicsComponent.h"
#include "Framework/Actor.h"


namespace kiko
{
	class Weapon : public kiko::Actor
	{
	public:
		CLASS_DECLARATION(Weapon)
		
		bool Initialize() override;
		void Update(float dt) override;

		void OnCollisionEnter(kiko::Actor* actor);

	private:
		float speed = 0;
		PhysicsComponent* m_physicsComponent = nullptr;
	};

}