#pragma once

#include "Object.h"

using namespace std;
using namespace sf;

namespace TP3 {
	class Shield : public Object
	{
	private:
		float posX;
		float posY;

	public:
		Shield(int defensePoint, float posX, float posY);
		int getDefensePoint();
	};
}
