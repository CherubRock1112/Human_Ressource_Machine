#include "interface.h"
#define TAILLE_REG 100


sf::Color color(255,215,0);

Interface::Interface(sf::RenderWindow& window, tgui::Gui& gui) : _window(window), _gui(gui)
{
		jouerPressed = 0;
		gui.add(tgui::Picture::create("GUI/fond.jpg"));
		
		_choix_lvl = tgui::ComboBox::create(); //Liste de choix de niveaux
        _choix_lvl->setSize(400, 40);
        _choix_lvl->setPosition(30, 30);
        _choix_lvl->addItem("1 - Maximum");
        _choix_lvl->addItem("2 - Multiplication 1");
        _choix_lvl->addItem("3 - Minimum");
		_choix_lvl->addItem("4 - Multiplication 2");
		_choix_lvl->addItem("5 - Fibonacci");
        _choix_lvl->setSelectedItem("1 - Maximum");
        gui.add(_choix_lvl);
		
		_but_jouer = tgui::Button::create(); //Bouton Jouer
        _but_jouer->setPosition(500, 30);
        _but_jouer->setText("JOUER");
        _but_jouer->setSize(200, 40);
		_but_jouer->connect("pressed", [&](){ jouerPressed = 1; });
        _gui.add(_but_jouer);
		
		
		auto but_aide = tgui::Button::create();	//Bouton Aide, déclenche la création de la fenêtre d'aide
        but_aide->setPosition(350, 100);
        but_aide->setText("AIDE");
        but_aide->setSize(200, 50);
		but_aide->connect("pressed", [&](){ afficher_aide(); });
        _gui.add(but_aide);
		
		
        _inbox = tgui::ChatBox::create(); //Inbox
        _inbox->setSize(160, 450);
        _inbox->setTextSize(35);
        _inbox->setPosition(20, 200);
        _inbox->setLinesStartFromTop();
        _gui.add(_inbox);
		
		_outbox = tgui::ChatBox::create(); //Outbox
        _outbox->setSize(160, 450);
        _outbox->setTextSize(35);
        _outbox->setPosition(700, 200);
        _outbox->setLinesStartFromTop();
        _gui.add(_outbox);
		
		for (size_t i = 0; i < 8; i++){ //Registres passifs
			_registres[i] = tgui::ChatBox::create();
			_registres[i]->setSize(TAILLE_REG, TAILLE_REG);
			_registres[i]->setTextSize(45);
			_registres[i]->setPosition(170+65+((i%4)*TAILLE_REG), (650-2*TAILLE_REG) + ((i/4) * TAILLE_REG)); //170 fin de inbox, 65 d'écart
			_registres[i]->setLinesStartFromTop();
			char ch [1]= {'0' + i};
			_registres[i]->addLine(ch, color);
			_gui.add(_registres[i]);
		}
		
		_reg_actif = tgui::ChatBox::create(); //Registre actif
        _reg_actif->setSize(TAILLE_REG, TAILLE_REG);
        _reg_actif->setTextSize(50);
        _reg_actif->setPosition(390, 310);
        _reg_actif->setLinesStartFromTop();
        _gui.add(_reg_actif);
		
		_instr_courrante = tgui::ChatBox::create(); //Zone de texte pour l'instruction en cours d'execution
        _instr_courrante->setSize(300, 50);
        _instr_courrante->setTextSize(20);
        _instr_courrante->setPosition(400, 680);
        _instr_courrante->setLinesStartFromTop();
        _instr_courrante->addLine("INSTRUCTION COURRANTE", color);
        _gui.add(_instr_courrante);
		
		_n_ligne = tgui::ChatBox::create(); //Son numéro de ligne
        _n_ligne->setSize(50, 50);
        _n_ligne->setTextSize(25);
        _n_ligne->setPosition(750, 680);
        _n_ligne->setLinesStartFromTop();
        _n_ligne->addLine("N", color);
        _gui.add(_n_ligne);
		
		_consigne = tgui::ChatBox::create(); //La consigne
        _consigne->setSize(220, 155);
        _consigne->setPosition(1100, 15);
        _consigne->setLinesStartFromTop();
        _consigne->addLine("CONSIGNE", color);
        _gui.add(_consigne);
		
		_aide_instr = tgui::ChatBox::create(); //L'espace d'aide pour les instructions
        _aide_instr->setSize(220, 148);
        _aide_instr->setPosition(1100, 175);
        _aide_instr->setLinesStartFromTop();
        _aide_instr->addLine("AIDE INSTRUCTION", color);
        _gui.add(_aide_instr);
		
		_zone_code = tgui::TextBox::create(); //Zone de texte utilisateur
        _zone_code->setSize(420, 300);
        _zone_code->setTextSize(15);
        _zone_code->setPosition(900, 350);
        _zone_code->setText("CODE UTILISATEUR");
        _gui.add(_zone_code);
		
		
		std::string nom_inst []= {"ENTREE", "SORTIE", "ADDITION", "SOUSTRACTION", "INCREMENT", "DECREMENT", "SAUVEGARDE", "CHARGE", "SAUT", "SAUT SI = 0", "SAUT SI < 0"};
		for (size_t i = 0; i<11; i++){ //Boutons d'aide aux instructions
			_but_instr[i] = tgui::Button::create();
			_but_instr[i]->setPosition(900, 15+(i*28));
			_but_instr[i]->setText(nom_inst[i].c_str());
			_but_instr[i]->setSize(190, 28);
			switch (i){
				case 0: _but_instr[i]->connect("pressed", [&](){ display_aide_inst("Place le premier element de l'inbox dans le registre actif, utilisation: ENTREE"); }); break;
				case 1: _but_instr[i]->connect("pressed", [&](){ display_aide_inst("Place le contenu du registre active dans l'outbox, utilisation: SORTIE"); }); break;
				case 2: _but_instr[i]->connect("pressed", [&](){ display_aide_inst("Effectue l'addition de la valeur du registre actif avec la valeur du registre n, le registre actif prend la valeur du resultat, utilisation: ADDITION n"); }); break;
				case 3: _but_instr[i]->connect("pressed", [&](){ display_aide_inst("Effectue la soustraction de la valeur du registre actif avec la valeur du registre n, le registre actif prend la valeur du resultat, utilisation: ADDITION n"); }); break;
				case 4: _but_instr[i]->connect("pressed", [&](){ display_aide_inst("Ajoute 1 a la valeur du registre actif, utilisation: INCREMENT"); }); break;
				case 5: _but_instr[i]->connect("pressed", [&](){ display_aide_inst("Enleve 1 a la valeur du registre actif, utilisation : DECREMENT"); }); break;
				case 6: _but_instr[i]->connect("pressed", [&](){ display_aide_inst("Ecrase la valeur du registre n voulu par la valeur du registre actif, utilisation: SAUVEGARDE n"); }); break;
				case 7: _but_instr[i]->connect("pressed", [&](){ display_aide_inst("Le registre actif prend la valeur du registre n, utilisation: CHARGE n"); }); break;
				case 8: _but_instr[i]->connect("pressed", [&](){ display_aide_inst("Fait un saut de n instructions, vers l'avant (+) ou l'arriere (-), utilisation: SAUT n"); }); break;
				case 9: _but_instr[i]->connect("pressed", [&](){ display_aide_inst("Fait un saut de n instructions si la valeur du registre actif est 0, utilisation: SAUTSINUL n"); }); break;
				case 10: _but_instr[i]->connect("pressed", [&](){ display_aide_inst("Fait un saut de n instructions si la valeur du registre actif est negative, utilisation: SAUTSINEGATIF n"); }); break;
			}
			_gui.add(_but_instr[i]);
		}
	
		
        _but_compiler = tgui::Button::create();	//Bouton compiler
        _but_compiler->setPosition(1010, 680);
        _but_compiler->setText("COMPILER");
        _but_compiler->setSize(200, 50);
        _gui.add(_but_compiler);
		
		
        sf::Texture texture;			
        sf::Sprite  sprite;
		
        texture.loadFromFile("GUI/Play.png"); //Bouton marche
        sprite.setTexture(texture);
        sprite.setScale(1,1);
        _canvas_play = tgui::Canvas::create({50, 50});
        _canvas_play->setPosition(70, 680);
        _canvas_play->clear(sf::Color::Transparent);
        _canvas_play->draw(sprite);
        _canvas_play->display();
        _gui.add(_canvas_play);
		
		texture.loadFromFile("GUI/Stop.png"); //Bouton stop
        sprite.setTexture(texture);
        sprite.setScale(1,1);
        _canvas_stop = tgui::Canvas::create({50, 50});
        _canvas_stop->setPosition(140, 680);
        _canvas_stop->clear(sf::Color::Transparent);
        _canvas_stop->draw(sprite);
        _canvas_stop->display();
        _gui.add(_canvas_stop);
		
		texture.loadFromFile("GUI/Step.png"); //Bouton step
        sprite.setTexture(texture);
        sprite.setScale(1,1);
        _canvas_step = tgui::Canvas::create({50, 50});
        _canvas_step->setPosition(210, 680);
        _canvas_step->clear(sf::Color::Transparent);
        _canvas_step->draw(sprite);
        _canvas_step->display();
        _gui.add(_canvas_step);
		
		texture.loadFromFile("GUI/Fast_Forward.png"); //Bouton avance rapide
        sprite.setTexture(texture);
        sprite.setScale(1,1);
        _canvas_ff = tgui::Canvas::create({50, 50});
        _canvas_ff->setPosition(280, 680);
        _canvas_ff->clear(sf::Color::Transparent);
        _canvas_ff->draw(sprite);
        _canvas_ff->display();
        _gui.add(_canvas_ff);
		

}

void Interface::afficher_aide()	//Création d'une fenêtre affichant un texte d'aide à la compréhension du jeu
{
		auto _child_aide = tgui::ChildWindow::create();
        _child_aide->setSize(1000, 400);
        _child_aide->setPosition(100, 100);
        _child_aide->setTitle("Aide");
        _gui.add(_child_aide);

        auto label_aide = tgui::Label::create();
        label_aide->setText("Le but du jeu est de construire un code constitue des instructions decrites afin d'atteindre le but donne en haut a droite de l'interface.\n\nL'inbox est a gauche, les registres au milieu et l'outbox a droite.\n\nUne aide est disponible pour chaque instruction avec les boutons a droite de l'interface.\n\nPour choisir le niveau, choisissez parmi ceux de la liste et cliquez sur Jouer.\n\nUne fois votre code construit, cliquez sur Compiler, puis cliquez sur un des modes d'execution en bas a gauche pour executer votre code.\n\nLorsqu'une ligne est affichee en rouge pendant la compilation, la synthaxe de celle-ci pose probleme.\n\n Vous pouvez arreter l'execution a tout moment pour modifier votre code, une recompilation suffit.\n");
        label_aide->setPosition(30, 30);
        label_aide->setTextSize(14);
        _child_aide->add(label_aide);
		
		auto but_ok_aide = tgui::Button::create();
        but_ok_aide->setPosition(450, 300);
        but_ok_aide->setText("J'ai compris");
        but_ok_aide->setSize(100, 30);
        but_ok_aide->connect("pressed", [=](){ _child_aide->hide(); });
        _child_aide->add(but_ok_aide);
}


void Interface::display_aide_inst(std::string msg) //Affiche le texte d'aide d'une instruction dans la zone correspondante
{
	_gui.remove(_aide_instr);
	_aide_instr->removeAllLines();
	_aide_instr->addLine(msg, color);
	_gui.add(_aide_instr);
}

void Interface::display_textbox(plateau_t& le_plateau){ //Affiche les valeurs dans leurs registres correspondants
	
	if(le_plateau.activeBox.first){ //Si le registre actif est utlisé
		_gui.remove(_reg_actif);
		_reg_actif->removeAllLines();
		_reg_actif->addLine(std::to_string(le_plateau.activeBox.second), color); //Affiche son contenu
		_gui.add(_reg_actif);
	}
		
	
	for (size_t i = 0; i < 8; i++){ //Si les registres passifs sont actifs
		if(le_plateau.memoryBox[i].first){
			_gui.remove(_registres[i]);
			_registres[i]->removeAllLines();
			_registres[i]->addLine(std::to_string(le_plateau.memoryBox[i].second), color); //Affiche leur contenu
			_gui.add(_registres[i]);
		}else{
			_gui.remove(_registres[i]);
			_registres[i]->removeAllLines(); //Ou n'affiche rien
			_gui.add(_registres[i]);
		}
	}
	
	_gui.remove(_inbox);
	_inbox->removeAllLines(); //Affiche le contenu de l'inbox
	for (size_t i = 0; i < le_plateau.inputBox.size(); i++)
		_inbox->addLine(std::to_string(le_plateau.inputBox[i]), color);
	_gui.add(_inbox);
	
	
	_gui.remove(_outbox);
	_outbox->removeAllLines(); //Et de l'outbox
	for (size_t i = 0; i < le_plateau.outputBox.size(); i++)
		_outbox->addLine(std::to_string(le_plateau.outputBox[i]), color);
	_gui.add(_outbox);
}

void Interface::display_instruction(std::string msg, int nbLine) //Affiche l'instruction en cours d'execution dans les zones correspondantes
{
	_gui.remove(_n_ligne);
	_n_ligne->removeAllLines();
	_gui.remove(_instr_courrante);
	_instr_courrante->removeAllLines();
	_instr_courrante->addLine(msg);
	_n_ligne->addLine(std::to_string(nbLine));
	_gui.add(_instr_courrante);
	_gui.add(_n_ligne);
}

void Interface::display_message(std::string msg, Code_Aff code) //Affiche un message dans la zone normalement reservé à l'affichage des instructions
{
	_gui.remove(_n_ligne);
	_n_ligne->removeAllLines();
	_gui.remove(_instr_courrante);
	_instr_courrante->removeAllLines();
	if (code == ERREUR) //Si c'est un message d'erreur, l'affiche en rouge, etc...
		_instr_courrante->addLine(msg, sf::Color::Red);
	else if (code == SUCCES)
		_instr_courrante->addLine(msg, sf::Color::Green);
	else if (code == AUTRE)
		_instr_courrante->addLine(msg, sf::Color::Blue);
	_gui.add(_instr_courrante);
	_gui.add(_n_ligne);
}
	