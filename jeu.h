#pragma once
#include <deque>
#include <vector>
#include <string>
#include <sstream>
#include <typeinfo>

#define N_INST 11

#include "instruction.h"
#include "interface.h"
#include "plateau.h"
#include "niveau.h"

#include "saut.h"
#include "sautsinul.h"
#include "sautsinegatif.h"

#include "addition.h"
#include "soustraction.h"
#include "increment.h"
#include "decrement.h"

#include "entree.h"
#include "sortie.h"
#include "sauvegarde.h"
#include "charge.h"

enum exec_mode {Stop, Marche, Pas, Instant}; //Mode d'execution du code

class Jeu
{
public:
	Jeu(niveau_t&, Interface&);
	void compilation ();
	bool compilation_ligne(std::string ligne, int &nb_inst, Instruction* toutes_inst [N_INST]);
	void init_registre();
	bool exec_next_inst();
	void execution();
	void lancerExec(); // à exécuter quand la compilation a réussie
	bool estCompile() {return _codeCompile;}
	bool estGagne();
	plateau_t _lePlateau;
	Interface& _inter;
	void operator=(niveau_t&); //Opérateur permettant d'affecter un nouveau niveau au Jeu
	
private:
	niveau_t _lvl;
	bool _codeCompile; //Permet de savoir si le code a été compilé
	std::vector<Instruction*> _lesInstructions;
	std::vector<int>& _outboxSouhaite;	//Outbox que l'on souhaite obtenir afin de réussir la partie
	exec_mode _mode;
};