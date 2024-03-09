#include "Shield.h"

namespace TP3 {

	Shield::Shield(int defensePoint, float posX, float posY) : posX(posX), posY(posY)
	{
		this->defensePoint = defensePoint;
		//On peut equiper une bouclier
		this->canEquip = true;
		this->isEquiped = false;
		this->type = 1;

		//Setter la texture
		if (!this->textureObject.loadFromFile("Textures/shieldObject1.png")) {
			cout << "\nErreur chargement de la texture\n";
		}
		this->spriteObject.setTexture(this->textureObject);
		this->spriteObject.setScale(0.5, 0.5);
		this->spriteObject.setPosition(this->posX, this->posY);

		if (!this->textureObjectHighlighted.loadFromFile("Textures/shieldObject1Highlight.png")) {
			cout << "\nErreur chargement de la texture\n";
		}
		if (!this->textureObjectEquiped.loadFromFile("Textures/shieldObject1Equiped.png")) {
			cout << "\nErreur chargement de la texture\n";
		}

		//Centrer le point d'origine de l'objet
		this->spriteObject.setOrigin((this->spriteObject.getTexture()->getSize().x) / 2.f, (this->spriteObject.getTexture()->getSize().y) / 2.f);

		//Charger la police de text
		if (!font.loadFromFile("Textures/FontPixel.ttf"))
		{
			cout << "Erreur chargement police de texte";
		}
		this->textObject.setFont(font);
		this->textInfo.setFont(font);

		//Setter le texte de découverte d'un objet
		this->textObject.setString("You found a " + to_string(this->defensePoint) + " defense point shield ! Press E to collect.");
		this->textObject.setCharacterSize(20);
		this->textObject.setOutlineThickness(2.f);
		this->textObject.setFillColor(Color::White);
		this->textObject.setOutlineColor(Color::Black);
		this->textObject.setPosition(10, 550);

		//Setter le texte d'info d'un objet
		this->textInfo.setString(to_string(this->defensePoint) + " defense point shield. \nLeft click on it to equip or unequip.");
		this->textInfo.setCharacterSize(18);
		this->textInfo.setOutlineThickness(2.f);
		this->textInfo.setFillColor(Color::Black);
		this->textInfo.setOutlineColor(Color::White);
	}

	int Object::getDefensePoint() {
		return this->defensePoint;
	}
}