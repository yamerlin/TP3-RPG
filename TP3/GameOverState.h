#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

using namespace sf;

namespace TP3
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data);

		void init();
		void handleInput();
		void update(float dt);
		void draw(float dt);

	private:
		VertexArray setBackgroundGradient();

		int checkIfMouseIsOverAButton(int posX, int posY);

		GameDataRef gameData;

		Clock clock;

		Texture textureButton;
		Texture textureButtonOnHover;

		Sprite spriteButtonQuit;

		Font font;
		Text textQuit;
		Text textGameOver;

		Vector2f buttonOrigin;

		float buttonScaleX;
		float buttonScaleY;
		int buttonPosX;
		int buttonPosY;

		int textSize;
	};
}
