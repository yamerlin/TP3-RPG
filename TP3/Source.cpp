#include <iostream>
#include <string>

#include "Personnage.h"
#include "Jeu.h"


using namespace std;
using namespace sf;

int main() {
	cout << "TP3 RPG";

	//Cr�er le moteur de jeu
    Jeu jeu;

    //Boucle de jeu
    //Faire tourner le programme tant que la fen�tre est ouverte
    while (jeu.running())
    {
        jeu.update();

        jeu.render();
    }

	return 0;
}
