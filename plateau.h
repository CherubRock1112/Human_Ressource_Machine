#pragma once
#include <utility>
#include <deque>
#include <vector>

#define SIZE_MEMORYBOX 8

typedef struct plateau
{
	int instructionActive;	//n° Instruction executé
	std::deque<int> inputBox; //Input en cours, deque car on traite uniquement avec le premier élément
	std::pair<bool, int> activeBox;	//Registre actif, si le bool est à 0 le registre n'est pas activé et ne peut pas être utilisé
	std::pair<bool, int> memoryBox[SIZE_MEMORYBOX]; //Les 8 registres passifs
	std::deque<int> outputBox;	//Outbox en cours
} plateau_t;

