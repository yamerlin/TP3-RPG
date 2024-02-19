#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"


using namespace std;

int main() {
	cout << "Hello world";

	sf::Window window(sf::VideoMode(800, 600), "TP3 RPG");
    sf::Event event;

    //Faire tourner le programme tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        //Checker les events
        while (window.pollEvent(event))
        {
            //Si il y a un envent du type fermer la fenêtre alors on la ferme
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

	return 0;
}
