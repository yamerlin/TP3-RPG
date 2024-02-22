#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"

using namespace std;
using namespace sf;

class Personnage
{
private:
	int type; //0 = player; 1 = allié; 2 = ennemies
	int pointDeVie;
	int pointAttaque;
	int pointDefense;

	float vitesseDeplacement;

	void initTexture();
	void initSprite();

public:
	Sprite sprite;
	Texture texture;

	Personnage(int type, int nbPointDeVie, int nbPointAttaque, int nbPointDefense);
	~Personnage();

	void update();
	void render(RenderTarget& target);
	void bouger(const float dirX, const float dirY);

	void prendreDesDegats(int nbDegat);

	void setType(int type);
	void setPointDeVie(int nbPointDeVie);
	void setPointAttaque(int nbPointAttaque);
	void setPointDefense(int nbPointDefense);

	int getType();
	int getPointDeVie();
	int getPointAttaque();
	int getPointDefense();
	Vector2f getPosition();
};

