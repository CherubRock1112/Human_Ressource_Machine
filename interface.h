#pragma once
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <string>
#include "plateau.h"

enum Code_Aff {ERREUR, SUCCES, AUTRE}; //Code d'erreur pour créer un code couleur

class Interface
{
public :
	Interface(sf::RenderWindow&, tgui::Gui&);
	virtual ~Interface(){}
	sf::RenderWindow& _window;
	tgui::Gui& _gui;
	void display_textbox(plateau_t&);
	void display_instruction(std::string, int);
	void display_message(std::string, Code_Aff);
	void display_aide_inst(std::string msg);
	void afficher_aide();
	
	tgui::ChatBox::Ptr 	_registres [8], _inbox, _outbox, _reg_actif, _instr_courrante, _n_ligne, _consigne, _aide_instr;
	tgui::TextBox::Ptr _zone_code;
	tgui::Button::Ptr _but_compiler, _but_instr [11], _but_jouer;
	tgui::Canvas::Ptr _canvas_play, _canvas_stop, _canvas_step, _canvas_ff;
	tgui::ComboBox::Ptr _choix_lvl;
	
	bool jouerPressed; //Utile pour savoir quand le bouton "Jouer" a été utilisé
	
};