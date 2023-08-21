#include "TextRenderComponent.h"
#include "Framework/Actor.h"

namespace kiko
{
	CLASS_DEFINITION(TextRenderComponent)

	TextRenderComponent::TextRenderComponent(const TextRenderComponent& other)
	{
		text = other.text;
		fontName = other.fontName;
		fontSize = other.fontSize;

		m_changed = true;
		m_text = std::make_unique<Text>(*other.m_text.get());
	}

	bool TextRenderComponent::Initialize()
	{
		if (!fontName.empty()) m_text = std::make_unique<kiko::Text>(GET_RESOURCE(Font, fontName, fontSize));
		
		return true;
	}

	void TextRenderComponent::Update(float dt)
	{
	}

	void TextRenderComponent::Draw(Renderer& renderer)
	{
		// Update te text if changed
		if (m_changed)
		{
			m_changed = false;
			// Create text using text string and color
			m_text->Create(renderer, text, { 1, 1, 1, 1 });
		}
		// Draw Text
		m_text->Draw(renderer, m_owner->transform);
	}

	void TextRenderComponent::SetText(const std::string& string)
	{
		// Check if text has changed. If changed, set new string and update
		if (string != text)
		{
			text = string;
			m_changed = true;
		}
	}

	void TextRenderComponent::Read(const json_t& value)
	{
		READ_DATA(value, text);
		READ_DATA(value, fontName);
		READ_DATA(value, fontSize);
	}
}