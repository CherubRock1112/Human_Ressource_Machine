#pragma once
#include "instruction.h"

class Saut : public Instruction
{
public:
	Saut(int& numInstr, int& val){
		_valSaut = val;
		_numInstr = numInstr;
	}
	
	Saut* newInst(int& numInstr, int& val){ return new Saut(numInstr, val);}
	
	virtual bool executer(plateau_t& le_plateau){	
		if (_valSaut + _numInstr < -1) return false; //Si on veut faire un saut en arrière dépassant les limites du code
		if (_valSaut < 0)	//Rajoute -1 d'offset si le saut est négatif pour avoir un jeu plus intuitif, dans Saut -n, n correspond maintenant au nombre d'instruction à sauter en arrière. Viens du faites que l'on incrémente instructionActive dès la sortie de cette fonction.
			le_plateau.instructionActive += (_valSaut-1);
		else
			le_plateau.instructionActive += _valSaut;	//Actualise la valeur de l'instruction courrante
		
		return true;
	}
	
	virtual std::string toString() {return "SAUT";}
	virtual std::string fulltoString(){
		std::stringstream ret;
		ret<<toString()<<" "<<_valSaut<<" "<<_numInstr<<std::endl;
		return ret.str();
	}
protected:
	int _valSaut;
};