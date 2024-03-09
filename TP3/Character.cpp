#include "Character.h"

namespace TP3 {
	Character::Character(int type, int healthPoint, int attackPoint, int defensePoint, float spawnPosX, float spawnPosY) {
		this->type = type;
		this->healthPoint = healthPoint;
		this->attackPoint = attackPoint;
		this->defensePoint = defensePoint;
		this->deplacementSpeed = 7.f;
		this->isFighted = false;
		this->isLooted = false;
		this->isSwordEquiped = false;
		this->isShieldEquiped = false;

		this->initTexture(type);
		this->initSprite(spawnPosX, spawnPosY);
	}

	void Character::initTexture(int type)
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

	void Character::initSprite(float spawnPosX, float spawnPosY)
	{
		this->sprite.setTexture(this->texture);

		this->sprite.scale(0.4f, 0.4f); //originel : 140x190

		//Centrer le point d'origine (la pos du perso)
		this->sprite.setOrigin((this->sprite.getTexture()->getSize().x) / 2.f, (this->sprite.getTexture()->getSize().y) / 2.f);

		sprite.setPosition(spawnPosX, spawnPosY);
	}

	void Character::update()
	{
	}

	void Character::render(RenderTarget& target)
	{
		target.draw(this->sprite);
	}

	void Character::movePlayer(const float dirX, const float dirY)
	{
		this->sprite.move(this->deplacementSpeed * dirX, this->deplacementSpeed * dirY);
	}

	void Character::setType(int type) {
		if (type != 0 && type != 1 && type && 2) {
			cout << "\nType de personnage invalide";
			exit(1);
		}
		else {
			this->type = type;
		}
	}

	void Character::takeDamage(int damage) {
		this->healthPoint = this->healthPoint - damage;
	}

	void Character::setHealthPoint(int healthPoint) {
		this->healthPoint = healthPoint;
	}

	void Character::setAttackPoint(int attackPoint) {
		this->attackPoint = attackPoint;
	}

	void Character::setDefensePoint(int defensePoint) {
		this->defensePoint = defensePoint;
	}

	int Character::getType() {
		return this->type;
	}

	int Character::getHealthPoint() {
		return this->healthPoint;
	}

	int Character::getAttackPoint() {
		return this->attackPoint;
	}

	int Character::getDefensePoint() {
		return this->defensePoint;
	}

	Vector2f Character::getPosition()
	{
		return this->sprite.getPosition();
	}
}
