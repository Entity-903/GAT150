#pragma once
#include "Framework/Components/RenderComponent.h"
#include "Renderer/Texture.h"

namespace kiko
{
	class SpriteComponent : public RenderComponent
	{
	public:
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() { return m_texture->GetSize().Length() * 0.5f; }

	public:
		res_t<Texture> m_texture;
	};
}