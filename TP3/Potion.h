#pragma once

#include "Object.h"

using namespace std;
using namespace sf;

namespace TP3 {
	class Potion : public Object
	{
	private:
		float posX;
		float posY;

	public:
		Potion(int healthPoint, float posX, float posY);
		int getHealthPoint();
	};
}
