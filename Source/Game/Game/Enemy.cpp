#include "Enemy.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Weapon.h"

bool Enemy::Initialize()
{
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
		transform.rotation += turnAngle * dt;
		//Check if player is in front
		float angle = kiko::vec2::Angle(forward, direction.Normalized());
		if (std::fabs(turnAngle) < kiko::DegreesToRadians(30.0f))
		{
			// I see you!
		}
		
	}

	transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	transform.position.x = kiko::Wrap((float)transform.position.x, (float)kiko::g_renderer.GetWidth());
	transform.position.y = kiko::Wrap((float)transform.position.y, (float)kiko::g_renderer.GetHeight());

	if (m_fireRate != -1.0f)
	{
		m_fireTime -= dt;
		if (m_fireTime <= 0)
		{
			m_fireTime = m_fireRate;

			if (m_enemyDifficulty == 1 || m_enemyDifficulty >= 3) {
			kiko::Transform transform1{ transform.position, transform.rotation, 1};
			std::unique_ptr<Weapon> weapon1 = std::make_unique<Weapon>(400.0f, transform1);
			weapon1->tag = "Enemy";

			auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
			collisionComponent->m_radius = 30.0f;
			weapon1->AddComponent(std::move(collisionComponent));

			std::unique_ptr<kiko::SpriteComponent> component = std::make_unique<kiko::SpriteComponent>();
			component->m_texture = GET_RESOURCE(kiko::Texture, "SpaceProjectile.png", kiko::g_renderer);
			weapon1->AddComponent(std::move(component));

			m_scene->Add(std::move(weapon1));
			}

			if (m_enemyDifficulty >= 2) {
				kiko::Transform transform2{ transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), 1};
				std::unique_ptr<Weapon> weapon2 = std::make_unique<Weapon>(400.0f, transform2);
				weapon2->tag = "Enemy";

				auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
				collisionComponent->m_radius = 30.0f;
				weapon2->AddComponent(std::move(collisionComponent));

				std::unique_ptr<kiko::SpriteComponent> component = std::make_unique<kiko::SpriteComponent>();
				component->m_texture = GET_RESOURCE(kiko::Texture, "SpaceProjectile.png", kiko::g_renderer);
				weapon2->AddComponent(std::move(component));

				m_scene->Add(std::move(weapon2));

				kiko::Transform transform3{ transform.position, transform.rotation - kiko::DegreesToRadians(10.0f), 1};
				std::unique_ptr<Weapon> weapon3 = std::make_unique<Weapon>(400.0f, transform3);
				weapon3->tag = "Enemy";

				collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
				collisionComponent->m_radius = 30.0f;
				weapon3->AddComponent(std::move(collisionComponent));

				component = std::make_unique<kiko::SpriteComponent>();
				component->m_texture = GET_RESOURCE(kiko::Texture, "SpaceProjectile.png", kiko::g_renderer);
				weapon3->AddComponent(std::move(component));

				m_scene->Add(std::move(weapon3));
				
			}

			kiko::g_audioSystem.PlayOneShot("Laser_Shoot");
		}
	}
}

void Enemy::OnCollision(Actor* other)
{

	if (dynamic_cast<Weapon*>(other) != nullptr && other->tag == "Player")
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

				kiko::Transform transform{ transform.position, 0, 1 };
				auto emitter = std::make_unique<kiko::Emitter>(transform, data);
				emitter->lifespan = 1.0f;
				m_scene->Add(std::move(emitter));

				// Points and Destruction
				m_game->AddPoints(100);
				destroyed = true;
			}
	}
}
