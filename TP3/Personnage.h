#pragma once
class Personnage
{
private:
	int type; //0 = player; 1 = allié; 2 = ennemies
	int pointDeVie;
	int pointAttaque;
	int pointDefense;

public:
	Personnage(int type, int nbPointDeVie, int nbPointAttaque, int nbPointDefense);

	void prendreDesDegats(int nbDegat);

	void setType(int type);
	void setPointDeVie(int nbPointDeVie);
	void setPointAttaque(int nbPointAttaque);
	void setPointDefense(int nbPointDefense);

	int getType();
	int getPointDeVie();
	int getPointAttaque();
	int getPointDefense();
};

