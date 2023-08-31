#include "PlatformGame.h"

#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"


bool PlatformGame::Initialize()
{
	// Create Font / Text Objects
	//m_font = GET_RESOURCE(kiko::Font, "ArcadeClassic.ttf", 24); //std::make_shared<kiko::Font>("ArcadeClassic.ttf", 24);
	//m_scoreText = std::make_unique<kiko::Text>(GET_RESOURCE(kiko::Font, "ArcadeClassic.ttf", 24));
	//m_scoreText->Create(kiko::g_renderer, "SCORE 0000", kiko::Color{ 1, 0, 1, 1 });

	//m_gameoverText = std::make_unique<kiko::Text>(GET_RESOURCE(kiko::Font, "ArcadeClassic.ttf", 24));
	//m_gameoverText->Create(kiko::g_renderer, "Game Over", kiko::Color{ 1, 1, 1, 1 });

	// Load Audio (None currently)
	

	// Create Scene
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("Scenes/Scene.json");
	m_scene->Load("Scenes/tilemap.json");
	m_scene->Initialize();


	// Add Events
	EVENT_SUBSCRIBE("OnAddPoints", PlatformGame::OnAddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", PlatformGame::OnPlayerDead);

	return true;
}

void PlatformGame::Shutdown()
{
	//
}

void PlatformGame::Update(float dt)
{
	switch (m_state)
	{
	case PlatformGame::Title:
	{
		//auto actor = INSTANTIATE(Actor, "Crate");
		//actor->transform.position = { kiko::random(kiko::g_renderer.GetWidth()), 100 };
		//actor->Initialize();
		//m_scene->Add(std::move(actor));


	}
		break;
	case PlatformGame::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case PlatformGame::StartLevel:
		break;
	case PlatformGame::Game:
		break;
	case eState::PlayerDeadStart:
		break;
	case PlatformGame::PlayerDead:
		break;
	case PlatformGame::GameOver:
		break;
	default:
		break;
	}

	m_scene->Update(dt);
}

void PlatformGame::Draw(kiko::Renderer& renderer)
{
	m_scene->Draw(renderer);
}

void PlatformGame::OnAddPoints(const kiko::Event& event)
{
	m_score += std::get<int>(event.data);
}

void PlatformGame::OnPlayerDead(const kiko::Event& event)
{
	m_state = eState::PlayerDeadStart;
}
