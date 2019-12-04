#include <SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<list>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "Game.h"
#include "Menu.h"

int main()
{
	/*Menu M;
	
	
	while (M.WindowMenu.isOpen())
	{
		M.WindowMenu.clear();
		M.WindowMenu.draw(M.Title);
		M.WindowMenu.draw(M.Start_L);
		M.WindowMenu.draw(M.Start_O);
		M.WindowMenu.draw(M.Exit);
		M.WindowMenu.display();
		sf::Event event;

		while (M.WindowMenu.pollEvent(event))
		{
			switch (event.type)
			{

			case sf::Event::KeyReleased:

				switch (event.key.code)
				{

				case sf::Keyboard::Up:
					M.SelecUp();
					break;

				case sf::Keyboard::Down:
					M.SelecDown();
					break;

				case sf::Keyboard::Return:

					switch (M.Index)
					{
					case 0:
					{
						M.WindowMenu.close();
						Game game;
						game.run();
						break;
					}
					case 1:
					{
						M.WindowMenu.close();
						Game game;
						game.run();
						break;
					}
					case 2:
						M.WindowMenu.close();
						break;
					}

					break;
				}
				break;
			}
		}
	}*/

	Game game;
	game.run();
	return 0;

}