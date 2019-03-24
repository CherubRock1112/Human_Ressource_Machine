#pragma once
#include "mouvement.h"

class Charge : public Mouvement
{
public:
	Charge(int& numInstr, int& cible){
		_cibleBox = cible;
		_numInstr = numInstr;
	}
	
	Charge* newInst(int& numInstr, int& cible){ return new Charge(numInstr, cible);}
	
	virtual bool executer(plateau_t& le_plateau){	//Place la valeur du registre passif cible dans le registre actif
		if (_cibleBox < 0 or _cibleBox > NB_REGISTRE - 1) return false;	//Si le registre passif n'existe pas
		if (!le_plateau.memoryBox[_cibleBox].first) return false;	//Si il n'est pas activé
		
		le_plateau.activeBox.first = true;
		le_plateau.activeBox.second = le_plateau.memoryBox[_cibleBox].second;
		return true;
	}
	virtual std::string toString() {return "CHARGE";}
	virtual std::string fulltoString(){
		std::stringstream ret;
			ret<<toString()<<" "<<_cibleBox<<std::endl;
		return ret.str();
	}
};