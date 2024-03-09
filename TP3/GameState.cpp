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
	}

	void GameState::initPersonnages()
	{
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

					this->gameData->machine.addState(StateRef(new CombatState(this->gameData, this->player, this->ennemyArray[i])), false);
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

	void GameState::update(float dt)
	{
		//Mettre a jour delta time
		this->dt = clock.restart().asSeconds();

		//Mettre a jour la position du joueur
		this->updatePlayerPos();

		//Detecter les combats
		this->detectCombat();
	}

	void GameState::showInventory()
	{
		//Position des objets dans l'inventaire
		float inventoryObjectPosX = 60.f;
		float inventoryObjectPosY = 671.f;

		for (Object* it : this->player->inventory) {
			it->spriteObject.setPosition(inventoryObjectPosX, inventoryObjectPosY);
			this->gameData->window.draw(it->spriteObject);

			inventoryObjectPosX = inventoryObjectPosX + 50.f;
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
		/*for (int i = 0; i < size(objectArray); i++) {
			this->findObject()->spriteObject;
		}*/
		for (Object* it : objectList) {
			this->gameData->window.draw(it->spriteObject);
		}

		//Faire afficher le joueur
		this->player->render(this->gameData->window);

		//Detecter les objets
		if (this->detectObject()) {
			this->gameData->window.draw(findObject()->textObject);
			cout << "Objet detecte" << endl;
		}

		this->gameData->window.display();
	}

	void GameState::resume()
	{
		cout << "Retour au jeu";
	}
}