#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
	class Player : public kiko::Actor
	{
	public:
		CLASS_DECLARATION(Player)

		//Player(float speed, float turnRate, const kiko::Transform& transform) :
		//	Actor{ transform },
		//	m_speed{ speed },
		//	m_turnRate{ turnRate }
		//{}

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;

	private:
		float m_speed = 0;
		float m_turnRate = 0;
		float m_health = 100.0f;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}