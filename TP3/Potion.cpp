#include "Potion.h"

namespace TP3 {

	Potion::Potion(int healthPoint) : healthPoint(healthPoint)
	{
		if (!this->textureObject.loadFromFile("Textures/potionObject.png")) {
			cout << "\nErreur chargement de la texture\n";
		}
		this->spriteObject.setTexture(this->textureObject);
		this->spriteObject.setScale(0.5, 0.5);

		//Centrer le point d'origine (la pos du perso)
		this->spriteObject.setOrigin((this->spriteObject.getTexture()->getSize().x) / 2.f, (this->spriteObject.getTexture()->getSize().y) / 2.f);
	}

	int Potion::getHealthPoint() {
		return this->healthPoint;
	}
}