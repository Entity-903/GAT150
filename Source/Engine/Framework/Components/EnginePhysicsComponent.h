#pragma once
#include "PhysicsComponent.h"

namespace kiko
{

	class EnginePhysicsComponent : public PhysicsComponent
	{
	public:
		virtual void Update(float dt) override;
		virtual void ApplyForce(const vec2& force) override;
		virtual void ApplyTorque(float torque) override;

		CLASS_DECLARATION(EnginePhysicsComponent)
	};
}