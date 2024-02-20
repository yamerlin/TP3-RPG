#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"

#include "Personnage.h"

using namespace std;
using namespace sf;

class Jeu
{
private:
	RenderWindow* window;
	VideoMode videoMode;
	Event event;

	void initVariables();
	void initWindow();

public:
	//Constructeur
	Jeu();

	//Destructeur
	~Jeu();

	const bool running() const;

	void updateEvent();
	void update();
	void render();
};

