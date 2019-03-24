#pragma once
#include "mouvement.h"


class Entree : public Mouvement
{
public:
	Entree(int& numInstr, int& cible){
		_cibleBox = cible;
		_numInstr = numInstr;
	}
	
	Entree* newInst(int& numInstr, int& cible){ return new Entree(numInstr, cible);}
	
	virtual bool executer(plateau_t& le_plateau){	//Place la première valeur de l'inbox dans le registre actif
		if(le_plateau.inputBox.empty()) return false;
		le_plateau.activeBox.first = true;
		le_plateau.activeBox.second = le_plateau.inputBox.front();
		le_plateau.inputBox.pop_front();
		return true;
	}
	
	virtual std::string toString() {return "ENTREE";}
	virtual std::string fulltoString(){
		std::stringstream ret;
			ret<<toString()<<std::endl;
		return ret.str();
	}
};