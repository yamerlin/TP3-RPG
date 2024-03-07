#pragma once

#include "Object.h"

using namespace std;
using namespace sf;

namespace TP3 {
	class Shield : public Object
	{
	private:
		int defensePoint;

	public:
		Shield(int defensePoint);

		int getDefensePoint();
	};
}
