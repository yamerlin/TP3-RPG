#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <iostream>
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
		//Clock pour la seed du srand()
		Clock random;

		//Clocks pour afficher le sprite de degat seulement un petit temps
		Clock damageTimeEnnemy;
		Clock damageTimePlayer;

		//Clock délais avant attaque de l'ennemi pour pas que ca soit instantané après l'attaque du joueur
		Clock ennemyAttackDelay;

		//Clock pour avoir un delai en fin de match
		Clock combatEndDelay;

		GameDataRef gameData;

		Font font;

		Character* player;
		Character* ennemy;

		Text textPlayerHealth;
		Text textEnnemyHealth;
		Text textAttack;
		Text textStatsAttack;
		Text textStatsDefense;

		Text textCombatStatus; //Gagné ou perdu

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

		int playerTurn;
		bool isCombatOver;

		bool checkIfMouseIsOverButton(int posX, int posY);
		void changeTurn();

		bool checkIfSomeoneLost();
	};
}