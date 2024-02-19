#include "Personnage.h"
#include <string>
#include <iostream>

using namespace std;

Personnage::Personnage(int type, int nbPointDeVie, int nbPointAttaque, int nbPointDefense) {
	this->type = type;
	this->pointDeVie = nbPointDeVie;
	this->pointAttaque = nbPointAttaque;
	this->pointDefense = nbPointDefense;
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
