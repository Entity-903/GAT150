#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Framework/Component/SpriteComponent.h"
#include "Framework/Resource/ResourceManager.h"
#include "Framework/Components/PhysicsComponent.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

void Player::Update(float dt)
{

	Actor::Update(dt);

	// Movement
	float rotate = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

	float thrust = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) thrust = -1;
	
	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);

	auto physicsComponent = GetComponent<kiko::PhysicsComponent>();
	physicsComponent->ApplyForce(forward * m_speed * thrust);

	//m_transform.position += forward * m_speed * 0.25 * thrust * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap((float)m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap((float)m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	// Fire Weapon
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
		!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		// Create Weapon
		//if (m_score)
		// 
		// Weapon 1
		kiko::Transform transform1{ m_transform.position, m_transform.rotation, 1};
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform1); 
		weapon->m_tag = "Player";

		std::unique_ptr<kiko::SpriteComponent> component = std::make_unique<kiko::SpriteComponent>();
		component->m_texture = kiko::g_resources.Get<kiko::Texture>("SpaceProjectile.png", kiko::g_renderer);
		weapon->AddComponent(std::move(component));

		m_scene->Add(std::move(weapon));

		// Weapon 2

		kiko::Transform transform2{ m_transform.position, m_transform.rotation - kiko::DegreesToRadians(10.0f), 1};
		weapon = std::make_unique<Weapon>(400.0f, transform2);
		weapon->m_tag = "Player";

		component = std::make_unique<kiko::SpriteComponent>();
		component->m_texture = kiko::g_resources.Get<kiko::Texture>("SpaceProjectile.png", kiko::g_renderer);
		weapon->AddComponent(std::move(component));

		m_scene->Add(std::move(weapon));

		// Weapon 3

		kiko::Transform transform3{ m_transform.position, m_transform.rotation + kiko::DegreesToRadians(10.0f), 1};
		weapon = std::make_unique<Weapon>(400.0f, transform3);
		weapon->m_tag = "Player";

		component = std::make_unique<kiko::SpriteComponent>();
		component->m_texture = kiko::g_resources.Get<kiko::Texture>("SpaceProjectile.png", kiko::g_renderer);
		weapon->AddComponent(std::move(component));

		m_scene->Add(std::move(weapon));

	}

	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kiko::g_time.SetTimeScale(0.5f);
	else kiko::g_time.SetTimeScale(1.0f);
}

void Player::OnCollision(Actor* other)
{
	if (dynamic_cast<Weapon*>(other) != nullptr && other->m_tag == "Enemy")
	{
		m_health -= 10;
		std::cout << m_health << "\n";
		if (m_health <= 0)
		{
			m_game->SetLives(m_game->GetLives() - 1);
			dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
			m_destroyed = true;
		}
	}
}
