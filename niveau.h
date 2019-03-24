#pragma once
#include <deque>
#include <vector>

typedef struct niv //Structure décrivant un niveau
{
	std::deque<int> inbox;	//Inbox de départ
	std::vector<int> outboxSouhaite;	//Outbox que l'on doit obtenir pour gagner
	std::string consigne;
} niveau_t;

