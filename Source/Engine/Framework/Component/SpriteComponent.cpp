#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"


namespace kiko
{
	CLASS_DEFINITION(SpriteComponent)

	void kiko::SpriteComponent::Update(float dt)
	{
		//
	}

	void kiko::SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->m_transform);
	}
}
