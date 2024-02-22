#pragma once

#include "Personnage.h"

using namespace std;
using namespace sf;

class Jeu
{
private:
	RenderWindow* window;
	VideoMode videoMode;
	Event event;

	Personnage* joueur;

	void initVariables();
	void initWindow();
	void initJoueur();

	

public:
	//Constructeur
	Jeu();

	//Destructeur
	~Jeu();

	const bool running() const;

	void updateEvent();
	void updateInput();
	void update();
	void render();
};

