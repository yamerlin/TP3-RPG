#pragma once

#include "Object.h"

using namespace std;
using namespace sf;

namespace TP3 {
	class Potion : public Object
	{
	private:
		int healthPoint;

	public:
		Potion(int healthPoint);

		int getHealthPoint();
	};
}
