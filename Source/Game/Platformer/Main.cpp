#include "PlatformGame.h"
#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Framework.h"
#include "Physics/PhysicsSystem.h"

#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include <array>
#include <map>
#include <functional>

// Need to know how to check what animation sequence a sprite is on
// Maybe it could be checked by looping through all animations a sprite could be in from the json?
// But how would we get the sequence?
// A method, GetSequence(), has been made in SpriteAnimRenderComponent with no definition
// Try accessing m_sequence in SpriteAnimRenderComponent to get the current sequence

// Animation for the attack plays, but it loops until the character moves again, effectively replacing the idle animation...

// How to update the scoreText using the json?

using namespace std;


int main(int argc, char* argv[])
{

	INFO_LOG("Initialize Engine...");

	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("Assets/Platformer");

	// Engine Initialization
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("GAT150", 800, 600);

	kiko::g_inputSystem.Initialize();

	kiko::g_audioSystem.Initialize();

	kiko::PhysicsSystem::Instance().Initialize();

	// Create Game
	unique_ptr<PlatformGame> game = make_unique<PlatformGame>();
	game->Initialize();


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

		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());
		kiko::PhysicsSystem::Instance().Update(kiko::g_time.GetDeltaTime());

		// Update game
		game->Update(kiko::g_time.GetDeltaTime());
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());

		// Update Audio
		kiko::g_audioSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
		}

		// Draw game
		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();

		game->Draw(kiko::g_renderer);

		kiko::g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);

		kiko::g_particleSystem.Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();

	}

	return 0;
}