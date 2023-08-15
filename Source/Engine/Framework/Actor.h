#pragma once
#include "Object.h"
//#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Components/Component.h"

#include <memory>

namespace kiko
{
class Actor : public Object
{
public:
	Actor() = default;
	Actor(const kiko::Transform& transform) :
		m_transform{ transform }
	{}

	virtual bool Initialize() override;
	virtual void OnDestroy() override;

	virtual void Update(float dt);
	virtual void Draw(kiko::Renderer& renderer);

	void AddComponent(std::unique_ptr<Component> component);

	template<typename T>
	T* GetComponent();

	float GetRadius() { return 30.0f; }
	virtual void OnCollision(Actor* other) {}

	class Scene* m_scene = nullptr;
	friend class Scene;

	class Game* m_game = nullptr;

	kiko::Transform m_transform;
	std::string m_tag;
	float m_lifespan = -1.0f;

protected:
	std::vector<std::unique_ptr<Component>> m_components;

	bool m_destroyed = false;
};
template<typename T>
inline T* Actor::GetComponent()
{
	for (auto& component : m_components)
	{
		T* result = dynamic_cast<T*>(component.get());
		if (result) return result;
	}

	return nullptr;
}
}