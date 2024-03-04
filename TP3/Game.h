#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"

using namespace std;
using namespace sf;

namespace TP3
{
	struct GameData
	{
		StateMachine machine;
		RenderWindow window;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class Game
	{
	public:
		Game(int width, int height, string title);

	private:
		GameDataRef gameData = make_shared<GameData>();
		Clock clock;
		void run();
	};


}