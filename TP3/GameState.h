#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Character.h"
#include "Potion.h"
#include "Sword.h"
#include "Shield.h"
#include "Object.h"

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

		const bool running() const;
		bool combat;

		Clock clock;
		//Clock pour la seed du srand()
		Clock random;
		float dt;
		float multiplier;

	private:
		GameDataRef gameData;

		RectangleShape rectangle;

		Texture textureMonde;
		Sprite spriteMonde;

		Character* player;
		Character* ennemy;
		Character* ennemyArray[3];

		list<Object*> objectList; 

		Font font;
		Text textInventaire;
		Text textStatsAttack;
		Text textStatsDefense;

		int zoneDetectionCombatX; //En nombre de pixels
		int zoneDetectionCombatY;

		int zoneDetectionObjectsX;
		int zoneDetectionObjectsY;

		//float inventoryObjectPosX;
		//float inventoryObjectPosY;

		void showInventory();

		void initPersonnages();
		void initMonde();
		void initObjects();
		void updatePlayerPos();

		bool checkIfMouseIsOverAnItem(int posX, int posY);
		Object* findObjectToHighlight(int posX, int posY);
		void detectCombat();
		bool detectObject();
		void lootDefeatedEnnemy();
		Object* findObject();
	};
}
