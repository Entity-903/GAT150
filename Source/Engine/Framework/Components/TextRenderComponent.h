#pragma once
#include "RenderComponent.h"
#include "Renderer/Text.h"

namespace kiko
{
	class TextRenderComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(TextRenderComponent);

		TextRenderComponent() = default;
		TextRenderComponent(const TextRenderComponent& other);

		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		void SetText(const std::string& string);

	public:
		std::string text;
		std::string fontName;
		int fontSize = 0;
	private:
		bool m_changed = true;
		std::unique_ptr<Text> m_text;
	};
}