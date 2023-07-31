#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Scene.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"

bool SpaceGame::Initialize()
{
	// Create Font / Text Objects
	m_font = std::make_shared<kiko::Font>("EmptyMegazineDemoRegular.ttf", 24);
	m_scoreText = std::make_unique<kiko::Text>(m_font);
	m_scoreText->Create(kiko::g_renderer, "SCORE 0000", kiko::Color{ 1, 0, 1, 1 });

	m_titleText = std::make_unique<kiko::Text>(m_font);
	m_titleText->Create(kiko::g_renderer, "Asteroids", kiko::Color{ 1, 1, 1, 1 });

	m_gameoverText = std::make_unique<kiko::Text>(m_font);
	m_gameoverText->Create(kiko::g_renderer, "Game Over", kiko::Color{ 1, 1, 1, 1 });

	// Load Audio
	kiko::g_audioSystem.AddAudio("Laser_Shoot", "Laser_Shoot.wav");

	// Load Scene
	m_scene = std::make_unique<kiko::Scene>();





	//for (int i = 0; i < 5; i++)
	//{
	//	unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(75.0f, 150.0f), kiko::Pi, kiko::Transform{ {kiko::randomf(kiko::g_renderer.GetWidth()), kiko::randomf(kiko::g_renderer.GetHeight())}, kiko::randomf(kiko::TwoPi), 3}, kiko::g_manager.Get("Something.txt"));
	//	enemy->m_tag = "Enemy";
	//	scene.Add(std::move(enemy));
	//}

	return true;
}

void SpaceGame::Shutdown()
{
	//
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::Title:
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			this->m_state = eState::StartGame;
		}
		break;
	case SpaceGame::StartGame:
		this->m_score = 0;
		this->m_lives = 3;
		this->m_state = eState::StartLevel;
		break;
	case SpaceGame::StartLevel:
	{
		m_scene->RemoveAll();

		std::unique_ptr<Player> player = std::make_unique<Player>(20.0f, kiko::Pi, kiko::Transform{ { 400, 300 }, 0, 3 }, kiko::g_manager.Get("Ship.txt"));
		player->m_tag = "Player";
		player->m_game = this;
		player->SetDamping(0.9f);
		m_scene->Add(std::move(player));
	}
	m_state = eState::Game;
		break;
	case SpaceGame::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0.0f;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(75.0f, 150.0f), kiko::Pi, kiko::Transform{ {kiko::randomf((float)kiko::g_renderer.GetWidth()), kiko::randomf((float)kiko::g_renderer.GetHeight())}, kiko::randomf(kiko::TwoPi), 3}, kiko::g_manager.Get("Something.txt"), *this);
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));
		}
		break;
	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;

		break;
	case SpaceGame::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) 
		{
		m_state = eState::StartLevel;
		}
		break;
	case SpaceGame::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	
	m_scoreText->Create(kiko::g_renderer, "SCORE: " + std::to_string(m_score), {1, 1, 1, 1});
	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 400, 300);
	}
	if (m_state == eState::GameOver)
	{
		m_gameoverText->Draw(renderer, 400, 300);
	}
	m_scoreText->Draw(renderer, 40, 40);
	m_scene->Draw(renderer);
}
