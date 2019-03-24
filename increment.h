#pragma once
#include "operation.h"

class Increment : public Operation
{
public:
	Increment(int& numInstr, int& cible){
		_cibleBox = cible;
		_numInstr = numInstr;
	}
	Increment* newInst(int& numInstr, int& cible){ return new Increment(numInstr, cible);}
	
	virtual bool executer(plateau_t& le_plateau){	//Incrémente la valeur du registre actif
		if(le_plateau.activeBox.first == false) return false;

		le_plateau.activeBox.first = true;
		le_plateau.activeBox.second++;
		
		return true;
	}
	
	virtual std::string toString() {return "INCREMENT";}
	virtual std::string fulltoString(){
		std::stringstream ret;
			ret<<toString()<<std::endl;
		return ret.str();
	}
};