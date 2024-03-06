#include "CombatState.h"
#include "PauseState.h"

#include <iostream>

using namespace sf;
using namespace std;

namespace TP3 
{
	TP3::CombatState::CombatState(GameDataRef data, Character* player, Character* ennemy) : gameData(data), player(player), ennemy(ennemy)
	{

	}

	void CombatState::init()
	{
		//Charger la texture du background
		if (!this->textureUI.loadFromFile("Textures/combat.png")) {
			cout << "\nErreur chargement de la texture de l'ui\n";
		}
		spriteUI.setTexture(this->textureUI);



		//Charger les textures des personnages

		if (!this->texturePlayerCombat.loadFromFile("Textures/playerCombat.png")) {
			cout << "\nErreur chargement de la texture\n";
		}
		spritePlayerCombat.setTexture(this->texturePlayerCombat);

		if (!this->texturePlayerDamagedCombat.loadFromFile("Textures/playerCombatDamaged.png")) {
			cout << "\nErreur chargement de la texture\n";
		}


		if (!this->textureEnnemyCombat.loadFromFile("Textures/ennemyCombat.png")) {
			cout << "\nErreur chargement de la texture\n";
		}
		spriteEnnemyCombat.setTexture(this->textureEnnemyCombat);

		if (!this->textureEnnemyDamagedCombat.loadFromFile("Textures/ennemyCombatDamaged.png")) {
			cout << "\nErreur chargement de la texture\n";
		}


		//Positioner les personnages
		spritePlayerCombat.setPosition(0,144);
		spriteEnnemyCombat.setPosition(550,140);

		//Charger la police de text
		if (!font.loadFromFile("Textures/FontPixel.ttf"))
		{
			cout << "Erreur chargement police de texte";
		}
		textPlayerHealth.setFont(font);
		textEnnemyHealth.setFont(font);

		//Crééer les strings qui affiche les points de vies
		textPlayerHealth.setString("Health : " + to_string(this->player->getHealthPoint()));
		textEnnemyHealth.setString("Health : " + to_string(this->ennemy->getHealthPoint()));
		textPlayerHealth.setFillColor(Color::Red);
		textEnnemyHealth.setFillColor(Color::Red);

		//Positionement
		textPlayerHealth.setPosition(60,130);
		textEnnemyHealth.setPosition(600, 110);


		//Charger la textures du bouton d'attaque
		if (!this->textureButton.loadFromFile("Textures/button.png")) {
			cout << "\nErreur chargement de la texture\n";
		}
		if (!this->textureButtonOnHover.loadFromFile("Textures/buttonOnHover2.png")) {
			cout << "\nErreur chargement de la texture\n";
		}
		spriteButtonAttack.setTexture(this->textureButton);

		//Positionner le bouton
		this->spriteButtonAttack.setScale(0.7, 0.5);
		this->spriteButtonAttack.setPosition(30,635);

		//Créer le texte sur le bouton d'attaque
		textAttack.setFont(font);
		textAttack.setFillColor(Color::Red);
		textAttack.setCharacterSize(40);
		textAttack.setString("Attack !");
		textAttack.setPosition((this->spriteButtonAttack.getPosition().x) + 60, (this->spriteButtonAttack.getPosition().y) + 37);

		//Afficher les stats du joueur
		textStatsAttack.setFont(font);
		textStatsAttack.setCharacterSize(30);
		textStatsAttack.setFillColor(Color::Black);
		textStatsAttack.setString("Your attack points : " + to_string(this->player->getAttackPoint()));
		textStatsAttack.setPosition(450,625);

		textStatsDefense.setFont(font);
		textStatsDefense.setCharacterSize(30);
		textStatsDefense.setFillColor(Color::Black);
		textStatsDefense.setString("Your defense points : " + to_string(this->player->getDefensePoint()));
		textStatsDefense.setPosition(450, 725);
	}

	//Fonctions qui retourne true si la souris se trouve sur le bouton d'attaque
	bool CombatState::checkIfMouseIsOverButton(int posX, int posY)
	{
		bool isMouseOverButton = false;

		if (this->spriteButtonAttack.getGlobalBounds().contains(Vector2f(posX, posY)))
		{
			isMouseOverButton = true;
		}

		return isMouseOverButton;
	}

	void CombatState::handleInput()
	{
		sf::Event event;

		while (this->gameData->window.pollEvent(event))
		{
			//Cliquer sur le bouton fermer la fenetre
			if (Event::Closed == event.type)
			{
				this->gameData->window.close();
			}

			//Mettre en pause
			if (Event::KeyPressed == event.type)
			{
				if (event.key.code == Keyboard::Escape) {
					this->gameData->machine.addState(StateRef(new PauseState(this->gameData)), false);
				}
			}

			//Effet hover
			if (Event::MouseMoved == event.type)
			{
				bool isMouseOverButton = checkIfMouseIsOverButton(Mouse::getPosition(gameData->window).x, Mouse::getPosition(gameData->window).y);

				if (isMouseOverButton) {
					this->spriteButtonAttack.setTexture(this->textureButtonOnHover);
				}
				else {
					this->spriteButtonAttack.setTexture(this->textureButton);
				}
			}

			//Clique sur le bouton
			if (Event::MouseButtonReleased == event.type)
			{
				bool isMouseOverButton = checkIfMouseIsOverButton(Mouse::getPosition(gameData->window).x, Mouse::getPosition(gameData->window).y);

				if (isMouseOverButton) {
					this->ennemy->takeDamage(this->player->getAttackPoint());
					cout << "Ennemy took damage";
					cout << this->ennemy->getHealthPoint();

					Clock damageTime;
					damageTime.restart();

					this->spriteEnnemyCombat.setTexture(this->textureEnnemyDamagedCombat);
					
					/*Thread thread(&func);*/

					while (damageTime.getElapsedTime().asMilliseconds() < 1000)
					{
						this->gameData->window.draw(this->spriteEnnemyCombat);
					}

					this->spriteEnnemyCombat.setTexture(this->textureEnnemyCombat);
					this->gameData->window.draw(this->spriteEnnemyCombat);
				}
			}
		}
	}

	void CombatState::update(float dt)
	{
		/*cout << "Update appelle maintenant";*/
		//Updater l'affichage de la vie des personnages
		textPlayerHealth.setString("Health : " + to_string(this->player->getHealthPoint()));
		textEnnemyHealth.setString("Health : " + to_string(this->ennemy->getHealthPoint()));
	}

	void CombatState::draw(float dt)
	{
		this->gameData->window.clear();

		//Dessiner l'UI
		this->gameData->window.draw(this->spriteUI);

		//Dessiner les personnages
		this->gameData->window.draw(this->spritePlayerCombat);
		this->gameData->window.draw(this->spriteEnnemyCombat);

		//Dessiner les points de vies
		this->gameData->window.draw(this->textPlayerHealth);
		this->gameData->window.draw(this->textEnnemyHealth);

		//Dessiner le bouton d'attaque
		this->gameData->window.draw(this->spriteButtonAttack);
		this->gameData->window.draw(this->textAttack);

		//Afficher les stats
		this->gameData->window.draw(this->textStatsAttack);
		this->gameData->window.draw(this->textStatsDefense);

		this->gameData->window.display();
	}
}