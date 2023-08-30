#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"


namespace kiko
{
	CLASS_DEFINITION(SpriteComponent)

		bool SpriteComponent::Initialize()
	{
		if (!textureName.empty()) m_texture = GET_RESOURCE(Texture, textureName, g_renderer);
		if (source.w == 0 && source.h == 0)
		{
			if (m_texture)
			{
				source.x = 0;
				source.y = 0;
				source.w = (int)m_texture->GetSize().x;
				source.h = (int)m_texture->GetSize().y;
			}
		}

		return true;
	}

	void kiko::SpriteComponent::Update(float dt)
	{
		//
	}

	void kiko::SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), source, m_owner->transform, origin, flipH);
	}

	void SpriteComponent::Read(const json_t& value)
		{
		READ_DATA(value, textureName);
		READ_DATA(value, source);
		READ_DATA(value, flipH);
		READ_DATA(value, origin);
		}
}
