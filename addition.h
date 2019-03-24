#pragma once
#include "operation.h"

class Addition : public Operation
{
public:
	Addition(int& numInstr, int& cible){
		_cibleBox = cible;
		_numInstr = numInstr;
	}
	Addition* newInst(int& numInstr, int& cible){ return new Addition(numInstr, cible);}
	
	virtual bool executer(plateau_t& le_plateau){	//Fait l'addition de la valeur du registre actif avec celle du registre passif cible
		if(le_plateau.activeBox.first == false) return false;	//Si le registre actif n'est pas activé
		if (_cibleBox < 0 or _cibleBox > NB_REGISTRE - 1) return false;	//Si le registre n'existe pas
		if(le_plateau.memoryBox[_cibleBox].first == false) return false; 	//Si il n'est pas activé

		le_plateau.activeBox.first = true;
		le_plateau.activeBox.second += le_plateau.memoryBox[_cibleBox].second;

		return true;
	}
	
	virtual std::string toString() {return "ADDITION";}
	virtual std::string fulltoString(){
		std::stringstream ret;
			ret<<toString()<<" "<<_cibleBox<<std::endl;
		return ret.str();
	}
};