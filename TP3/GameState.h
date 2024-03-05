#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Character.h"

using namespace sf;

namespace TP3
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);
		~GameState();

		void init();
		void handleInput();
		void update(float dt);
		void draw(float dt);

		void resume();


		void renderMonde();
		void detecterCombat();

		const bool running() const;
		bool combat;

		Clock clock;
		float dt;
		float multiplier;

	private:
		GameDataRef gameData;

		RectangleShape rectangle;

		Texture textureMonde;
		Sprite spriteMonde;

		Character* joueur;
		Character* ennemi;
		Character* tableauEnnemi[3];

		int zoneDetectionCombatX; //En nombre de pixels
		int zoneDetectionCombatY;

		void initPersonnages();
		void initMonde();
		void updatePlayerPos();
	};
}


