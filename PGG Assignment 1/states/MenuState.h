#include <unordered_map>

#include "State.h"
#include "StateManager.h"
#include "../Vec2.h"
#include "../entities/Button.h"
#include "../Music.h"

#pragma once

/**
@class MenuState
@brief The state which contains the menu
*/
class MenuState : public State
{
private:
	/// All the possible buttons on this menu
	enum MenuButton
	{
		Play,
		Quit
	};
public:
	/**
	@brief Create the State
	@param StateManager* - Pointer to the current state manager
	@param SDL_Renderer* - Renderer
	*/
	MenuState(StateManager* manager, SDL_Renderer* renderer);

	~MenuState();

	/**
	@brief Handles any events such as keyboard/mouse input
	*/
	bool eventHandler();

	/**
	@brief Update any internal values
	@param float - delta time
	*/
	void update(float dt);

	/**
	@brief Render any sprites relevant to the state
	*/
	void render();

private:
	/// Buttons background texture
	Texture* buttonTexture;

	/// The mouse's current position
	Vec2 mouse;

	/// Array of all of the buttons in the menu
	std::unordered_map<MenuButton, Button*> buttons;

	/**
	@brief When the mouse is clicked this function checks which/if a button was pressed
	@return bool - If the game should continue, False to exit
	*/
	bool click();

	///Game Logo texture
	Texture* logo;

	///Menu screen background texture
	Texture* background;

	///Background music
	Music* music;

};