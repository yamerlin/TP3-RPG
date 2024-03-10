#include "GameState.h"
#include "PauseState.h"
#include "CombatState.h"

#include <string>
#include <iostream>

using namespace sf;
using namespace std;

namespace TP3
{
	GameState::GameState(GameDataRef data) : gameData(data)
	{

	}

	GameState::~GameState()
	{

	}

	void GameState::initMonde()
	{
		//Map
		if (!this->textureMonde.loadFromFile("Textures/map.png")) {
			cout << "\nErreur chargement de la texture du monde\n";
		}

		this->spriteMonde.setTexture(this->textureMonde);

		//Charger la police de text
		if (!font.loadFromFile("Textures/FontPixel.ttf"))
		{
			cout << "Erreur chargement police de texte";
		}
		this->textInventaire.setFont(font);
		//Setter le texte inventaire
		this->textInventaire.setString("Inventory :");
		this->textInventaire.setCharacterSize(25);
		this->textInventaire.setFillColor(Color::Black);
		this->textInventaire.setPosition(20, 605);

		//Afficher les stats du joueur
		textStatsAttack.setFont(font);
		textStatsAttack.setCharacterSize(30);
		textStatsAttack.setFillColor(Color::Black);
		textStatsAttack.setString("Your attack points : " + to_string(this->player->getAttackPoint()));
		textStatsAttack.setPosition(445, 635);

		textStatsDefense.setFont(font);
		textStatsDefense.setCharacterSize(30);
		textStatsDefense.setFillColor(Color::Black);
		textStatsDefense.setString("Your defense points : " + to_string(this->player->getDefensePoint()));
		textStatsDefense.setPosition(445, 715);
	}

	void GameState::initObjects()
	{
		objectList.push_front(new Potion(20, 405.f, 405.f));
		objectList.push_front(new Potion(30, 950.f, 550.f));
		objectList.push_front(new Sword(20, 50.f, 550.f));
		objectList.push_front(new Shield(10, 780.f, 50.f));
	}

	void GameState::initPersonnages()
	{
		//Le joueur
		this->player = new Character(0, 300, 20, 10, 100.f, 150.f);

		//Ennemi difficile
		ennemyArray[0] = new Character(2, 400, 40, 15, 550.f, 550.f);

		//Ennemi moyen
		ennemyArray[1] = new Character(2, 100, 60, 5, 515.f, 50.f);

		//Ennemi facile
		ennemyArray[2] = new Character(2, 60, 30, 15, 950.f, 250.f);
	}


	void GameState::init()
	{
		this->multiplier = 60.f;
		this->zoneDetectionCombatX = 60;
		this->zoneDetectionCombatY = 85;
		this->zoneDetectionObjectsX = 50;
		this->zoneDetectionObjectsY = 50;

		this->initPersonnages();
		this->initMonde();
		this->initObjects();
	}

	void GameState::handleInput()
	{
		sf::Event event;

		while (this->gameData->window.pollEvent(event))
		{
			if (Event::Closed == event.type)
			{
				this->gameData->window.close();
			}

			if (Event::KeyPressed == event.type)
			{
				//Ouvrir le menu Pause
				if (event.key.code == Keyboard::Escape) {
					this->gameData->machine.addState(StateRef(new PauseState(this->gameData)), false);
				}

				//Rammaser un objet
				if (event.key.code == Keyboard::E && detectObject()) {
					//Le mettre dans l'inventaire du joueur
					this->player->inventory.push_front(findObject());

					//L'enlever de la map
					this->objectList.remove(findObject());
				}
			}

			//Mettre un effet de surlignage quand on passe la souris sur un item
			if (Event::MouseMoved == event.type)
			{
				if (checkIfMouseIsOverAnItem(Mouse::getPosition(gameData->window).x, Mouse::getPosition(gameData->window).y)) {
					Object* object = findObjectToHighlight(Mouse::getPosition(gameData->window).x, Mouse::getPosition(gameData->window).y);

					if (!object->isEquiped) {
						object->spriteObject.setTexture(object->textureObjectHighlighted);
					}
				}
				else {
					for (Object* it : this->player->inventory) {
						if (!it->isEquiped) {
							it->spriteObject.setTexture(it->textureObject);
						}
					}
				}
			}

			//Equiper et désequiper un objet
			if (Event::MouseButtonReleased == event.type)
			{
				if (checkIfMouseIsOverAnItem(Mouse::getPosition(gameData->window).x, Mouse::getPosition(gameData->window).y)) {
					Object* object = findObjectToHighlight(Mouse::getPosition(gameData->window).x, Mouse::getPosition(gameData->window).y);

					//Equiper
					if (object->canEquip && !object->isEquiped) {
						if (object->type == 0 && !this->player->isSwordEquiped) {
							object->isEquiped = true;
							this->player->isSwordEquiped = true;
							//Sprite
							object->spriteObject.setTexture(object->textureObjectEquiped);

							//Points
							this->player->setAttackPoint(this->player->getAttackPoint() + object->getAttackPoint());
							this->textStatsAttack.setString("Your attack points : " + to_string(this->player->getAttackPoint()));
						}
						else if (object->type == 1 && !this->player->isShieldEquiped) {
							object->isEquiped = true;
							this->player->isShieldEquiped = true;

							object->spriteObject.setTexture(object->textureObjectEquiped);

							this->player->setDefensePoint(this->player->getDefensePoint() + object->getDefensePoint());
							this->textStatsDefense.setString("Your defense points : " + to_string(this->player->getDefensePoint()));
						}

					}
					//Désequiper
					else if (object->canEquip && object->isEquiped) {
						if (object->type == 0) {
							object->isEquiped = false;
							this->player->isSwordEquiped = false;

							object->spriteObject.setTexture(object->textureObject);

							this->player->setAttackPoint(this->player->getAttackPoint() - object->getAttackPoint());
							this->textStatsAttack.setString("Your attack points : " + to_string(this->player->getAttackPoint()));
						}
						else if (object->type == 1) {
							object->isEquiped = false;
							this->player->isShieldEquiped = false;

							object->spriteObject.setTexture(object->textureObject);

							this->player->setDefensePoint(this->player->getDefensePoint() - object->getDefensePoint());
							this->textStatsDefense.setString("Your defense points : " + to_string(this->player->getDefensePoint()));
						}
					}
				}
			}
		}
	}

	void GameState::updatePlayerPos()
	{
		//Faire bouger le joueur tout en le gardant dans les limites de la map
		if (Keyboard::isKeyPressed(Keyboard::Left) && player->getPosition().x > 0 + ((player->sprite.getTexture()->getSize().x) / 4.f) - 1.0) {
			this->player->movePlayer(-1.f * this->dt * this->multiplier, 0.f);
		}

		if (Keyboard::isKeyPressed(Keyboard::Right) && player->getPosition().x < this->gameData->window.getSize().x - ((player->sprite.getTexture()->getSize().x) / 4.f) - 1.0) {
			this->player->movePlayer(1.f * this->dt * this->multiplier, 0.f);
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) && player->getPosition().y > 0 + (player->sprite.getTexture()->getSize().y) / 4.f) {
			this->player->movePlayer(0.f, -1.f * this->dt * this->multiplier);
		}

		if (Keyboard::isKeyPressed(Keyboard::Down) && player->getPosition().y < this->gameData->window.getSize().y - ((player->sprite.getTexture()->getSize().y) / 4.f) - 200.0) {
			this->player->movePlayer(0.f, 1.f * this->dt * this->multiplier);
		}
	}

	//Retourne l'objet de l'inventaire sur lequel est la souris
	Object* GameState::findObjectToHighlight(int posX, int posY)
	{
		Object* object = NULL;

		for (Object* it : this->player->inventory) {

			if (it->spriteObject.getGlobalBounds().contains(Vector2f(posX, posY)))
			{
				object = it;
			}
		}

		return object;
	}

	//Retourne true de si la souris est sur un objet de l'inventaire
	bool GameState::checkIfMouseIsOverAnItem(int posX, int posY)
	{
		bool isMouseOverAnItem = false;

		for (Object* it : this->player->inventory) {

			if (it->spriteObject.getGlobalBounds().contains(Vector2f(posX, posY)))
			{
				isMouseOverAnItem = true;
			}
		}

		return isMouseOverAnItem;
	}

	//Qaund un joueur s'approche d'un ennemi un combat est detecté
	void GameState::detectCombat()
	{
		for (int i = 0; i < 3; i++) {

			if (player->getPosition().x > ennemyArray[i]->getPosition().x - zoneDetectionCombatX
				&& player->getPosition().x < ennemyArray[i]->getPosition().x + zoneDetectionCombatX
				&& player->getPosition().y > ennemyArray[i]->getPosition().y - zoneDetectionCombatY
				&& player->getPosition().y < ennemyArray[i]->getPosition().y + zoneDetectionCombatY)
			{
				if (!ennemyArray[i]->isFighted) {
					cout << "Combat !" << endl;
					ennemyArray[i]->isFighted = true;

					/*this->createPotionList();*/
					this->gameData->machine.addState(StateRef(new CombatState(this->gameData, this->player, this->ennemyArray[i]/*, this->potionList*/)), false);
				}
				else {
					cout << "Ennemi deja combattu !" << endl;
				}
			}
		}
	}

	//Retourne true si le joueur est sur un objet
	bool GameState::detectObject()
	{
		bool isObject = false;

		for (Object* it : objectList) {

			if (player->getPosition().x > it->spriteObject.getPosition().x - zoneDetectionObjectsX
				&& player->getPosition().x < it->spriteObject.getPosition().x + zoneDetectionObjectsX
				&& player->getPosition().y > it->spriteObject.getPosition().y - zoneDetectionObjectsY
				&& player->getPosition().y < it->spriteObject.getPosition().y + zoneDetectionObjectsY)
			{
				isObject = true;
			}
		}

		return isObject;
	}

	//Quand je joueur s'approche d'un objet cette fonction retourne l'objet de la list objectList sur lequel il se trouve
	Object* GameState::findObject()
	{
		Object* object = NULL;

		for (Object* it : objectList) {

			if (player->getPosition().x > it->spriteObject.getPosition().x - zoneDetectionObjectsX
				&& player->getPosition().x < it->spriteObject.getPosition().x + zoneDetectionObjectsX
				&& player->getPosition().y > it->spriteObject.getPosition().y - zoneDetectionObjectsY
				&& player->getPosition().y < it->spriteObject.getPosition().y + zoneDetectionObjectsY)
			{
				object = it;
			}
		}

		return object;
	}

	//Retourne true si un ennemi a été vaincu et si il n'a pas déjà été looté
	void GameState::lootDefeatedEnnemy()
	{
		random2.restart();
		for (int i = 0; i < 3; i++) {
			if (ennemyArray[i]->isFighted && !ennemyArray[i]->isLooted) {
				ennemyArray[i]->isLooted = true;

				//Création d'un loot alléatoire
				srand(this->random.getElapsedTime().asMicroseconds() + this->random2.getElapsedTime().asMicroseconds());
				int randomObject = rand() % 3;

				//0 = Potion
				if (randomObject == 0) {
					objectList.push_front(new Potion(300, ennemyArray[i]->sprite.getPosition().x, ennemyArray[i]->sprite.getPosition().y));
				}

				//1 = Epée
				if (randomObject == 1) {
					objectList.push_front(new Sword(40, ennemyArray[i]->sprite.getPosition().x, ennemyArray[i]->sprite.getPosition().y));
				}

				//2 = Bouclier
				if (randomObject == 2) {
					objectList.push_front(new Shield(35, ennemyArray[i]->sprite.getPosition().x, ennemyArray[i]->sprite.getPosition().y));
				}
			}
		}
	}

	//void GameState::createPotionList() {
	//	for (Object* it : this->player->inventory) {
	//		//On requpére seulement les potions qui sont dans l'inventaire
	//		if (it->isPotion) {
	//			this->potionList.push_front(it);
	//		}
	//	}
	//}

	void GameState::update(float dt)
	{
		//Mettre a jour delta time
		this->dt = clock.restart().asSeconds();

		//Mettre a jour la position du joueur
		this->updatePlayerPos();

		//Detecter les combats
		this->detectCombat();

		//Vérifier si un ennemi a été battu pour pouvoir créer son loot
		this->lootDefeatedEnnemy();
	}

	void GameState::showInventory()
	{
		int objectCount = 0;
		//Position des objets dans l'inventaire
		float inventoryObjectPosX = 60.f;
		float inventoryObjectPosY = 671.f;

		for (Object* it : this->player->inventory) {
			objectCount++;
			it->spriteObject.setPosition(inventoryObjectPosX, inventoryObjectPosY);
			this->gameData->window.draw(it->spriteObject);

			inventoryObjectPosX = inventoryObjectPosX + 80.f;

			//Decaler à la deuxième ligne de l'inventaire
			if (objectCount == 5) {
				inventoryObjectPosX = 60.f;
				inventoryObjectPosY = inventoryObjectPosY + 80;
			}
		}
	}

	void GameState::draw(float dt)
	{
		this->gameData->window.clear();

		//Faire afficher la map
		this->gameData->window.draw(this->spriteMonde);

		//Afficher le texte de l'inventaire
		this->gameData->window.draw(this->textInventaire);
		this->gameData->window.draw(this->textStatsAttack);
		this->gameData->window.draw(this->textStatsDefense);
		//Afficher les objets de l'inventaire
		this->showInventory();

		//Faire afficher les ennemis
		for (int i = 0; i < 3; i++) {
			this->ennemyArray[i]->render(this->gameData->window);
		}

		//Afficher les objects
		for (Object* it : objectList) {
			this->gameData->window.draw(it->spriteObject);
		}

		//Faire afficher le joueur
		this->player->render(this->gameData->window);

		//Afficher le texte qui dit qu'on a trouvé un objet
		if (this->detectObject()) {
			this->gameData->window.draw(findObject()->textObject);
			/*cout << "Objet detecte" << endl;*/
		}

		//Afficher le texte d'information de l'objet
		if (checkIfMouseIsOverAnItem(Mouse::getPosition(gameData->window).x, Mouse::getPosition(gameData->window).y)) {
			Object* object = findObjectToHighlight(Mouse::getPosition(gameData->window).x, Mouse::getPosition(gameData->window).y);
			object->textInfo.setPosition((Mouse::getPosition(gameData->window).x) + 20, Mouse::getPosition(gameData->window).y);

			this->gameData->window.draw(object->textInfo);
		}

		this->gameData->window.display();
	}

	void GameState::resume()
	{
		cout << "Retour au jeu";
	}
}