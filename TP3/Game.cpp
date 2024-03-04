#include "Game.h"
#include "MenuState.h"

#include <stdlib.h>


namespace TP3
{
	Game::Game(int width, int height, string title)
	{
		gameData->window.create(VideoMode(width, height), title, Style::Close | Style::Titlebar);
		gameData->window.setVerticalSyncEnabled(false);

		gameData->machine.addState(StateRef(new MenuState(this->gameData)));

		this->run();
	}

	void Game::run()
	{
		while (this->gameData->window.isOpen())
		{
			float dt = clock.restart().asSeconds();

			this->gameData->machine.processStateChanges();

			this->gameData->machine.getActiveState()->handleInput();
			this->gameData->machine.getActiveState()->update(dt);
			this->gameData->machine.getActiveState()->draw(dt);
		}
	}
}