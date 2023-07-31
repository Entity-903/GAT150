#include "Particle.h"
#include "Renderer.h"

void kiko::Particle::Update(float dt)
{
	m_data.lifetimer += dt;
	if (m_data.lifetimer >= m_data.lifetime)
	{
		m_isActive = false;
		return;
	}

	m_data.prevPosition = m_data.position;
	m_data.position += m_data.velocity * dt;
	m_data.velocity *= std::pow(1.0f - m_data.damping, dt);
}

void kiko::Particle::Draw(Renderer& renderer)
{
	renderer.SetColor(Color::ToInt(m_data.color.r), Color::ToInt(m_data.color.g), Color::ToInt(m_data.color.b), Color::ToInt(m_data.color.a));
	renderer.DrawLine(m_data.position.x, m_data.position.y, m_data.prevPosition.x, m_data.prevPosition.y);
}
