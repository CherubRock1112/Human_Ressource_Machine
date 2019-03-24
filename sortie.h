#pragma once
#include "mouvement.h"


class Sortie : public Mouvement
{
public:
	Sortie(int& numInstr, int& cible){
		_cibleBox = cible;
		_numInstr = numInstr;
	}
	
	Sortie* newInst(int& numInstr, int& cible){ return new Sortie(numInstr, cible);}
	
	virtual bool executer(plateau_t& le_plateau){
		if(!le_plateau.activeBox.first) return false;
		le_plateau.outputBox.push_front(le_plateau.activeBox.second); //Place la valeur du registre actif dans l'outbox
		return true;
	}
	
	virtual std::string toString() {return "SORTIE";}
	virtual std::string fulltoString(){
		std::stringstream ret;
			ret<<toString()<<std::endl;
		return ret.str();
	}
};