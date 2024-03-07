#pragma once

#include "Object.h"

using namespace std;
using namespace sf;

namespace TP3 {
	class Sword : public Object
	{
	private:
		int attackPoint;

	public:
		Sword(int attackPoint);

		int getAttackPoint();
	};
}
