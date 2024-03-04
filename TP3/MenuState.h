#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

using namespace sf;

namespace TP3
{
	class MenuState : public State
	{
	public:
		MenuState(GameDataRef data);

		void init();
		void handleInput();
		void update(float dt);
		void draw(float dt);

	private:
		GameDataRef gameData;

		Clock clock;

		VertexArray setBackgroundGradient();
	};
}
