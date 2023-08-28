#include "Enemy.h"
#include "Player.h"
#include "PlatformGame.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"

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
			m_physicsComponent->ApplyForce(direction.Normalized() * m_speed);
		}


		
	}

	void Enemy::OnCollisionEnter(Actor* other)
	{

		if (other->tag == "Player")
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
		READ_NAME_DATA(value, "health", m_health);
	}

}
