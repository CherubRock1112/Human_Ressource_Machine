#include "interface.h"
#include "jeu.h"
#include "instruction.h"
#include <unistd.h>

niveau_t maximum = 
{
	{8, 77, 81, 94, 54, 53, 25, 32},
	{32,54,94,77},
	"Pour chaque 2 entrees, envoyer dans la sortie le plus grand element",
};

niveau_t mult1 = 
{
	{2, 8, 5, 3, 7, 9, 5, 9}, 
	{45,63,15,16},
	"Pour chaque 2 entrees, envoyer dans la sortie la multiplication des deux valeurs",
};

niveau_t minimum = 
{
	{15, 13, 10, -1, 25, 22, 13, 22, 18, 23, -1, 7, 11, -1, 4, 1, 22, 6, -1},
	{1,7,13,10},
	"Pour chaque chaine terminee par -1, renvoyer le plus petit element",
};

niveau_t mult2 = 
{
	{6, 8, 2},
	{80,320,240},
	"Pour chaque element, renvoyer la valeur de l'element multipliee par 40",
};

niveau_t fibonacci = 
{
	{23, 41},
	{34,21,13,8,5,3,2,1,1,0,21,13,8,5,3,2,1,1,0},
	"Pour chaque entree, envoyer tout les termes de la suite de Fibonnachi inferieur à la valeur de l'entree en partant de 0",
};


int main()
{
	sf::RenderWindow _window(sf::VideoMode(1366, 768), "TGUI window");
    _window.setFramerateLimit(60);

    tgui::Gui _gui(_window);
	Interface inter(_window, _gui);
	Jeu game(maximum,inter);
	

	 while (_window.isOpen())
    {
		
        sf::Event event;
		
		if(inter.jouerPressed){ //Si on change de niveau
			inter.jouerPressed = 0;
			switch (inter._choix_lvl->getSelectedItemIndex ())
			{
				case 0 : game = maximum; break;
				case 1 : game = mult1; break;
				case 2 : game = minimum; break;
				case 3 : game = mult2; break;
				case 4 : game = fibonacci; break;
			}
		}

        if(game.estCompile()) //Si le code a été compilé, lance la fonction d'execution (le mode est sur pause par défault)
        {
        	game.execution();
        } 

        while (_window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                _window.close();
            _gui.handleEvent(event);
        }
        _window.clear();
        _gui.draw();
        _window.display();
    }

    return EXIT_SUCCESS;
}
