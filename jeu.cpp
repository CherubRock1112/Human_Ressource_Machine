#include "jeu.h"



Jeu::Jeu(niveau_t& lvl, Interface& inter) :  _inter (inter),  _lvl(lvl), _outboxSouhaite(lvl.outboxSouhaite)
{
	
	sf::Color color(255,215,0);
	_inter._gui.remove(_inter._but_compiler); //Lie le lancement de la compilation au bouton associé
	_inter._but_compiler->connect("pressed", [&](){ compilation(); });
	_inter._gui.add(_inter._but_compiler);
	
	_inter._gui.remove(_inter._canvas_play); //Lie le mode d'execution correpondant à leur bouton
	_inter._canvas_play->connect("clicked", [&](){ _mode = Marche;});
	_inter._gui.add(_inter._canvas_play);
	
	_inter._gui.remove(_inter._canvas_stop);
	_inter._canvas_stop->connect("clicked", [&](){ _mode = Stop;});
	_inter._gui.add(_inter._canvas_stop);
	
	_inter._gui.remove(_inter._canvas_ff);
	_inter._canvas_ff->connect("clicked", [&](){ _mode = Instant;});
	_inter._gui.add(_inter._canvas_ff);
	
	_inter._gui.remove(_inter._canvas_step);
	_inter._canvas_step->connect("clicked", [&](){ _mode = Pas;});
	_inter._gui.add(_inter._canvas_step);
	
	_inter._gui.remove(_inter._consigne); //Affiche la consigne asscoié au niveau
	_inter._consigne->addLine(_lvl.consigne, color);
	_inter._gui.add(_inter._consigne);
	
	init_registre(); //Initialise les registres du plateau
	_mode = Stop; //Mode d'execution sur Stop par défault
	_codeCompile = false;
}

void Jeu::init_registre() //Initialise les registres du plateau
{
	_lePlateau.activeBox.first = 0; //Tous les registres sont désactivés
	_lePlateau.instructionActive = 0;
	_lePlateau.inputBox.clear();
	_lePlateau.outputBox.clear();
	for (size_t i = 0; i < 8; i++)
		_lePlateau.memoryBox[i].first = 0;
	
	for (size_t i = 0; i < _lvl.inbox.size(); i++) //Rempli l'inbox avec celle fourni par le niveau
		_lePlateau.inputBox.push_back(_lvl.inbox[i]);
	
	_inter.display_textbox(_lePlateau); //L'affiche sur l'interface
}


bool Jeu::compilation_ligne(std::string ligne, int &nb_inst, Instruction* toutes_inst [N_INST]){ //Crée une instruction à partir d'une ligne de texte et l'ajoute au vecteur _lesInstructions 
	unsigned int n = 0;
	int val = -1;
	std::string temp_nom, temp_val;
	while (n < ligne.size() && ligne[n] != ' '){ //Récupère le nom de l'instruction
		temp_nom.push_back(ligne[n]);
		n++;
	}
	n++; //Passer l'espace
	while (n < ligne.size()){ //Récupère l'entier associé
		temp_val.push_back(ligne[n]);
		n++;
	}
	if(temp_val.size()){ //Si il y a un entier, sinon reste à -1
		for (size_t i = 0; i < temp_val.size(); i++){ //S'assure qu'on récupère uniquement des chiffres et des -/+
			if (((temp_val[i] < '0') or (temp_val[i] > '9')) and (temp_val[i] != '-') and (temp_val[i] != '+'))
				return 0;
		}
		val = std::stoi( temp_val ); //Converti le texte en entier
	}
	for (size_t j = 0; j < N_INST; j++){
		if (temp_nom == toutes_inst[j]->toString()){ //Cherche si le nom correspond à une instruction existante, la créee et l'ajoute au reste si c'est le cas
			_lesInstructions.push_back( toutes_inst[j]->newInst(nb_inst, val));
			nb_inst++;
			break;
		}
		if (j == N_INST - 1) //Si on ne trouve pas d'instruction correspondante
			return 0;
	}
	
	return 1;
}

void Jeu::compilation (){
	
	for (size_t i = 0; i< _lesInstructions.size(); i--){ //Vide le vecteur des instructions 
		delete _lesInstructions[_lesInstructions.size()-1-i];
		_lesInstructions.pop_back();
	}
	_lesInstructions.clear();
	
	std::string text = _inter._zone_code->getText();
	
	if(!text.size())
		_inter.display_message("Erreur, code vide!", ERREUR);
	
	std::string temp_nom, temp_val, temp;
	int nb_inst = 0, z = 0;
	size_t i = 0;
	Instruction** toutes_inst = new Instruction*[N_INST]; //Créer un tableau avec toutes les instructions possibles
	toutes_inst [0] = new Addition(z,z);
	toutes_inst [1]= new Soustraction(z,z);
	toutes_inst [2]= new Increment(z,z);
	toutes_inst [3]= new Decrement(z,z);
	toutes_inst [4]= new Saut(z,z);
	toutes_inst [5]= new SautSiNul(z,z);
	toutes_inst [6]= new SautSiNegatif(z,z);
	toutes_inst [7]= new Sauvegarde(z,z);
	toutes_inst [8]= new Charge(z,z);
	toutes_inst [9]= new Entree(z,z);
	toutes_inst [10]= new Sortie(z,z);
	
	while (i < text.size()){
		if (text[i] == '\n'){ //Changement de ligne, compile la ligne que l'on vient de terminer
				if (!compilation_ligne(temp, nb_inst, toutes_inst)){
					_inter.display_message(temp, ERREUR); //Si la ligne ne peut pas être compilé, affiche la ligne posant problème sur l'interface
					return; //Termine la compilation prématurément
				}
			
			temp.clear();	
		}else{ //Si ce n'est pas une fin de ligne, ajoute le caractère à la ligne en cours
			temp.push_back(text[i]);
		}
		i++;
	}
	
	if (text[text.size()-1] != '\n'){ //Compile la dernière ligne si le dernier caractère n'est pas un retour à la ligne
		if (!compilation_ligne(temp, nb_inst, toutes_inst)){
			_inter.display_message(temp, ERREUR);	
			return;
		}
	}
	delete [] toutes_inst;
	
	_inter.display_message("La compilation a reussie", SUCCES);
	init_registre();
	_codeCompile = true;
}


bool Jeu::exec_next_inst() //Execute une ligne
{  
	bool retour;

	if (_lePlateau.instructionActive < _lesInstructions.size()){	//Si le numéro de l'instruction executé est valide
		retour = _lesInstructions[_lePlateau.instructionActive]->executer(_lePlateau); //Execute l'instruction 
		
		if (_lePlateau.instructionActive > (int) _lesInstructions.size() - 1){
			_inter.display_message("ERREUR: SAUT HORS LIMITE", ERREUR);
		}else{
			if (retour){ //Affichage du plateau actualisé si l'instruction a bien été executé
				_inter.display_textbox(_lePlateau);
				if (_lePlateau.instructionActive == -1)
					_inter.display_message("Saut vers le debut", AUTRE);
				else
				_inter.display_instruction(_lesInstructions[_lePlateau.instructionActive]->fulltoString(), _lePlateau.instructionActive);
			
				_lePlateau.instructionActive++;
				
			}else{  //Affiche la ligne fautive en rouge si l'éxecution a retourné une erreur
				_inter.display_message(_lesInstructions[_lePlateau.instructionActive]->fulltoString(), ERREUR);
			}
			
			if (_lePlateau.inputBox.empty()){ //On teste si le code est bon dès que l'inbox est vide
				if(estGagne()){
					_inter.display_message("VICTOIRE", AUTRE);
					_mode = Stop;
					_codeCompile = false;
					return false;
				}
			}
		}
	}
	
	if (_lePlateau.instructionActive > (int) _lesInstructions.size() - 1){ //Code arrivé en fin d'execution ou sortant d'une erreur de saut de ligne
		_mode = Stop;
		_codeCompile = false;
		_lePlateau.instructionActive = 0;
		if(estGagne()){
			_inter.display_message("VICTOIRE", SUCCES);
		}else{
			_inter.display_message("ECHEC", AUTRE);
			init_registre();
		}
  		return false;
	}

	return retour;
}


void Jeu::execution()
{
	bool nobug = false;
	switch(_mode)
           	{ //Execute selon le mode choisi
           		case Stop: //Ne fait rien
					break;
            	case Marche: //Execute puis attend un certains temps
           			nobug = exec_next_inst();
           			for (size_t i = 0; i<500000000;i++); //TEMPO
					break;
            	case Pas: //Execute une seule instruction
           			nobug = exec_next_inst();
           			_mode = Stop;
					break;
            	case Instant: //Execute tout d'un coup jusqu'à arriver soit à une victoire soit à un echec
           			do
           			{
           				nobug = exec_next_inst();
           			} while(nobug);
					_mode = Stop;
					break;
				default:
					nobug = false;
           	}
}


bool Jeu::estGagne() //Regarde si la partie est gagnée
{
	if(_outboxSouhaite.size() != _lePlateau.outputBox.size())
		return false;

	for(size_t i = 0; i < _lePlateau.outputBox.size(); i++)
	{ //Compare le contenu de l'outbox et celle voulu par le niveau
		if(_lePlateau.outputBox[i] != _outboxSouhaite[i]) return false;
	}

	return true; //Retourne vrai si aucune différence detectée
}

void Jeu::operator=(niveau_t& lvl)
{ //Permet de changer de niveau, actualise les variables correspondantes, la consigne affichée et réinitialise les registres
	sf::Color color(255,215,0);
	_lvl = lvl;
	 _outboxSouhaite = _lvl.outboxSouhaite;
	_inter._gui.remove(_inter._consigne);
	_inter._consigne->removeAllLines();
	_inter._consigne->addLine("CONSIGNE", color);
	_inter._consigne->addLine(_lvl.consigne, color);
	_inter._gui.add(_inter._consigne);
	init_registre();
}
	
	