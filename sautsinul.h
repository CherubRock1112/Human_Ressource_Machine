#pragma once
#include "saut.h"


class SautSiNul : public Saut
{
public:
	SautSiNul(int& numInstr, int& val) : Saut(numInstr,val){}
	SautSiNul* newInst(int& numInstr, int& val){ return new SautSiNul(numInstr, val);}
	
	virtual bool executer(plateau_t& le_plateau){	//Fait un saut d'instruction si la valeur du registre actif est nulle
		if ((_valSaut + _numInstr) < -1){return false;} //Si on veut faire un saut en arrière dépassant les limites du code
		if(le_plateau.activeBox.first == false){ return false;}

		if(le_plateau.activeBox.second == 0){
			if (_valSaut < 0)	//Rajoute -1 d'offset si le saut est négatif pour avoir un jeu plus intuitif, dans Saut -n, n correspond maintenant au nombre d'instruction à sauter en arrière. Viens du faites que l'on incrémente instructionActive dès la sortie de cette fonction.
				le_plateau.instructionActive += (_valSaut-1);
			else
				le_plateau.instructionActive += _valSaut;
		}
		
		return true;
	}
	virtual std::string toString() {return "SAUTSINUL";}
	virtual std::string fulltoString(){
		std::stringstream ret;
		ret<<toString()<<" "<<_valSaut<<" "<<_numInstr<<std::endl;
		return ret.str();
	}
};