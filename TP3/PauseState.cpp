#include "MenuState.h"
#include "GameState.h"

#include <iostream>
#include "PauseState.h"

using namespace sf;
using namespace std;

namespace TP3
{
	PauseState::PauseState(GameDataRef data) : gameData(data)
	{

	}

	void PauseState::init()
	{
		//Charger la texture des boutons
		if (!this->textureButton.loadFromFile("Textures/button.png")) {
			cout << "\nErreur chargement de la texture du monde\n";
		}
		if (!this->textureButtonOnHover.loadFromFile("Textures/buttonOnHover.png")) {
			cout << "\nErreur chargement de la texture du monde\n";
		}

		//Donner les textures des sprites
		this->spriteButtonPlay.setTexture(this->textureButton);
		this->spriteButtonSave.setTexture(this->textureButton);
		this->spriteButtonQuit.setTexture(this->textureButton);

		//Mettre l'origin au centre des boutons
		this->buttonOrigin = Vector2f((this->spriteButtonPlay.getLocalBounds().width)/2,(this->spriteButtonPlay.getLocalBounds().height)/2);
		this->spriteButtonPlay.setOrigin(buttonOrigin);
		this->spriteButtonSave.setOrigin(buttonOrigin);
		this->spriteButtonQuit.setOrigin(buttonOrigin);

		//Mettre les positions au centre de la fenetre
		this->buttonPosX = (this->gameData->window.getSize().x)/2;
		this->buttonPosY = (this->gameData->window.getSize().y)/2;

		//Positionner les boutons par rapport au centre de la fenêtre
		this->spriteButtonPlay.setPosition(buttonPosX, buttonPosY - 140);
		this->spriteButtonSave.setPosition(buttonPosX, buttonPosY);
		this->spriteButtonQuit.setPosition(buttonPosX, buttonPosY + 140);

		//Régler la taille des boutons
		this->buttonScaleX = 0.7;
		this->buttonScaleY = 0.5;
		this->spriteButtonPlay.setScale(buttonScaleX, buttonScaleY);
		this->spriteButtonSave.setScale(buttonScaleX, buttonScaleY);
		this->spriteButtonQuit.setScale(buttonScaleX, buttonScaleY);



		//Charger la police de text
		if (!font.loadFromFile("Textures/FontPixel.ttf"))
		{
			cout << "Erreur chargement police de texte";
		}
		textPlay.setFont(font);
		textSave.setFont(font);
		textQuit.setFont(font);
		textPauseMenu.setFont(font);

		//Setter les texts
		textPlay.setString("Return to game");
		textSave.setString("Save and quit");
		textQuit.setString("Quit");
		textPauseMenu.setString("Pause Menu");

		//Régler la taille des texts
		this->textSize = 27;
		textPlay.setCharacterSize(this->textSize);
		textSave.setCharacterSize(this->textSize);
		textQuit.setCharacterSize(this->textSize);
		textPauseMenu.setCharacterSize(60);

		//Mettre l'origin au centre des texts
		this->textPlay.setOrigin(Vector2f((this->textPlay.getLocalBounds().width) / 2, (this->textPlay.getLocalBounds().height) / 2));
		this->textSave.setOrigin(Vector2f((this->textSave.getLocalBounds().width) / 2, (this->textSave.getLocalBounds().height) / 2));
		this->textQuit.setOrigin(Vector2f((this->textQuit.getLocalBounds().width) / 2, (this->textQuit.getLocalBounds().height) / 2));
		this->textPauseMenu.setOrigin(Vector2f((this->textPauseMenu.getLocalBounds().width) / 2, (this->textPauseMenu.getLocalBounds().height) / 2));


		//Régler la couleurs des texts
		textPlay.setFillColor(Color(0, 216, 255));
		textSave.setFillColor(Color(0, 216, 255));
		textQuit.setFillColor(Color(0, 216, 255));
		textPauseMenu.setFillColor(Color(255, 215, 0));

		//Régler la position des texts
		textPlay.setPosition(this->spriteButtonPlay.getPosition().x, this->spriteButtonPlay.getPosition().y);
		textSave.setPosition(this->spriteButtonSave.getPosition().x, this->spriteButtonSave.getPosition().y);
		textQuit.setPosition(this->spriteButtonQuit.getPosition().x, this->spriteButtonQuit.getPosition().y);
		textPauseMenu.setPosition((this->gameData->window.getSize().x)/2, 35);
	}

	//Fonctions qui retourne le numéro du boutons sur lequel la souris se trouve
	int PauseState::checkIfMouseIsOverAButton(int posX, int posY)
	{
		//Retourne 0 -> Rien ou 1 -> Play ou 2 -> Load ou 3 -> Quit
		int button = 0;

		if (this->spriteButtonPlay.getGlobalBounds().contains(Vector2f(posX, posY)))
		{
			button = 1;
		}

		if (this->spriteButtonSave.getGlobalBounds().contains(Vector2f(posX, posY)))
		{
			button = 2;
		}

		if (this->spriteButtonQuit.getGlobalBounds().contains(Vector2f(posX, posY)))
		{
			button = 3;
		}

		return button;
	}

	void PauseState::handleInput()
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
					this->gameData->machine.removeState();
				}
			}

			//Clique sur les boutons
			if (Event::MouseButtonReleased == event.type)
			{
				int isMouseOverAButton = checkIfMouseIsOverAButton(Mouse::getPosition(gameData->window).x, Mouse::getPosition(gameData->window).y);

				//Retourner au jeu
				if (isMouseOverAButton == 1) {
					this->gameData->machine.removeState();
				}

				//Sauvegarder et quitter
				if (isMouseOverAButton == 2) {

				}

				//Quitter
				if (isMouseOverAButton == 3) {
					this->gameData->window.close();
				}
			}

			//Mettre un effet de surlignage des boutons quand on passe la souris dessus
			if (Event::MouseMoved == event.type)
			{
				int isMouseOverAButton = checkIfMouseIsOverAButton(Mouse::getPosition(gameData->window).x, Mouse::getPosition(gameData->window).y);
				
				if (isMouseOverAButton == 1) {
					this->spriteButtonPlay.setTexture(this->textureButtonOnHover);
				}
				else {
					this->spriteButtonPlay.setTexture(this->textureButton);
				}
				
				if (isMouseOverAButton == 2) {
					this->spriteButtonSave.setTexture(this->textureButtonOnHover);
				}
				else {
					this->spriteButtonSave.setTexture(this->textureButton);
				}
				
				if (isMouseOverAButton == 3) {
					this->spriteButtonQuit.setTexture(this->textureButtonOnHover);
				}
				else{
					this->spriteButtonQuit.setTexture(this->textureButton);
				}
			}
		}
	}

	VertexArray PauseState::setBackgroundGradient()
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
		background[1].color = Color(255,209,148);
		background[2].color = Color(0, 216, 255);
		background[3].color = Color(255, 209, 148);

		//On retourne le fond
		return background;
	}

	void PauseState::update(float dt)
	{
	}

	void PauseState::draw(float dt)
	{
		this->gameData->window.clear();

		this->gameData->window.draw(setBackgroundGradient());

		//Afficher les boutons
		this->gameData->window.draw(this->spriteButtonPlay);
		this->gameData->window.draw(this->spriteButtonSave);
		this->gameData->window.draw(this->spriteButtonQuit);

		//Afficher les textes
		this->gameData->window.draw(this->textPlay);
		this->gameData->window.draw(this->textSave);
		this->gameData->window.draw(this->textQuit);
		this->gameData->window.draw(this->textPauseMenu);

		this->gameData->window.display();
	}
}