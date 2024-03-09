#pragma once
#include <string>
#include <iostream>
#include <list>
#include "Object.h"

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"

using namespace std;
using namespace sf;

namespace TP3 {

	class Character
	{
	private:
		int type; //0 = joueur; 1 = allié; 2 = ennemies
		int healthPoint;
		int attackPoint;
		int defensePoint;

		float deplacementSpeed;

		void initTexture(int type);
		void initSprite(float spawnPosX, float spawnPosY);

	public:
		Sprite sprite;
		Texture texture;
		bool isFighted;
		bool isLooted;

		bool isSwordEquiped;
		bool isShieldEquiped;

		Character(int type, int healthPoint, int attackPoint, int defensePoint, float spawnPosX, float spawnPosY);
		list<Object*> inventory;

		void update();
		void render(RenderTarget& target);
		void movePlayer(const float dirX, const float dirY);

		void takeDamage(int damage);

		void setType(int type);
		void setHealthPoint(int healthPoint);
		void setAttackPoint(int attackPoint);
		void setDefensePoint(int defensePoint);

		int getType();
		int getHealthPoint();
		int getAttackPoint();
		int getDefensePoint();
		Vector2f getPosition();
	};
}

