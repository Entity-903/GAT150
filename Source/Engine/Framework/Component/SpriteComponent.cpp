#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"


namespace kiko
{
	CLASS_DEFINITION(SpriteComponent)

		bool SpriteComponent::Initialize()
	{
		m_texture = GET_RESOURCE(Texture, textureName, g_renderer);

		return true;
	}

	void kiko::SpriteComponent::Update(float dt)
	{
		//
	}

	void kiko::SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->transform);
	}

	void SpriteComponent::Read(const json_t& value)
		{
		READ_DATA(value, textureName);
		}
}
