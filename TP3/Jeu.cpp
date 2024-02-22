#include "Jeu.h"
#include <string>
#include <iostream>

using namespace sf;
using namespace std;

void Jeu::initVariables()
{
	this->window = nullptr;
}

void Jeu::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 800;
	this->window = new RenderWindow(this->videoMode, "TP3 RPG", Style::Titlebar | Style::Close /*Style::Fullscreen*/);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Jeu::initJoueur()
{
	this->joueur = new Personnage(0, 100, 10, 10);
}

Jeu::Jeu()
{
	this->initVariables();
	this->initWindow();
	this->initJoueur();
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
	if (Keyboard::isKeyPressed(Keyboard::Left) && joueur->getPosition().x > 0 + ((joueur->sprite.getTexture()->getSize().x)/4.f) - 1.0 ) {
		this->joueur->bouger(-1.f, 0.f);
	}

	if (Keyboard::isKeyPressed(Keyboard::Right) && joueur->getPosition().x < window->getSize().x - ((joueur->sprite.getTexture()->getSize().x) / 4.f) - 1.0) {
		this->joueur->bouger(1.f, 0.f);
	}

	if (Keyboard::isKeyPressed(Keyboard::Up) && joueur->getPosition().y > 0 + (joueur->sprite.getTexture()->getSize().y) / 4.f) {
		this->joueur->bouger(0.f, -1.f);
	}

	if (Keyboard::isKeyPressed(Keyboard::Down) && joueur->getPosition().y < window->getSize().y - ((joueur->sprite.getTexture()->getSize().y) / 4.f) + 5.0) {
		this->joueur->bouger(0.f, 1.f);
	}
}

void Jeu::update()
{
	this->updateEvent();
	this->updateInput();

	cout << "X = " << to_string(joueur->getPosition().x) << "    Y = " << to_string(joueur->getPosition().y) << endl;
}

void Jeu::render()
{
	this->window->clear();

	this->joueur->render(*this->window);

	this->window->display();
}
