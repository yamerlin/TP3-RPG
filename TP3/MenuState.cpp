#include "MenuState.h"
#include "GameState.h"

using namespace sf;

namespace TP3
{
	MenuState::MenuState(GameDataRef data) : gameData(data)
	{

	}

	void MenuState::init()
	{
		
	}

	void MenuState::handleInput()
	{
		sf::Event event;

		while (this->gameData->window.pollEvent(event))
		{
			if (Event::Closed == event.type)
			{
				this->gameData->window.close();
			}

			if (Event::MouseButtonReleased == event.type)
			{
				this->gameData->machine.addState(StateRef(new GameState(gameData)), true);
			}
		}
	}

	VertexArray MenuState::setBackgroundGradient() 
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

	void MenuState::update(float dt)
	{
	}

	void MenuState::draw(float dt)
	{
		this->gameData->window.clear();

		this->gameData->window.draw(setBackgroundGradient());

		this->gameData->window.display();
	}
}