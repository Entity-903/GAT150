#pragma once
#include "Framework/Framework.h"
#include "PlatformGame.h"

namespace kiko
{
	class Enemy : public kiko::Actor
	{
	public:

		CLASS_DECLARATION(Enemy)

			bool Initialize() override;

		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;

	private:
		float m_speed = 0;

		float m_health = 20.0f;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}
