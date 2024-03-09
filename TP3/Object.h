#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

namespace TP3 {

	class Object
	{
	private:

	protected:
		
	public:
		int attackPoint;
		int defensePoint;
		int type; //0 = Sword, 1 = Shield

		Texture textureObject;
		Texture textureObjectHighlighted;
		Texture textureObjectEquiped;
		Sprite spriteObject;

		Font font;
		Text textObject;
		Text textInfo;

		bool canEquip;
		bool isEquiped;

		int getAttackPoint();
		int getDefensePoint();
		int getHealthPoint();
	};
}


