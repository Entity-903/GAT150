#include "AudioSystem.h"

namespace kiko
{
	AudioSystem g_audioSystem;

bool kiko::AudioSystem::Initialize()
{
	FMOD::System_Create(&m_fmodSystem);

	void* extradriverdata = nullptr;
	m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);

	return true;
}

void kiko::AudioSystem::Shutdown()
{
	for (auto sound : m_sounds) sound.second->release();
	m_sounds.clear();

	m_fmodSystem->close();
	m_fmodSystem->release();
}

void kiko::AudioSystem::Update()
{
	m_fmodSystem->update();
}

void kiko::AudioSystem::AddAudio(const std::string& name, const std::string& filename)
{
	if (m_sounds.find(name) == m_sounds.end())
	{
		FMOD::Sound* sound = nullptr;
		m_fmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
		m_sounds[name] = sound;
	}
}

void kiko::AudioSystem::PlayOneShot(const std::string& name, bool loop)
{
	auto iter = m_sounds.find(name);
	if (iter != m_sounds.end())
	{
		FMOD::Sound* sound = iter->second;
		sound->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
		
		

		FMOD::Channel* channel;
		m_fmodSystem->playSound(sound, 0, false, &channel);
	}
}
}
