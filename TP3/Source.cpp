#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "Personnage.h"


using namespace std;

int main() {
	cout << "TP3 RPG";

	sf::Window window(sf::VideoMode(800, 600), "TP3 RPG");
    sf::Event event;

    Personnage joueur(1,100,20,20);

    joueur.setType(0);

    cout << "\n" << joueur.getType() << endl;
    cout << "\n" << joueur.getPointDeVie() << endl;
    cout << "\n" << joueur.getPointAttaque() << endl;
    cout << "\n" << joueur.getPointDefense() << endl;


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
