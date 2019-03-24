#pragma once
#include "instruction.h"


class Operation : public Instruction //ABSTRAITE
{
public:
	virtual bool executer(plateau_t&) = 0;
	virtual std::string toString() = 0;
protected:
	int _cibleBox;	//Registre cible
};