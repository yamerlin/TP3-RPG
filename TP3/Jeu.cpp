#include "Jeu.h"

using namespace sf;
using namespace std;

void Jeu::initVariables()
{
	this->window = nullptr;
}

void Jeu::initWindow()
{
	this->videoMode.height = 1080;
	this->videoMode.width = 1920;
	this->window = new RenderWindow(this->videoMode, "TP3 RPG", Style::Titlebar | Style::Close /*Style::Fullscreen*/);
}

Jeu::Jeu()
{
	this->initVariables();
	this->initWindow();
}

Jeu::~Jeu()
{
	delete this->window;
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

void Jeu::update()
{
	this->updateEvent();
}

void Jeu::render()
{
	this->window->clear();

	this->window->display();
}
