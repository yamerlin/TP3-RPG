#pragma once

#include "Character.h"

namespace TP3 {

	class Combat
	{
	private:
		Character* player;
		Character* ennemy;

		Texture texture;
		Sprite spriteUICombat;

	public:
		Combat(Character* player, Character* ennemy);

		~Combat();
	};

}
