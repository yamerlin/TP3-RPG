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

	Texture textureMonde;
	Sprite spriteMonde;

	Personnage* joueur;
	Personnage* ennemi;
	Personnage* tableauEnnemi[3];

	int zoneDetectionCombatX; //En nombre de pixels
	int zoneDetectionCombatY;

	void initVariables();
	void initWindow();
	void initPersonnages();
	void initMonde();

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
	void renderMonde();
	void detecterCombat();
};

