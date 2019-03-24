#pragma once
#include <sstream>
#include "plateau.h"

#define NB_REGISTRE 8


class Instruction
{
public:
	virtual bool executer(plateau_t&) = 0; //Fonction exécutant l'instruction sur le plateau
	virtual std::string toString() = 0; //Donne le nom de l'instruction
	virtual std::string fulltoString() = 0; //Donne le nom de l'instruction, et la case affecté si il y en a une
	virtual Instruction* newInst(int& numInstr, int& cible) = 0; //Crée une instruction et la retourne
protected:
	int _numInstr = 0; //Numéro de l'instruction dans le code
};
