
#pragma once
#include "SFML/Graphics.hpp"

class Menu
{
public:
	Menu();
	~Menu();

	void SelecUp();
	void SelecDown();

	sf::RenderWindow WindowMenu;

	unsigned int Index = 0;
	sf::Font font;
	sf::Text Title;
	sf::Text Start_L;
	sf::Text Start_O;
	sf::Text Exit;

};
