#pragma once

#include "Particle.h"
#include <vector>

namespace kiko
{

	class ParticleSystem
	{
	public:
		ParticleSystem() = default;
		ParticleSystem(int maxCount)
		{
			m_particles.resize(maxCount);
		}

		void Update(float dt);
		void Draw(class Renderer& renderer);

		Particle* GetFreeParticle();

	private:
		std::vector<Particle> m_particles;
	};

	extern ParticleSystem g_particleSystem;
}