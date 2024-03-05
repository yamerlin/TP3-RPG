#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

using namespace sf;

namespace TP3
{
	class PauseState : public State
	{
	public:
		PauseState(GameDataRef data);

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

		Sprite spriteButtonPlay;
		Sprite spriteButtonSave;
		Sprite spriteButtonQuit;

		Font font;
		Text textPauseMenu;
		Text textPlay;
		Text textSave;
		Text textQuit;

		Vector2f buttonOrigin;

		float buttonScaleX;
		float buttonScaleY;
		int buttonPosX;
		int buttonPosY;

		int textSize;
	};
}
