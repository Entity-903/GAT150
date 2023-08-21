#pragma once
#include "Object.h"
#include "Renderer/Renderer.h"
#include "Components/Component.h"

#include <memory>

namespace kiko
{
class Actor : public Object
{

public:
	Actor() = default;
	Actor(const kiko::Transform& transform) :
		transform{ transform }
	{}

	Actor(const Actor& other);

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

public:
	kiko::Transform transform;
	std::string tag;
	float lifespan = -1.0f;
	bool destroyed = false;
	bool persistant = false;
	bool prototype = false;

	CLASS_DECLARATION(Actor)

protected:
	std::vector<std::unique_ptr<Component>> components;
};
template<typename T>
inline T* Actor::GetComponent()
{
	for (auto& component : components)
	{
		T* result = dynamic_cast<T*>(component.get());
		if (result) return result;
	}

	return nullptr;
}
}