#include <unordered_map>

#include "State.h"
#include "StateManager.h"
#include "../Vec2.h"
#include "../entities/Button.h"

#pragma once

class MenuState : public State
{
private:
	enum MenuButton
	{
		Play,
		Options,
		Credits,
		Help,
		Quit
	};
public:
	MenuState(StateManager* manager, SDL_Renderer* renderer);
	~MenuState();
	bool eventHandler();

	void update(float dt);

	void render();

private:

	Texture* buttonTexture;

	Vec2 mouse;

	std::unordered_map<MenuButton, Button*> buttons;

	bool click();

	Texture* logo;
	Texture* background;

};