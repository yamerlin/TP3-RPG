#include "CombatState.h"

using namespace sf;
using namespace std;

namespace TP3 
{
	TP3::CombatState::CombatState(GameDataRef data, Character* player, Character* ennemy/*, list<Object*> potionList*/) : gameData(data), player(player), ennemy(ennemy)/*, potionList(potionList)*/
	{

	}

	void CombatState::init()
	{
		this->isCombatOver = false;

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
		textStatsAttack.setPosition(445, 635);

		textStatsDefense.setFont(font);
		textStatsDefense.setCharacterSize(30);
		textStatsDefense.setFillColor(Color::Black);
		textStatsDefense.setString("Your defense points : " + to_string(this->player->getDefensePoint()));
		textStatsDefense.setPosition(445, 715);

		//Initialiser le text de status du combat; gagné ou perdu
		textCombatStatus.setFont(font);
		textCombatStatus.setFillColor(Color::Red);
		textCombatStatus.setOutlineThickness(5.f);
		textCombatStatus.setOutlineColor(Color::Black);
		textCombatStatus.setCharacterSize(50);

		//Choix du joueur qui commence à attaquer : 0=joueur, 1=ennemi
		random.restart();
		srand(this->random.getElapsedTime().asMicroseconds()); //On met une clock en temps que seed pour que ca soit réélement aléatoire enfin presque réélement bref ça l'est jamais réélement mais voila on fait genre
		this->playerTurn = rand() % 2;

		//Console log
		if (this->playerTurn == 1) {
			cout << "L'ennemi commence" << endl;
		}
		else {
			cout << "Le joueur commence" << endl;
		}
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

	//Change le tour du joueur qui doit attaquer
	void CombatState::changeTurn()
	{
		if (this->playerTurn == 0) {
			this->playerTurn = 1;
		}
		else {
			this->playerTurn = 0;
		}
	}

	bool CombatState::checkIfSomeoneLost()
	{
		bool endCombat = false;

		//Defaite du joueur
		if (this->player->getHealthPoint() <= 0) {

			//Ajouter les potions disponibles de l'inventaire dans la liste des potions
			for (Object* it : this->player->inventory) {
				if (it->isPotion) {
					this->potionList.push_front(it);
				}
			}

			//Vérifier si il y a des potions disponible
			if (!potionList.empty()) {
				//Utiliser la dernière potion de la liste (donc la première qui avait été ajouté dans l'inventaire)
				
				Object* potion = NULL;
				//Défiler jusqu'a la derniere potion
				for (Object* it : potionList) {
					potion = it;
				}
				//Redonner la vie
				this->player->setHealthPoint(potion->getHealthPoint());
				//Supprimer la potion de la liste et de l'inventaire
				this->potionList.remove(potion);
				this->player->inventory.remove(potion);

				//Informer le joueur qu'une potion a été utilisée
				cout << "Potion utilisé" << endl;
			}
			else {
				//Si il n'y a plus de potions disponible, mourir
				cout << "Vous avez perdu" << endl;

				cout << "Combat fini" << endl;
				this->combatEndDelay.restart();

				isCombatOver = true;
				endCombat = true;

				textCombatStatus.setString("You lost ...");
				textCombatStatus.setOrigin(Vector2f((this->textCombatStatus.getGlobalBounds().width) / 2, (this->textCombatStatus.getGlobalBounds().height) / 2));
				textCombatStatus.setPosition((this->gameData->window.getSize().x) / 2, ((this->gameData->window.getSize().y) / 2) - 100);
			}
		}

		//Defaite de l'ennemi
		if (this->ennemy->getHealthPoint() <= 0) {
			cout << "Vous avez gagne" << endl;

			cout << "Combat fini" << endl;
			this->combatEndDelay.restart();

			isCombatOver = true;
			endCombat = true;

			textCombatStatus.setString("You won !");
			textCombatStatus.setOrigin(Vector2f((this->textCombatStatus.getGlobalBounds().width) / 2, (this->textCombatStatus.getGlobalBounds().height) / 2));
			textCombatStatus.setPosition((this->gameData->window.getSize().x) / 2, ((this->gameData->window.getSize().y) / 2)-100);
		}

		return endCombat;
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

				//Attaque du joueur
				if (isMouseOverButton && playerTurn == 0 && !isCombatOver) {

					//Calculer les dégats
					int damage = (this->player->getAttackPoint()) - (this->ennemy->getDefensePoint());

					//On vérifiequ'on va pas infliger des dégats négatifs
					if (damage < 0) {
						damage = 0;
					}

					//Infliger les dégats
					this->ennemy->takeDamage(damage);
					cout << "Ennemy took damage";
					cout << this->ennemy->getHealthPoint();
					
					//Lancer la clock pour le sprite
					this->damageTimeEnnemy.restart();

					//Lancer la clock pour le delais d'attaque
					this->ennemyAttackDelay.restart();

					//Changer le sprite
					this->spriteEnnemyCombat.setTexture(this->textureEnnemyDamagedCombat);

					//Changer le tour
					changeTurn();
				}
			}
		}
	}

	

	void CombatState::update(float dt)
	{
		/*cout << "Update appelle maintenant";*/


		//Updater l'affichage de la vie des personnages en vérifiant qu'il ne sont pas négatif
		int playerHealth = this->player->getHealthPoint();
		if (playerHealth < 0) {
			playerHealth = 0;
		}
		textPlayerHealth.setString("Health : " + to_string(playerHealth));

		int ennemyHealth = this->ennemy->getHealthPoint();
		if (ennemyHealth < 0) {
			ennemyHealth = 0;
		}
		textEnnemyHealth.setString("Health : " + to_string(ennemyHealth));

		//Updater le sprite des personnage prenant des dégats
		if (this->damageTimeEnnemy.getElapsedTime().asMilliseconds() > 800) {
			this->spriteEnnemyCombat.setTexture(this->textureEnnemyCombat);
		}

		if (this->damageTimePlayer.getElapsedTime().asMilliseconds() > 800) {
			this->spritePlayerCombat.setTexture(this->texturePlayerCombat);
		}

		//Attaque de l'ennemi, vérifier que c'est son tour et qu'il a bien attendu un petit délai
		if (playerTurn == 1 && ennemyAttackDelay.getElapsedTime().asMilliseconds() > 1100 && !isCombatOver) {
			
			//Calculer les dégats
			int damage = (this->ennemy->getAttackPoint()) - (this->player->getDefensePoint());

			//On vérifiequ'on va pas infliger des dégats négatifs
			if (damage < 0) {
				damage = 0;
			}

			//Infliger les dégats
			this->player->takeDamage(damage);

			//Lancer la clock
			this->damageTimePlayer.restart();

			//Changer le sprite
			this->spritePlayerCombat.setTexture(this->texturePlayerDamagedCombat);

			//Changer le tour
			changeTurn();
		}

		//Vérifier si il ya eu une défaite
		if (!isCombatOver) {
			checkIfSomeoneLost();
		}
		
		if (isCombatOver && combatEndDelay.getElapsedTime().asMilliseconds() > 2000) {
			this->gameData->machine.addState(StateRef(new GameOverState(this->gameData)), true);
		}
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

		//Status du combat
		this->gameData->window.draw(this->textCombatStatus);

		this->gameData->window.display();
	}
}