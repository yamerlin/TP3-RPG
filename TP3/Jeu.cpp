#include "Jeu.h"
#include <string>
#include <iostream>

using namespace sf;
using namespace std;

void Jeu::initVariables()
{
	this->window = nullptr;
	this->zoneDetectionCombatX = 60;
	this->zoneDetectionCombatY = 85;
}

void Jeu::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 1000;
	this->window = new RenderWindow(this->videoMode, "TP3 RPG", Style::Titlebar | Style::Close /*Style::Fullscreen*/);
	//this->window->setFramerateLimit(5);
	this->window->setVerticalSyncEnabled(false);
}

void Jeu::initPersonnages()
{
	this->joueur = new Personnage(0, 100, 10, 10, 100.f, 150.f);

	/*this->ennemi = new Personnage(2, 100, 10, 10);
	this->ennemi2 = new Personnage(2, 100, 10, 10);
	this->ennemi3 = new Personnage(2, 100, 10, 10);*/

	tableauEnnemi[0] = new Personnage(2, 100, 10, 10, 550.f, 550.f);
	tableauEnnemi[1] = new Personnage(2, 100, 10, 10, 515.f, 50.f);
	tableauEnnemi[2] = new Personnage(2, 100, 10, 10, 950.f, 250.f);
}

void Jeu::initMonde()
{
	if (!this->textureMonde.loadFromFile("Textures/maptest1.png")) {
		cout << "\nErreur chargement de la texture du monde\n";
	}
	
	this->spriteMonde.setTexture(this->textureMonde);
}

Jeu::Jeu(Clock clock, float dt)
{
	this->initVariables();
	this->initWindow();
	this->initMonde();
	this->initPersonnages();
	this->clock = clock;
	this->dt = dt;
	this->multiplieur = 60.f;
}

Jeu::~Jeu()
{
	delete this->window;
	delete this->joueur;
}

const bool Jeu::running() const
{
	return this->window->isOpen();
}


//Recupérer les event
void Jeu::updateEvent()
{
	while (this->window->pollEvent(this->event)) {
		switch (this->event.type) {

		case Event::Closed():
			this->window->close();
			break;

		case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape) {
				this->window->close();
			}
			break;
		}
	}
}

void Jeu::updateInput()
{
	//Mettre a jour delta time
	dt = clock.restart().asSeconds();

	//Faire bouger le joueur tout en le gardant dans les limites de la map
	if (Keyboard::isKeyPressed(Keyboard::Left) && joueur->getPosition().x > 0 + ((joueur->sprite.getTexture()->getSize().x)/4.f) - 1.0 ) {
		this->joueur->bougerJoueur(-1.f * dt * multiplieur, 0.f);
	}

	if (Keyboard::isKeyPressed(Keyboard::Right) && joueur->getPosition().x < window->getSize().x - ((joueur->sprite.getTexture()->getSize().x) / 4.f) - 1.0) {
		this->joueur->bougerJoueur(1.f * dt * multiplieur, 0.f);
	}

	if (Keyboard::isKeyPressed(Keyboard::Up) && joueur->getPosition().y > 0 + (joueur->sprite.getTexture()->getSize().y) / 4.f) {
		this->joueur->bougerJoueur(0.f, -1.f * dt * multiplieur);
	}

	if (Keyboard::isKeyPressed(Keyboard::Down) && joueur->getPosition().y < window->getSize().y - ((joueur->sprite.getTexture()->getSize().y) / 4.f) - 200.0) {
		this->joueur->bougerJoueur(0.f, 1.f * dt * multiplieur);
	}
}

void Jeu::renderMonde()
{
	this->window->draw(this->spriteMonde);
}

//Qaund un joueur s'approche d'un ennemi un combat est detecté
void Jeu::detecterCombat()
{
	for (int i = 0; i < 3; i++) {

		if (	joueur->getPosition().x > tableauEnnemi[i]->getPosition().x - zoneDetectionCombatX
			&& joueur->getPosition().x < tableauEnnemi[i]->getPosition().x + zoneDetectionCombatX
			&& joueur->getPosition().y > tableauEnnemi[i]->getPosition().y - zoneDetectionCombatY
			&& joueur->getPosition().y < tableauEnnemi[i]->getPosition().y + zoneDetectionCombatY)
		{
			if (!tableauEnnemi[i]->combattu) {
				cout << "Combat !" << endl;
				tableauEnnemi[i]->combattu = true;
			}
			else {
				cout << "Ennemi deja combattu !" << endl;
			}
		}
	}
}

void Jeu::update()
{
	this->updateEvent();
	this->updateInput();
	this->detecterCombat();

	//cout << "X = " << to_string(joueur->getPosition().x) << "    Y = " << to_string(joueur->getPosition().y) << endl;
}

void Jeu::render()
{
	this->window->clear();

	//Faire afficher la map
	this->renderMonde();

	//Faire afficher les ennemis
	for (int i = 0; i < 3; i++) {
		this->tableauEnnemi[i]->render(*this->window);
	}
	
	//Faire afficher le joueur
	this->joueur->render(*this->window);

	this->window->display();

	//cout << "dt: " << dt << endl;
}
