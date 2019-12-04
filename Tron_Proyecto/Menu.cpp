#include "Menu.h"



Menu::Menu() : WindowMenu(sf::VideoMode(500, 500), "MENU")
{


	if (!font.loadFromFile("Font/Real Brush.otf"))
	{
		//
	}

	Title.setFont(font);
	Title.setFillColor(sf::Color::Blue);
	Title.setString("TRON MENU");
	Title.setPosition(sf::Vector2f(250, 10));

	Start_L.setFont(font);
	Start_L.setFillColor(sf::Color::Red);
	Start_L.setString("Start local");
	Start_L.setPosition(sf::Vector2f(250, 150));

	Start_O.setFont(font);
	Start_O.setFillColor(sf::Color::White);
	Start_O.setString("Start online");
	Start_O.setPosition(sf::Vector2f(250, 250));

	Exit.setFont(font);
	Exit.setFillColor(sf::Color::White);
	Exit.setString("Exit");
	Exit.setPosition(sf::Vector2f(250, 350));

}


Menu::~Menu()
{
}


void Menu::SelecUp()
{
	if (Index != 0)
	{
		Index--;
		if (Index == 0)
		{
			Start_L.setFillColor(sf::Color::Red);
			Start_O.setFillColor(sf::Color::White);
		}
		if (Index == 1)
		{
			Start_O.setFillColor(sf::Color::Red);
			Exit.setFillColor(sf::Color::White);
		}
	}
}

void Menu::SelecDown()
{
	if (Index != 2)
	{
		Index++;
		if (Index == 1)
		{
			Start_L.setFillColor(sf::Color::White);
			Start_O.setFillColor(sf::Color::Red);
		}
		if (Index == 2)
		{
			Start_O.setFillColor(sf::Color::White);
			Exit.setFillColor(sf::Color::Red);
		}
	}
}