#pragma once

#include <SFML/Graphics.hpp>
#include "jugador.h"
class Game
{
public:
	Game();
	~Game();
	void run();
private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key);
	void GameOver();
private:

	int GameWith = 800;
	int GameHeigth = 700;

	bool GameZone[800][700] = { false };

	sf::RenderWindow mWindow;
	
	jugador Player1;
	jugador Player2;
	
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
};
