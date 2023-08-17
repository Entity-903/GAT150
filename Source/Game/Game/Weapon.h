#pragma once
#include "Framework/Actor.h"


//namespace kiko
//{
	class Weapon : public kiko::Actor
	{
	public:
		
		Weapon(float speed, const kiko::Transform& transform) :
			Actor{ transform },
			speed{ speed }
		{
			lifespan = 2.0f;
		}
		
		bool Initialize() override;
		void Update(float dt) override;
		void OnCollision(kiko::Actor* actor);
		void Read(const kiko::json_t& value);

	private:
		float speed = 0;
	};

//}