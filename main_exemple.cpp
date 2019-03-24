#include <TGUI/TGUI.hpp>
#include <iostream>
#include <string>
#define TAILLE_REG 100

int main()
{
    sf::RenderWindow window(sf::VideoMode(1366, 768), "TGUI window");
    window.setFramerateLimit(60);

    tgui::Gui gui(window);

    try
	{
        auto chatbox_inbox = tgui::ChatBox::create();
        chatbox_inbox->setSize(160, 450);
        chatbox_inbox->setTextSize(20);
        chatbox_inbox->setPosition(20, 200);
        chatbox_inbox->setLinesStartFromTop();
        chatbox_inbox->addLine("INBOX", sf::Color::Yellow);
        gui.add(chatbox_inbox);
		
		auto chatbox_outbox = tgui::ChatBox::create();
        chatbox_outbox->setSize(160, 450);
        chatbox_outbox->setTextSize(20);
        chatbox_outbox->setPosition(700, 200);
        chatbox_outbox->setLinesStartFromTop();
        chatbox_outbox->addLine("OUTBOX", sf::Color::Yellow);
        gui.add(chatbox_outbox);
		
		tgui::ChatBox::Ptr 	registres [8];
		for (size_t i = 0; i < 8; i++){
			registres[i] = tgui::ChatBox::create();
			registres[i]->setSize(TAILLE_REG, TAILLE_REG);
			registres[i]->setTextSize(30);
			registres[i]->setPosition(170+65+((i%4)*TAILLE_REG), (650-2*TAILLE_REG) + ((i/4) * TAILLE_REG)); //170 fin de inbox, 65 d'écart
			registres[i]->setLinesStartFromTop();
			char ch [1]= {'0' + i};
			registres[i]->addLine(ch, sf::Color::Yellow);
			gui.add(registres[i]);
		}
		
		auto reg_actif = tgui::ChatBox::create();
        reg_actif->setSize(TAILLE_REG, TAILLE_REG);
        reg_actif->setTextSize(20);
        reg_actif->setPosition(390, 310);
        reg_actif->setLinesStartFromTop();
        reg_actif->addLine("JOUEUR", sf::Color::Yellow);
        gui.add(reg_actif);
		
		auto instr_courrante = tgui::ChatBox::create();
        instr_courrante->setSize(300, 50);
        instr_courrante->setTextSize(20);
        instr_courrante->setPosition(400, 680);
        instr_courrante->setLinesStartFromTop();
        instr_courrante->addLine("INSTRUCTION COURRANTE", sf::Color::Yellow);
        gui.add(instr_courrante);
		
		auto n_ligne = tgui::ChatBox::create();
        n_ligne->setSize(50, 50);
        n_ligne->setTextSize(25);
        n_ligne->setPosition(750, 680);
        n_ligne->setLinesStartFromTop();
        n_ligne->addLine("N", sf::Color::Yellow);
        gui.add(n_ligne);
		
		auto consigne = tgui::ChatBox::create();
        consigne->setSize(220, 155);
        consigne->setPosition(1100, 15);
        consigne->setLinesStartFromTop();
        consigne->addLine("CONSIGNE", sf::Color::Yellow);
        gui.add(consigne);
		
		auto aide_instr = tgui::ChatBox::create();
        aide_instr->setSize(220, 148);
        aide_instr->setPosition(1100, 175);
        aide_instr->setLinesStartFromTop();
        aide_instr->addLine("AIDE INSTRUCTION", sf::Color::Yellow);
        gui.add(aide_instr);
		
		auto zone_code = tgui::TextBox::create(); //ZONE DE TEXTE USER
        zone_code->setSize(420, 300);
        zone_code->setTextSize(15);
        zone_code->setPosition(900, 350);
        zone_code->setText("CODE UTILISATEUR");
        gui.add(zone_code);

		tgui::Button::Ptr but_instr [11];
		std::string nom_inst []= {"INBOX", "OUTBOX", "ADDITION", "SOUSTRACTION", "INCREMENT", "DECREMENT", "SAUVEGARDE", "CHARGEMENT", "SAUT", "SAUT SI = 0", "SAUT SI < 0"};
		for (size_t i = 0; i<11; i++){
			but_instr[i] = tgui::Button::create();
			but_instr[i]->setPosition(900, 15+(i*28));
			but_instr[i]->setText(nom_inst[i].c_str());
			but_instr[i]->setSize(190, 28);
			but_instr[i]->connect("pressed", [&](){ window.close(); });
			gui.add(but_instr[i]);
		}
		
        auto but_compiler = tgui::Button::create();	//COMPILER
        but_compiler->setPosition(1010, 680);
        but_compiler->setText("COMPILER");
        but_compiler->setSize(200, 50);
        but_compiler->connect("pressed", [&](){ window.close(); });
        gui.add(but_compiler);
		
        sf::Texture texture;			
        sf::Sprite  sprite;
        texture.loadFromFile("GUI/Play.png");
        sprite.setTexture(texture);
        sprite.setScale(1,1);

        auto canvas_play = tgui::Canvas::create({50, 50});
        canvas_play->setPosition(70, 680);
        canvas_play->clear();
        canvas_play->draw(sprite);
        canvas_play->display();
        gui.add(canvas_play);
		
		texture.loadFromFile("GUI/Stop.png");
        sprite.setTexture(texture);
        sprite.setScale(1,1);

        auto canvas_stop = tgui::Canvas::create({50, 50});
        canvas_stop->setPosition(140, 680);
        canvas_stop->clear();
        canvas_stop->draw(sprite);
        canvas_stop->display();
        gui.add(canvas_stop);
		
		texture.loadFromFile("GUI/Step.png");
        sprite.setTexture(texture);
        sprite.setScale(1,1);

        auto canvas_step = tgui::Canvas::create({50, 50});
        canvas_step->setPosition(210, 680);
        canvas_step->clear();
        canvas_step->draw(sprite);
        canvas_step->display();
        gui.add(canvas_step);
		
		texture.loadFromFile("GUI/Fast_Forward.png");
        sprite.setTexture(texture);
        sprite.setScale(1,1);

        auto canvas_ff = tgui::Canvas::create({50, 50});
        canvas_ff->setPosition(280, 680);
        canvas_ff->clear();
        canvas_ff->draw(sprite);
        canvas_ff->display();
        gui.add(canvas_ff);
		
	

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            gui.handleEvent(event);
        }

        window.clear();
        gui.draw();
        window.display();
    }

    return EXIT_SUCCESS;
}