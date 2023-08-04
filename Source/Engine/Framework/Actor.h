#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Components/Component.h"

#include <memory>

namespace kiko
{
class Actor
{
public:
	Actor() = default;
	Actor(const kiko::Transform& transform) :
		m_transform{ transform }
	{}
	Actor(const kiko::Transform& transform, std::shared_ptr<Model> model) :
		m_transform{ transform },
		m_model{ model }
	{}

	virtual void Update(float dt);
	virtual void Draw(kiko::Renderer& renderer);

	void AddComponent(std::unique_ptr<Component> component);

	float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : -10000; }
	virtual void OnCollision(Actor* other) {}

	void AddForce(vec2 force) { m_velocity += force; }
	void SetDamping(float damping) { m_damping = damping; }

	class Scene* m_scene = nullptr;
	friend class Scene;

	class Game* m_game = nullptr;

	kiko::Transform m_transform;
	std::string m_tag;
	float m_lifespan = -1.0f;

protected:
	std::vector<std::unique_ptr<Component>> m_components;

	bool m_destroyed = false;

	std::shared_ptr<Model> m_model;

	vec2 m_velocity;
	float m_damping = 0;
};
}