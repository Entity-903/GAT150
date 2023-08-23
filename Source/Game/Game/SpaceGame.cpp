#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"

// Vector3.h Needs More Work!!!


bool SpaceGame::Initialize()
{
	// Create Font / Text Objects
	//m_font = GET_RESOURCE(kiko::Font, "ArcadeClassic.ttf", 24); //std::make_shared<kiko::Font>("ArcadeClassic.ttf", 24);
	m_scoreText = std::make_unique<kiko::Text>(GET_RESOURCE(kiko::Font, "ArcadeClassic.ttf", 24));
	m_scoreText->Create(kiko::g_renderer, "SCORE 0000", kiko::Color{ 1, 0, 1, 1 });

	m_gameoverText = std::make_unique<kiko::Text>(GET_RESOURCE(kiko::Font, "ArcadeClassic.ttf", 24));
	m_gameoverText->Create(kiko::g_renderer, "Game Over", kiko::Color{ 1, 1, 1, 1 });

	// Load Audio
	kiko::g_audioSystem.AddAudio("Laser_Shoot", "Laser_Shoot.wav");

	// Create Scene
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("Scene.json");
	m_scene->Initialize();

	// Add Events
	EVENT_SUBSCRIBE("OnAddPoints", SpaceGame::OnAddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", SpaceGame::OnPlayerDead);

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
			//auto actor = m_scene->GetActorByName("Background")->active;
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

		// Create Player
		std::unique_ptr<Player> player = std::make_unique<Player>(20.0f, kiko::Pi, kiko::Transform{ { 400, 300 }, 0, 0.25f });
		player->tag = "Player";
		player->m_game = this;

		// Create Components
		auto renderComponent = CREATE_CLASS(SpriteComponent)
		renderComponent->m_texture = GET_RESOURCE(kiko::Texture, "JoeBiden.jpg", kiko::g_renderer); // "Ship.txt" 
		player->AddComponent(std::move(renderComponent));

		auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent)
		physicsComponent->m_damping = 0.9f;
		player->AddComponent(std::move(physicsComponent));

		auto collisionComponent = CREATE_CLASS(CircleCollisionComponent)
		collisionComponent->m_radius = 30.0f;
		player->AddComponent(std::move(collisionComponent));

		player->Initialize();
		m_scene->Add(std::move(player));
	}
	m_state = eState::Game;
		break;
	case SpaceGame::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0.0f;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(75.0f, 150.0f), kiko::Pi, kiko::Transform{ {kiko::randomf((float)kiko::g_renderer.GetWidth()), kiko::randomf((float)kiko::g_renderer.GetHeight())}, kiko::randomf(kiko::TwoPi), 0.5f}, *this);
			enemy->tag = "Enemy";
			enemy->m_game = this;

			// Create Components
			auto renderComponent = CREATE_CLASS(SpriteComponent)
			renderComponent->m_texture = GET_RESOURCE(kiko::Texture, "DonaldTrump.jpg", kiko::g_renderer);
			enemy->AddComponent(std::move(renderComponent));

			auto collisionComponent = CREATE_CLASS(CircleCollisionComponent)
			collisionComponent->m_radius = 30.0f;
			enemy->AddComponent(std::move(collisionComponent));

			enemy->Initialize();
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

	
	m_scoreText->Create(kiko::g_renderer, "SCORE " + std::to_string(m_score), {1, 1, 1, 1});
	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
	m_scene->Draw(renderer);
	if (m_state == eState::GameOver)
	{
		m_gameoverText->Draw(renderer, 400, 300);
	}
	m_scoreText->Draw(renderer, 40, 40);
}

void SpaceGame::OnAddPoints(const kiko::Event& event)
{
	m_score += std::get<int>(event.data);
}

void SpaceGame::OnPlayerDead(const kiko::Event& event)
{
	m_state = eState::PlayerDeadStart;
}
