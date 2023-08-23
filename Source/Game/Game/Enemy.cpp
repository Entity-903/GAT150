#include "Enemy.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Weapon.h"

namespace kiko
{

	CLASS_DEFINITION(Enemy);

	bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<kiko::PhysicsComponent>();
		auto collisionComponent = GetComponent<kiko::CollisionComponent>();
		if (collisionComponent != nullptr)
		{
			kiko::RenderComponent* renderComponent = GetComponent<kiko::RenderComponent>();
			if (renderComponent != nullptr)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = renderComponent->GetRadius() * scale;
			}
		}

		return true;
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);

		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			kiko::vec2 direction = player->transform.position - transform.position;
			// Turn towards player
			float turnAngle = kiko::vec2::SignedAngle(forward, direction.Normalized());
			//transform.rotation += turnAngle * dt;

			m_physicsComponent->ApplyTorque(turnAngle);

			//Check if player is in front
			float angle = kiko::vec2::Angle(forward, direction.Normalized());
			if (std::fabs(turnAngle) < kiko::DegreesToRadians(30.0f))
			{
				// I see you!
			}
		
		}

		m_physicsComponent->ApplyForce(forward * m_speed);

		//transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
		transform.position.x = kiko::Wrap((float)transform.position.x, (float)kiko::g_renderer.GetWidth());
		transform.position.y = kiko::Wrap((float)transform.position.y, (float)kiko::g_renderer.GetHeight());

		if (m_fireRate != -1.0f)
		{
 			m_fireTime -= dt;
			if (m_fireTime <= 0)
			{
				m_fireTime = m_fireRate;


				// Weapon 1
				if (m_enemyDifficulty == 1 || m_enemyDifficulty >= 3) {

					auto weapon1 = INSTANTIATE(Weapon, "EnemyBasicWeapon");
					weapon1->transform = { transform.position, transform.rotation, 1 };
					weapon1->Initialize();

					m_scene->Add(std::move(weapon1));
				}

				// Weapon 2
				if (m_enemyDifficulty >= 2) {
					auto weapon2 = INSTANTIATE(Weapon, "EnemyBasicWeapon");
					weapon2->transform = { transform.position, transform.rotation + kiko::DegreesToRadians(10.0f) , 1 };
					weapon2->Initialize();

					m_scene->Add(std::move(weapon2));

				// Weapon 3
					auto weapon3 = INSTANTIATE(Weapon, "EnemyBasicWeapon");
					weapon3->transform = { transform.position, transform.rotation - kiko::DegreesToRadians(10.0f), 1 };
					weapon3->Initialize();

					m_scene->Add(std::move(weapon3));
				
				}

				kiko::g_audioSystem.PlayOneShot("Laser_Shoot");
			}
		}
	}

	void Enemy::OnCollision(Actor* other)
	{

		if (dynamic_cast<kiko::Weapon*>(other) != nullptr && other->tag == "Player")
		{
				m_health -= 10;
				std::cout << m_health << "\n";
				if (m_health <= 0)
				{

					// Create explosion using EmitterData
					kiko::EmitterData data;
					data.burst = true;
					data.burstCount = 100;
					data.spawnRate = 200;
					data.angle = 0;
					data.angleRange = kiko::Pi;
					data.lifetimeMin = 0.5f;
					data.lifetimeMax = 1.5f;
					data.speedMin = 50;
					data.speedMax = 250;
					data.damping = 0.5f;

					data.color = kiko::Color{ 1, 0, 0, 1 };

					kiko::Transform transform{ this->transform.position, 0, 1 };
					auto emitter = std::make_unique<kiko::Emitter>(transform, data);
					emitter->lifespan = 1.0f;
					m_scene->Add(std::move(emitter));

					// Points and Destruction
					kiko::EventManager::Instance().DispatchEvent("OnAddPoints", 100);
					//m_game->AddPoints(100);
					destroyed = true;
				}
		}
	}
	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_NAME_DATA(value, "speed", m_speed);
		READ_NAME_DATA(value, "turnRate", m_turnRate);
		READ_NAME_DATA(value, "health", m_health);
		READ_NAME_DATA(value, "fireTime", m_fireTime);
		READ_NAME_DATA(value, "fireRate", m_fireRate);
	}

}
