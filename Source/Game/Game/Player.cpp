#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Framework/Component/SpriteComponent.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/PhysicsComponent.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
//#include "Framework/Factory.h"

#include "Framework/Components/CircleCollisionComponent.h"

bool Player::Initialize()
{
	Actor::Initialize();

	// Cashe off
	m_physicsComponent = GetComponent<kiko::PhysicsComponent>();
	auto collisionComponent = GetComponent<kiko::CollisionComponent>();
	if (collisionComponent)
	{
		auto renderComponent = GetComponent<kiko::RenderComponent>();
		if (renderComponent)
		{
			float scale = transform.scale;
			collisionComponent->m_radius = GetComponent<kiko::RenderComponent>()->GetRadius() * scale;
		}
	}

	return true;
}

void Player::Update(float dt)
{

	Actor::Update(dt);

	// Movement
	float rotate = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

	float thrust = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) thrust = -1;
	
	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);

	m_physicsComponent->ApplyForce(forward * m_speed * thrust);

	//m_transform.position += forward * m_speed * 0.25 * thrust * kiko::g_time.GetDeltaTime();
	transform.position.x = kiko::Wrap((float)transform.position.x, (float)kiko::g_renderer.GetWidth());
	transform.position.y = kiko::Wrap((float)transform.position.y, (float)kiko::g_renderer.GetHeight());

	// Fire Weapon
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
		!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{

		// Create Weapon
		//if (m_score)
		
		
		// All player's weapons
		
		// Weapon 1
		auto weapon1 = INSTANTIATE(Weapon, "PlayerBasicWeapon");
		weapon1->transform = { transform.position, transform.rotation, 1 };
		weapon1->Initialize();

		m_scene->Add(std::move(weapon1));

		// Weapon 2

		auto weapon2 = INSTANTIATE(Weapon, "PlayerBasicWeapon");
		weapon2->transform = { transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), 1 };
		weapon2->Initialize();

		m_scene->Add(std::move(weapon2));

		// Weapon 3

		auto weapon3 = INSTANTIATE(Weapon, "PlayerBasicWeapon");
		weapon3->transform = { transform.position, transform.rotation - kiko::DegreesToRadians(10.0f), 1 };
		weapon3->Initialize();

		m_scene->Add(std::move(weapon3));
	}

	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kiko::g_time.SetTimeScale(0.5f);
	else kiko::g_time.SetTimeScale(1.0f);
}

void Player::OnCollision(Actor* other)
{
	if (dynamic_cast<kiko::Weapon*>(other) != nullptr && other->tag == "Enemy")
	{
		m_health -= 10;
		std::cout << m_health << "\n";
		if (m_health <= 0)
		{
			//m_game->SetLives(m_game->GetLives() - 1);
			//dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
			kiko::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
			destroyed = true;
		}
	}
}
