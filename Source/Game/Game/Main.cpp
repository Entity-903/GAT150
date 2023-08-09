#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include "Input/InputSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "Audio/AudioSystem.h"
#include "Framework/Framework.h"

#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include <array>
#include <map>

using namespace std;

class Star
{
public:
	Star(const kiko::Vector2& pos, const kiko::Vector2& vel) :
		m_pos{ pos },
		m_vel{ vel } {}

	void Update(int width, int height)
	{
		m_pos += m_vel * kiko::g_time.GetDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::vec2 m_pos;
	kiko::vec2 m_vel;
};

int main(int argc, char* argv[])
{

	INFO_LOG("Initialize Engine...");

	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	// Engine Initialization
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();

	kiko::g_audioSystem.Initialize();

	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();
	//kiko::g_audioSystem.AddAudio("Laser_Shoot", "Laser_Shoot.wav");

	//// Create Font / Text Objects
	//std::shared_ptr<kiko::Font> font = std::make_shared<kiko::Font>("EmptyMegazineDemoRegular.ttf", 24);
	//std::unique_ptr<kiko::Text> text = std::make_unique<kiko::Text>(font);
	//text->Create(kiko::g_renderer, "NEUMONT", kiko::Color{ 1, 1, 1, 1 });

	//kiko::Model model;
	//model.Load("Ship.txt");
	kiko::vec2 position{ 400, 300 };

	float speed = 100;
	constexpr float turnrate = kiko::DegreesToRadians(180);

	/*kiko::Scene scene;
	unique_ptr<Player> player = std::make_unique<Player>(200.0f, kiko::Pi, kiko::Transform{ { 400, 300 }, 0, 6 }, kiko::g_manager.Get("Ship.txt"));
	player->m_tag = "Player";
	scene.Add(std::move(player));



	for (int i = 0; i < 5; i++)
	{
		unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(75.0f, 150.0f), kiko::Pi, kiko::Transform{ {kiko::randomf(kiko::g_renderer.GetWidth()), kiko::randomf(kiko::g_renderer.GetHeight())}, kiko::randomf(kiko::TwoPi), 3}, kiko::g_manager.Get("Something.txt"));
		enemy->m_tag = "Enemy";
		scene.Add(std::move(enemy));
	}*/

	vector<Star> stars;
	for (int i = 0; i < 5000; i++)
	{
		kiko::Vector2 pos(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight()));
		kiko::Vector2 vel(kiko::randomf(100, 200), 0.0f);

		stars.push_back(Star(pos, vel));
	}
	

	

	kiko::Transform transform{ { 400, 300 }, 0, 3};

	// Create Texture
	//kiko::res_t<kiko::Texture> texture = kiko::g_resources.Get<kiko::Texture>("JoeBiden.jpg", kiko::g_renderer);


	// Main Game Loop
	bool quit = false;
	while (!quit)
	{

		// Update engine
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		// Update game
		game->Update(kiko::g_time.GetDeltaTime());
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());

		// Update Audio
		kiko::g_audioSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			kiko::g_audioSystem.PlayOneShot("Laser_Shoot");
		}

		// Draw game
		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();

		//text->Draw(kiko::g_renderer, 400, 300);

		for (auto& star : stars)
		{
			star.Update(kiko::g_renderer.GetWidth(), kiko::g_renderer.GetHeight());

			if (star.m_pos.x >= kiko::g_renderer.GetWidth()) star.m_pos.x = 0;
			if (star.m_pos.y >= kiko::g_renderer.GetHeight()) star.m_pos.y = 0;

			kiko::g_renderer.SetColor(255, 255, 255, 255);
			kiko::g_renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}
	
		kiko::g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);

		game->Draw(kiko::g_renderer);
		kiko::g_particleSystem.Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();

	}

	return 0;
}