#include "InputSystem.h"

namespace kiko
{
	InputSystem g_inputSystem;

	bool InputSystem::Initialize()
	{
		int numKeys;
		// Get pointer to SDL keyboard states and number of keys
		const uint8_t* keyboardState = SDL_GetKeyboardState(&numKeys);

		// Resize of keyboard state vector using numKeys for size
		m_keyboardState.resize(numKeys);

		// Copy the SDL key states to keyboard state
		std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());

		// Set previous keyboard state to current keyboard state
		m_prevKeyboardState = m_keyboardState;

		return true;
	}
	void InputSystem::Shutdown()
	{
			//
	}
	void InputSystem::Update()
	{
		// Update SDL events
		SDL_Event event;
		SDL_PollEvent(&event);

		// Save previous keyboard state
		m_prevKeyboardState = m_keyboardState;

		// Get SDL keyboard state
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);

		// Copy SDL keyboard state to input system keyboard state
		std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = Vector2{ x, y };

		m_prevMouseButtonState = m_mouseButtonState;
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // Buttons [0001] & [0RML]
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // Buttons [0010] & [0RML]
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // Buttons [0100] & [0RML]

	}
}