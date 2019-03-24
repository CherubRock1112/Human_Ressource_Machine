#pragma once
#include "operation.h"

class Decrement : public Operation
{
public:
	Decrement(int& numInstr, int& cible){
		_cibleBox = cible;
		_numInstr = numInstr;
	}
	Decrement* newInst(int& numInstr, int& cible){ return new Decrement(numInstr, cible);}
	
	virtual bool executer(plateau_t& le_plateau){	//Décrémente la valeur du registre actif
		if(le_plateau.activeBox.first == false) return false;

		le_plateau.activeBox.first = true;
		le_plateau.activeBox.second--;

		return true;
	}
	
	virtual std::string toString() {return "DECREMENT";}
	virtual std::string fulltoString(){
		std::stringstream ret;
			ret<<toString()<<std::endl;
		return ret.str();
	}
};