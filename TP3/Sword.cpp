#include "Sword.h"

namespace TP3 {

	Sword::Sword(int attackPoint, float posX, float posY) : /*attackPoint(attackPoint),*/ posX(posX), posY(posY)
	{
		this->attackPoint = attackPoint;
		//On peut equiper une épée
		this->canEquip = true;
		this->isEquiped = false;
		this->type = 0;

		//Setter la texture
		if (!this->textureObject.loadFromFile("Textures/swordObject1.png")) {
			cout << "\nErreur chargement de la texture\n";
		}
		this->spriteObject.setTexture(this->textureObject);
		this->spriteObject.setScale(0.5, 0.5);
		this->spriteObject.setPosition(this->posX, this->posY);

		if (!this->textureObjectHighlighted.loadFromFile("Textures/swordObject1Highlight.png")) {
			cout << "\nErreur chargement de la texture\n";
		}
		if (!this->textureObjectEquiped.loadFromFile("Textures/swordObject1Equiped.png")) {
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
		this->textObject.setString("You found a " + to_string(this->attackPoint) + " attack point sword ! Press E to collect.");
		this->textObject.setCharacterSize(20);
		this->textObject.setOutlineThickness(2.f);
		this->textObject.setFillColor(Color::White);
		this->textObject.setOutlineColor(Color::Black);
		this->textObject.setPosition(10, 550);

		//Setter le texte d'info d'un objet
		this->textInfo.setString(to_string(this->attackPoint) + " attack point sword. \nLeft click on it to equip or unequip.");
		this->textInfo.setCharacterSize(18);
		this->textInfo.setOutlineThickness(2.f);
		this->textInfo.setFillColor(Color::Black);
		this->textInfo.setOutlineColor(Color::White);
	}

	int Object::getAttackPoint() {
		return this->attackPoint;
	}
}