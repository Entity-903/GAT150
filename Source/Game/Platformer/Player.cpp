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
		m_spriteAnimRenderComponent = GetComponent<SpriteAnimRenderComponent>();

		return true;
	}

	void Player::Update(float dt)
	{

		Actor::Update(dt);

		bool onGround = (groundCount > 0);
		bool isAttacking = (m_spriteAnimRenderComponent->GetSequence() == "attack");
		vec2 velocity = m_physicsComponent->m_velocity;

		// Movement
		float dir = 0;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;

		if (dir)
		{
		kiko::vec2 forward = kiko::vec2{ 1, 0 };
		velocity.x += m_speed * dir * ((onGround) ? 1 : 0.5f) * dt;
		velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
		m_physicsComponent->SetVelocity(velocity);

		//m_physicsComponent->ApplyForce(forward * m_speed * dir * ((onGround) ? 1 : 0.5f)); // Replace 0.5f with 10.0f for TF2 Scout
		}


		// Jump
		if (onGround && 
			kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W) &&
			!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_W))
		{
			kiko::vec2 up = kiko::vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(vec2{ velocity.x, -m_jump } );
		}

		m_physicsComponent->SetGravityScale((velocity.y > 0) ? 3 : 2);

		// Animation
		if (onGround && kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			m_physicsComponent->SetVelocity(0);
			m_spriteAnimRenderComponent->SetSequence("attack");
		} 
		// Check if Moving
		else if (std::fabs(velocity.x) > 0.2f)
		{
			// Run Animation
			if (dir != 0) m_spriteAnimRenderComponent->flipH = (dir < 0);
			m_spriteAnimRenderComponent->SetSequence("run");
		}
		else
		{
			// Idle Animation
			if (!isAttacking) m_spriteAnimRenderComponent->SetSequence("idle");
		}
		
		if (m_health <= 0)
		{
			m_spriteAnimRenderComponent->SetSequence("death");
		}
	}

	void Player::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Coin")
		{
			kiko::EventManager::Instance().DispatchEvent("OnAddPoints", 100);
			other->destroyed = true;
		}

		if (other->tag == "Enemy" && m_spriteAnimRenderComponent->GetSequence() != "attack")
		{
			m_health -= 10;
			std::cout << m_health << "\n";
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
		READ_NAME_DATA(value, "maxSpeed", maxSpeed);
		READ_NAME_DATA(value, "jump", m_jump);
		READ_NAME_DATA(value, "health", m_health);
	}
}
