#include "Personnage.h"
#include <string>
#include <iostream>
#include <list>

using namespace std;

Personnage::Personnage(int type, int nbPointDeVie, int nbPointAttaque, int nbPointDefense, float spawnPosX, float spawnPosY) {
	this->type = type;
	this->pointDeVie = nbPointDeVie;
	this->pointAttaque = nbPointAttaque;
	this->pointDefense = nbPointDefense;
	this->vitesseDeplacement = 7.f;

	this->initTexture(type);
	this->initSprite(spawnPosX, spawnPosY);
}

void Personnage::initTexture(int type)
{
	//Texture du joueur
	if (type == 0) {
		if (!this->texture.loadFromFile("Textures/joueur.png")) {
			cout << "\nErreur chargement de la texture\n";
		}
	}

	//Texture des ennemis
	if (type == 2) {
		if (!this->texture.loadFromFile("Textures/ennemi.png")) {
			cout << "\nErreur chargement de la texture\n";
		}
	}
	
}

void Personnage::initSprite(float spawnPosX, float spawnPosY)
{
	this->sprite.setTexture(this->texture);

	this->sprite.scale(0.4f, 0.4f); //originel : 140x190

	//Centrer le point d'origine (la pos du perso)
	this->sprite.setOrigin((this->sprite.getTexture()->getSize().x)/2.f, (this->sprite.getTexture()->getSize().y)/2.f);


	sprite.setPosition(spawnPosX, spawnPosY);
}

void Personnage::update()
{
}

void Personnage::render(RenderTarget& target)
{
	target.draw(this->sprite);
}

void Personnage::bougerJoueur(const float dirX, const float dirY)
{
	this->sprite.move(this->vitesseDeplacement * dirX, this->vitesseDeplacement * dirY);
}

void Personnage::setType(int type) {
	if (type != 0 && type != 1 && type && 2) {
		cout << "\nType de personnage invalide";
		exit(1);
	}
	else {
		this->type = type;
	}
}

void Personnage::prendreDesDegats(int nbDegat) {
	this->pointDeVie = this->pointDeVie - nbDegat;
}

void Personnage::setPointDeVie(int nbPointDeVie) {
	this->pointDeVie = nbPointDeVie;
}

void Personnage::setPointAttaque(int nbPointAttaque) {
	this->pointAttaque = nbPointAttaque;
}

void Personnage::setPointDefense(int nbPointDefense) {
	this->pointDefense = nbPointDefense;
}

int Personnage::getType() {
	return this->type;
}

int Personnage::getPointDeVie() {
	return this->pointDeVie;
}

int Personnage::getPointAttaque() {
	return this->pointAttaque;
}

int Personnage::getPointDefense() {
	return this->pointDefense;
}

Vector2f Personnage::getPosition()
{
	return this->sprite.getPosition();
}
