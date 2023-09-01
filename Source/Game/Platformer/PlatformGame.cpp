#include "PlatformGame.h"

#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Enemy.h"
#include "Player.h"


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
	case eState::Title:
	{
		//auto actor = INSTANTIATE(Actor, "Crate");
		//actor->transform.position = { kiko::random(kiko::g_renderer.GetWidth()), 100 };
		//actor->Initialize();
		//m_scene->Add(std::move(actor));

		m_state = eState::StartGame;
	}
		break;
	case eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case eState::StartLevel:
	{
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0.0f;

			auto enemy = INSTANTIATE(Enemy, "Enemy");
			enemy->transform.position = { kiko::randomf((float)kiko::g_renderer.GetWidth()), kiko::randomf((float)kiko::g_renderer.GetHeight()) };
			enemy->m_game = this;

			enemy->Initialize();
			m_scene->Add(std::move(enemy));
		}

		auto healthText = m_scene->GetActorByName("HealthText");
		if (healthText != nullptr)
		{
			auto player = m_scene->GetActorByName("Player");
			if (player != nullptr)
			{
			healthText->GetComponent<kiko::TextRenderComponent>()->SetText("Health " + std::to_string(dynamic_cast<kiko::Player*>(player)->m_health));
			}
		}

		auto scoreText = m_scene->GetActorByName("ScoreText");
		if (scoreText != nullptr)
		{
			scoreText->GetComponent<kiko::TextRenderComponent>()->SetText("Score " + std::to_string(m_score));
		}

	}
		break;
	case eState::Game:
		break;
	case eState::PlayerDeadStart:
		break;
	case eState::PlayerDead:
		break;
	case eState::GameOver:
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
