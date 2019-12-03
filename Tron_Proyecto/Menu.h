
#pragma once
#include "SFML/Graphics.hpp"

class Menu
{
public:
	Menu();
	~Menu();

	void SelecUp();
	void SelecDown();

	sf::Texture mTexture;
	sf::Sprite mArrow;
	sf::RenderWindow mWindow;

	bool Index = true;
	sf::Font font;
	sf::Text Title;
	sf::Text Start;
	sf::Text Exit;

};
