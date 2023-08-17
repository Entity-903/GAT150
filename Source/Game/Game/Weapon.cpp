#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"


//namespace kiko
//{
	bool Weapon::Initialize()
	{
		//auto collisionComponent = GetComponent<kiko::CollisionComponent>(kiko::CollisionComponent);
		// if (collisionComponent)
		//{
		//	
		//}

		return true;
	}

	void Weapon::Update(float dt)
	{
		Actor::Update(dt);

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		transform.position += forward * speed * kiko::g_time.GetDeltaTime();
		transform.position.x = kiko::Wrap((float)transform.position.x, (float)kiko::g_renderer.GetWidth());
		transform.position.y = kiko::Wrap((float)transform.position.y, (float)kiko::g_renderer.GetHeight());
	}

	void Weapon::OnCollision(kiko::Actor* other)
	{
		if (other->tag != tag)
		{
			destroyed = true;
		}
	}

	void Weapon::Read(const kiko::json_t& value)
	{
		READ_DATA(value, speed);
	}
//}
