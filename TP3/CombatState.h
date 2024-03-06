#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Character.h"

using namespace sf;

namespace TP3 
{
	class CombatState : public State
	{
	public:
		CombatState(GameDataRef data, Character* joueur, Character* ennemi);

		void init();
		void handleInput();
		void update(float dt);
		void draw(float dt);

	private:
		GameDataRef gameData;

		Font font;

		Character* player;
		Character* ennemy;

		Text textPlayerHealth;
		Text textEnnemyHealth;
		Text textAttack;
		Text textStatsAttack;
		Text textStatsDefense;

		Texture textureUI;
		Sprite spriteUI;

		Texture texturePlayerCombat;
		Sprite spritePlayerCombat;
		Texture texturePlayerDamagedCombat;

		Texture textureEnnemyCombat;
		Sprite spriteEnnemyCombat;
		Texture textureEnnemyDamagedCombat;

		Texture textureButton;
		Texture textureButtonOnHover;
		Sprite spriteButtonAttack;

		bool checkIfMouseIsOverButton(int posX, int posY);
	};
}