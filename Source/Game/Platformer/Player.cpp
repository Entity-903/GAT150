#include "Player.h"
#include "PlatformGame.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

#include "Framework/Components/CircleCollisionComponent.h"

namespace kiko
{
	CLASS_DEFINITION(Player);

	bool Player::Initialize()
	{
		Actor::Initialize();

		// Cashe off
		m_physicsComponent = GetComponent<kiko::PhysicsComponent>();

		return true;
	}

	void Player::Update(float dt)
	{

		Actor::Update(dt);

		// Movement
		float dir = 0;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;

		kiko::vec2 forward = kiko::vec2{ 1, 0 }.Rotate(transform.rotation);

		m_physicsComponent->ApplyForce(forward * m_speed * dir);

		// Jump
		bool onGround = (groundCount > 0);
		if (onGround && 
			kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			kiko::vec2 up = kiko::vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(up * m_jump);
		}
	}

	void Player::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			m_health -= 10;
			if (m_health <= 0)
			{
			destroyed = true;
			EVENT_DISPATCH("OnPlayerDead", 0);
			}
		}

		if (other->tag == "Ground")
		{
			groundCount++;
		}
	}

	void Player::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground")
		{
			groundCount--;
		}
	}

	void Player::Read(const kiko::json_t& value)
	{
		Actor::Read(value);

		READ_NAME_DATA(value, "speed", m_speed);
		READ_NAME_DATA(value, "jump", m_jump);
		READ_NAME_DATA(value, "health", m_health);
	}
}
