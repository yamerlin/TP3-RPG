#include "GameState.h"
#include "Combat.h"
#include "PauseState.h"

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
		if (!this->textureMonde.loadFromFile("Textures/maptest1.png")) {
			cout << "\nErreur chargement de la texture du monde\n";
		}

		this->spriteMonde.setTexture(this->textureMonde);
	}

	void GameState::initPersonnages()
	{
		this->joueur = new Character(0, 100, 20, 10, 100.f, 150.f);

		tableauEnnemi[0] = new Character(2, 100, 10, 10, 550.f, 550.f);
		tableauEnnemi[1] = new Character(2, 100, 10, 10, 515.f, 50.f);
		tableauEnnemi[2] = new Character(2, 100, 10, 10, 950.f, 250.f);
	}


	void GameState::init()
	{
		this->multiplier = 60.f;
		this->zoneDetectionCombatX = 60;
		this->zoneDetectionCombatY = 85;

		this->initMonde();
		this->initPersonnages();
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
				if (event.key.code == Keyboard::Escape) {
					this->gameData->machine.addState(StateRef(new PauseState(this->gameData)), false);
				}
			}
		}
	}

	void GameState::updatePlayerPos()
	{
		//Faire bouger le joueur tout en le gardant dans les limites de la map
		if (Keyboard::isKeyPressed(Keyboard::Left) && joueur->getPosition().x > 0 + ((joueur->sprite.getTexture()->getSize().x) / 4.f) - 1.0) {
			this->joueur->movePlayer(-1.f * this->dt * this->multiplier, 0.f);
		}

		if (Keyboard::isKeyPressed(Keyboard::Right) && joueur->getPosition().x < this->gameData->window.getSize().x - ((joueur->sprite.getTexture()->getSize().x) / 4.f) - 1.0) {
			this->joueur->movePlayer(1.f * this->dt * this->multiplier, 0.f);
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) && joueur->getPosition().y > 0 + (joueur->sprite.getTexture()->getSize().y) / 4.f) {
			this->joueur->movePlayer(0.f, -1.f * this->dt * this->multiplier);
		}

		if (Keyboard::isKeyPressed(Keyboard::Down) && joueur->getPosition().y < this->gameData->window.getSize().y - ((joueur->sprite.getTexture()->getSize().y) / 4.f) - 200.0) {
			this->joueur->movePlayer(0.f, 1.f * this->dt * this->multiplier);
		}
	}

	//Qaund un joueur s'approche d'un ennemi un combat est detecté
	void GameState::detecterCombat()
	{
		for (int i = 0; i < 3; i++) {

			if (joueur->getPosition().x > tableauEnnemi[i]->getPosition().x - zoneDetectionCombatX
				&& joueur->getPosition().x < tableauEnnemi[i]->getPosition().x + zoneDetectionCombatX
				&& joueur->getPosition().y > tableauEnnemi[i]->getPosition().y - zoneDetectionCombatY
				&& joueur->getPosition().y < tableauEnnemi[i]->getPosition().y + zoneDetectionCombatY)
			{
				if (!tableauEnnemi[i]->isFighted) {
					cout << "Combat !" << endl;
					tableauEnnemi[i]->isFighted = true;
				}
				else {
					cout << "Ennemi deja combattu !" << endl;
				}
			}
		}
	}

	void GameState::update(float dt)
	{
		//Mettre a jour delta time
		this->dt = clock.restart().asSeconds();

		//Mettre a jour la position du joueur
		this->updatePlayerPos();

		//Detecter les combats
		this->detecterCombat();
	}

	void GameState::draw(float dt)
	{
		this->gameData->window.clear(sf::Color::Red);

		//Faire afficher la map
		this->gameData->window.draw(this->spriteMonde);

		//Faire afficher les ennemis
		for (int i = 0; i < 3; i++) {
			this->tableauEnnemi[i]->render(this->gameData->window);
		}

		//Faire afficher le joueur
		this->joueur->render(this->gameData->window);

		this->gameData->window.display();
	}

	void GameState::resume()
	{
		cout << "Retour au jeu";
	}
}