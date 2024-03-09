#pragma once

#include "Object.h"

using namespace std;
using namespace sf;

namespace TP3 {
	class Sword : public Object
	{
	private:
		float posX;
		float posY;

	public:
		Sword(int attackPoint, float posX, float posY);
		int getAttackPoint();
	};
}
