#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL_events.h>
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "XInput.lib")

dae::InputManager::~InputManager()
{
	for (auto bind : m_ConsoleCommands)
	{
		// delete commands of the binds
		delete bind.second;
	}
	for (auto bind : m_KeyboardCommands)
	{
		// delete commands of the binds
		delete bind.second;
	}
}
bool dae::InputManager::ProcessInput()
{
	// todo: read the input
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		//keystate
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(0, &m_CurrentState);

		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				return false;
			}
			if (e.type == SDL_KEYDOWN) {
				// handle key down
				auto It = m_KeyboardCommands.find(e.key.keysym.sym);
				if (It == m_KeyboardCommands.end())
					return true;
				It->second->Execute();
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
			}
		}
		//keystroke
		ZeroMemory(&m_CurrentKeyStroke, sizeof(XINPUT_KEYSTROKE));
		dwResult = XInputGetKeystroke(i, 0, &m_CurrentKeyStroke);
		if (dwResult == ERROR_SUCCESS)
		{
			// handle controller input
			for (auto It{ m_ConsoleCommands.begin() }; It != m_ConsoleCommands.end(); ++It)
			{
				// if the button is pressed and the player id is the same
				if (IsPressed(It->first.first) && It->first.second == i)
				{
					m_ConsoleCommands[It->first]->Execute();
					return true;
				}
			}
		}
	}
	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	// returns whether the given button is pressed or not.
	if (m_CurrentKeyStroke.Flags == m_KeystrokeMode && m_CurrentKeyStroke.VirtualKey == static_cast<WORD>(button))
	{
		return true;
	}
	return false;
}
void dae::InputManager::BindCommand(ControllerButtonId buttonId, Command* command)
{
	m_ConsoleCommands[buttonId] = command;
}
void dae::InputManager::BindCommand(const SDL_Keycode& keycode, Command* command)
{
	m_KeyboardCommands[keycode] = command;
}
void dae::InputManager::UnBindCommand(ControllerButtonId buttonId)
{
	auto It = m_ConsoleCommands.find(buttonId);
	if (It != m_ConsoleCommands.end())
	{
		Command* command = It->second;
		m_ConsoleCommands.erase(It);
		delete command;
	}
}
void dae::InputManager::UnBindCommand(const SDL_Keycode& keycode)
{
	auto It = m_KeyboardCommands.find(keycode);
	if (It != m_KeyboardCommands.end())
	{
		Command* command = It->second;
		m_KeyboardCommands.erase(It);
		delete command;
	}
}