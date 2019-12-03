#include "Menu.h"



Menu::Menu() : mWindow(sf::VideoMode(500, 500), "MENU")
{


	font.loadFromFile("OpenSans-Bold.ttf");

	Title.setFont(font);
	Title.setFillColor(sf::Color::Blue);
	Title.setString("TRON MENU");
	Title.setPosition(sf::Vector2f(250, 10));

	Start.setFont(font);
	Start.setFillColor(sf::Color::Red);
	Start.setString("Start local");
	Start.setPosition(sf::Vector2f(250, 250));

	Exit.setFont(font);
	Exit.setFillColor(sf::Color::White);
	Exit.setString("Start online");
	Exit.setPosition(sf::Vector2f(250, 350));

}


Menu::~Menu()
{
}


void Menu::SelecUp()
{
	if (!Index)
	{
		mArrow.setPosition(150.f, 250.f);
		Index = true;
	}
}

void Menu::SelecDown()
{
	if (Index)
	{
		mArrow.setPosition(150.f, 350.f);
		Index = false;
	}
}