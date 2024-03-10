#include "MenuState.h"
#include "GameState.h"

#include <iostream>
#include "GameOverState.h"

using namespace sf;
using namespace std;

namespace TP3
{
	GameOverState::GameOverState(GameDataRef data) : gameData(data)
	{

	}

	void GameOverState::init()
	{
		//Charger la texture des boutons
		if (!this->textureButton.loadFromFile("Textures/button.png")) {
			cout << "\nErreur chargement de la texture du monde\n";
		}
		if (!this->textureButtonOnHover.loadFromFile("Textures/buttonOnHover.png")) {
			cout << "\nErreur chargement de la texture du monde\n";
		}

		//Donner les textures des sprites
		this->spriteButtonQuit.setTexture(this->textureButton);

		//Mettre l'origin au centre des boutons
		this->buttonOrigin = Vector2f((this->spriteButtonQuit.getLocalBounds().width) / 2, (this->spriteButtonQuit.getLocalBounds().height) / 2);
		this->spriteButtonQuit.setOrigin(buttonOrigin);

		//Mettre les positions au centre de la fenetre
		this->buttonPosX = (this->gameData->window.getSize().x) / 2;
		this->buttonPosY = (this->gameData->window.getSize().y) / 2;

		//Positionner les boutons par rapport au centre de la fenêtre
		this->spriteButtonQuit.setPosition(buttonPosX, buttonPosY);

		//Régler la taille des boutons
		this->buttonScaleX = 0.7;
		this->buttonScaleY = 0.5;
		this->spriteButtonQuit.setScale(buttonScaleX, buttonScaleY);


		//Charger la police de text
		if (!font.loadFromFile("Textures/FontPixel.ttf"))
		{
			cout << "Erreur chargement police de texte";
		}
		textQuit.setFont(font);
		textGameOver.setFont(font);

		//Setter les texts
		textQuit.setString("Quit");
		textGameOver.setString("Game Over !");

		//Régler la taille des texts
		this->textSize = 40;
		textQuit.setCharacterSize(this->textSize);
		textGameOver.setCharacterSize(80);

		//Mettre l'origin au centre des texts
		this->textQuit.setOrigin(Vector2f((this->textQuit.getLocalBounds().width) / 2, (this->textQuit.getLocalBounds().height) / 2));
		this->textGameOver.setOrigin(Vector2f((this->textGameOver.getLocalBounds().width) / 2, (this->textGameOver.getLocalBounds().height) / 2));

		//Régler la couleurs des texts
		textQuit.setFillColor(Color(0, 216, 255));
		textGameOver.setFillColor(Color::Red);
		textGameOver.setOutlineThickness(8.f);
		textGameOver.setOutlineColor(Color::Black);

		//Régler la position des texts
		textQuit.setPosition(this->spriteButtonQuit.getPosition().x, this->spriteButtonQuit.getPosition().y);
		textGameOver.setPosition((this->gameData->window.getSize().x)/2, 100);
	}

	//Fonctions qui retourne le numéro du boutons sur lequel la souris se trouve
	int GameOverState::checkIfMouseIsOverAButton(int posX, int posY)
	{
		//Retourne 0 -> Rien ou 1 -> Play ou 2 -> Load ou 3 -> Quit
		int button = 0;

		if (this->spriteButtonQuit.getGlobalBounds().contains(Vector2f(posX, posY)))
		{
			button = 1;
		}

		return button;
	}

	void GameOverState::handleInput()
	{
		sf::Event event;

		while (this->gameData->window.pollEvent(event))
		{
			if (Event::Closed == event.type)
			{
				this->gameData->window.close();
			}

			//Clique sur les boutons
			if (Event::MouseButtonReleased == event.type)
			{
				int isMouseOverAButton = checkIfMouseIsOverAButton(Mouse::getPosition(gameData->window).x, Mouse::getPosition(gameData->window).y);

				//Quitter
				if (isMouseOverAButton == 1) {
					this->gameData->window.close();
				}
			}

			//Mettre un effet de surlignage des boutons quand on passe la souris dessus
			if (Event::MouseMoved == event.type)
			{
				int isMouseOverAButton = checkIfMouseIsOverAButton(Mouse::getPosition(gameData->window).x, Mouse::getPosition(gameData->window).y);

				if (isMouseOverAButton == 1) {
					this->spriteButtonQuit.setTexture(this->textureButtonOnHover);
				}
				else {
					this->spriteButtonQuit.setTexture(this->textureButton);
				}
			}
		}
	}

	VertexArray GameOverState::setBackgroundGradient()
	{
		//Création d'un tableau de 4 vertex définissant un TriangleStrip
		VertexArray background(TriangleStrip, 4);

		//On définit la position des sommets du TriangleStrip
		background[0].position = Vector2f(0.f, 0.f);
		background[1].position = Vector2f(static_cast<float>(this->gameData->window.getSize().x), 0.f);
		background[2].position = Vector2f(0.f, static_cast<float>(this->gameData->window.getSize().y));
		background[3].position = Vector2f(static_cast<float>(this->gameData->window.getSize().x), static_cast<float>(this->gameData->window.getSize().y));

		//On définit la couleur des sommets du TriangleStrip
		background[0].color = Color(0, 216, 255);
		background[1].color = Color(255, 209, 148);
		background[2].color = Color(0, 216, 255);
		background[3].color = Color(255, 209, 148);

		//On retourne le fond
		return background;
	}

	void GameOverState::update(float dt)
	{
	}

	void GameOverState::draw(float dt)
	{
		this->gameData->window.clear();

		this->gameData->window.draw(setBackgroundGradient());

		//Afficher les boutons
		this->gameData->window.draw(this->spriteButtonQuit);

		//Afficher les textes
		this->gameData->window.draw(this->textQuit);
		this->gameData->window.draw(this->textGameOver);

		this->gameData->window.display();
	}
}