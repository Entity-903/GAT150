#pragma once
#include "Framework/Components/RenderComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"

namespace kiko
{
	class SpriteComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(SpriteComponent)

		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() { return m_texture->GetSize().Length() * 0.5f; }

	public:
		Rect source;
		bool flipH = false;
		vec2 origin{ 0.5f, 0.5f };

		std::string textureName;
		res_t<Texture> m_texture;
	};
}