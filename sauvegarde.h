#pragma once
#include "mouvement.h"

class Sauvegarde : public Mouvement
{
public:
	Sauvegarde(int& numInstr, int& cible){
		_cibleBox = cible;
		_numInstr = numInstr;
	}
	Sauvegarde* newInst(int& numInstr, int& cible){ return new Sauvegarde(numInstr, cible);}
	
	virtual bool executer(plateau_t& le_plateau){	//Place la valeur du registre actif dans un registre passif voulu
		if (!le_plateau.activeBox.first) return false;	//Si le registre actif n'est pas activé
		if (_cibleBox < 0 or _cibleBox > NB_REGISTRE - 1) return false;	//Si le registre passif n'existe pas
		
		le_plateau.memoryBox[_cibleBox].first = true;
		le_plateau.memoryBox[_cibleBox].second = le_plateau.activeBox.second;
		return true;
	}
	
	virtual std::string toString() {return "SAUVEGARDE";}
	virtual std::string fulltoString(){
		std::stringstream ret;
			ret<<toString()<<" "<<_cibleBox<<std::endl;
		return ret.str();
	}
};