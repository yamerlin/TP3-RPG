#include "Potion.h"

namespace TP3 {

	Potion::Potion(int healthPoint) : healthPoint(healthPoint)
	{
		if (!this->textureObject.loadFromFile("Textures/potionObject.png")) {
			cout << "\nErreur chargement de la texture\n";
		}
		this->spriteObject.setTexture(this->textureObject);
		this->spriteObject.setScale(0.5, 0.5);

		//Centrer le point d'origine de l'objet
		this->spriteObject.setOrigin((this->spriteObject.getTexture()->getSize().x) / 2.f, (this->spriteObject.getTexture()->getSize().y) / 2.f);

		//Charger la police de text
		if (!font.loadFromFile("Textures/FontPixel.ttf"))
		{
			cout << "Erreur chargement police de texte";
		}
		this->textObject.setFont(font);

		//Setter le texte de découverte d'un objet
		this->textObject.setString("You found a " + to_string(this->healthPoint) + " health point potion ! Press E to collect.");
		this->textObject.setCharacterSize(20);
		this->textObject.setOutlineThickness(2.f);
		this->textObject.setFillColor(Color::White);
		this->textObject.setOutlineColor(Color::Black);
		this->textObject.setPosition(10,550);
	}

	int Potion::getHealthPoint() {
		return this->healthPoint;
	}
}