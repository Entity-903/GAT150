#include "PhysicsSystem.h"

namespace kiko
{
	bool PhysicsSystem::Initialize()
	{
		b2Vec2 gravity{ 0, 10 };
		m_world = std::make_unique<b2World>(gravity);

		m_contactListener = std::make_unique<ContactListener>();
		m_world->SetContactListener(m_contactListener.get());

		return true;
	}
	void PhysicsSystem::Update(float dt)
	{
		m_world->Step(1.0f / 60.0f, 8, 3);
	}

	// Professor Provided Code
	b2Body* PhysicsSystem::CreateBody(const vec2& position, float angle, const RigidBodyData& data)
	{
		Vector2 worldPosition = ScreenToWorld(position);

		b2BodyDef bodyDef;
		bodyDef.type = (data.isDynamic) ? b2_dynamicBody : b2_staticBody;
		bodyDef.position = VEC2_TO_B2VEC2(worldPosition);
		bodyDef.angle = angle;
		bodyDef.fixedRotation = data.constrainAngle;
		b2Body* body = m_world->CreateBody(&bodyDef);

		return body;
	}

	void PhysicsSystem::DestroyBody(b2Body* body)
	{
		m_world->DestroyBody(body);
	}

	void PhysicsSystem::SetCollisionBox(b2Body* body, const CollisionData& data, class Actor* actor)
	{
		Vector2 worldSize = ScreenToWorld(data.size * 0.5f);
		Vector2 worldOffset = ScreenToWorld(data.size * data.offset);

		b2Vec2 vs[4] =
		{
			{ -worldSize.x - worldOffset.x, -worldSize.y - worldOffset.y },
			{  worldSize.x - worldOffset.x, -worldSize.y - worldOffset.y },
			{  worldSize.x - worldOffset.x,  worldSize.y - worldOffset.y },
			{ -worldSize.x - worldOffset.x,  worldSize.y - worldOffset.y }
		};

		b2PolygonShape shape;
		shape.Set( vs, 4);

		b2FixtureDef fixtureDef;
		fixtureDef.density = data.density;
		fixtureDef.friction = data.friction;
		fixtureDef.restitution = data.restitution;
		fixtureDef.isSensor = data.isTrigger;
		fixtureDef.shape = &shape;
		fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(actor);

		body->CreateFixture(&fixtureDef);
	}

	void PhysicsSystem::SetCollisionBoxStatic(b2Body* body, const CollisionData& data, Actor* actor)
	{
		Vector2 worldSize = PhysicsSystem::ScreenToWorld(data.size * 0.5f);

		b2Vec2 vs[4] =
		{
			{ -worldSize.x, -worldSize.y },
			{  worldSize.x, -worldSize.y },
			{  worldSize.x,  worldSize.y },
			{ -worldSize.x,  worldSize.y },
		};

		b2ChainShape shape;
		shape.CreateLoop(vs, 4);

		b2FixtureDef fixtureDef;
		fixtureDef.density = data.density;
		fixtureDef.friction = data.friction;
		fixtureDef.restitution = data.restitution;
		fixtureDef.isSensor = data.isTrigger;
		fixtureDef.shape = &shape;
		fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(actor);

		body->CreateFixture(&fixtureDef);
	}
}