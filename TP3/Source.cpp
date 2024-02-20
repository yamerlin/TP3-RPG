#include <iostream>
#include <string>

#include "Personnage.h"
#include "Jeu.h"


using namespace std;
using namespace sf;

int main() {
	cout << "TP3 RPG";

	//Créer le moteur de jeu
    Jeu jeu;

    Personnage joueur(1,100,20,20);

    joueur.setType(0);

    cout << "\n" << joueur.getType() << endl;
    cout << "\n" << joueur.getPointDeVie() << endl;
    cout << "\n" << joueur.getPointAttaque() << endl;
    cout << "\n" << joueur.getPointDefense() << endl;

    //Boucle de jeu
    //Faire tourner le programme tant que la fenêtre est ouverte
    while (jeu.running())
    {
        jeu.update();

        jeu.render();
    }

	return 0;
}
