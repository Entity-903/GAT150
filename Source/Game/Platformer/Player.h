#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
	class Player : public kiko::Actor
	{
	public:
		CLASS_DECLARATION(Player)

		bool Initialize() override;
		void Update(float dt) override;

		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	private:
		float m_speed;
		float m_jump;
		int groundCount = 0;
		float m_health;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}