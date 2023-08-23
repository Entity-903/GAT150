#pragma once
#include "Framework/Framework.h"
#include "Framework/Actor.h"
#include "SpaceGame.h"
#include "Framework/Game.h"

namespace kiko
{
class Enemy : public kiko::Actor
{
	public:

		CLASS_DECLARATION(Enemy);

		/*Enemy(float speed, float turnRate, const kiko::Transform& transform, SpaceGame& spaceGame) :
			Actor{ transform },
			m_speed{ speed },
			spaceGame{ spaceGame },
			m_turnRate{ turnRate }
		{
			m_fireTime = 2.0f;
			m_fireRate = m_fireTime;
		}*/
		bool Initialize() override;

		void Update(float dt) override;
		void OnCollision(Actor* other) override;

	private:
		float m_speed = 0;
		float m_turnRate = 0;
		//SpaceGame& spaceGame;
		float m_fireTime = 0;
		float m_fireRate = 0;

		int m_enemyDifficulty = 1; // (spaceGame.GetScore() / 1000) != 0 ? spaceGame.GetScore() / 1000 : 1;
		float m_health = 20.0f * m_enemyDifficulty;

		kiko::PhysicsComponent* m_physicsComponent = nullptr;
	};
}
