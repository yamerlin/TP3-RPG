#include <iostream>
#include <string>

#include "Personnage.h"
#include "Jeu.h"


using namespace std;
using namespace sf;

void menu() {
    cout << "TP3 RPG";
}

void jeu() {
    //Horloge et deltatime pour rendre le jeu independant du framerate
    Clock clock;
    float dt = clock.restart().asSeconds();

    //Créer le moteur de jeu
    Jeu jeu(clock, dt);

    //Boucle de jeu
    //Faire tourner le programme tant que la fenêtre est ouverte
    while (jeu.running())
    {
        jeu.update();

        jeu.render();
    }
}

int main() {

    menu();
    jeu();	

	return 0;
}
