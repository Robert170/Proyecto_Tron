#pragma once
#include <SFML/Graphics.hpp>

class jugador
{
public:
	jugador();
	jugador(sf::Vector2f Position, float Speed);
	~jugador();

	sf::RectangleShape P1;
	sf::RectangleShape P2;


	//Velocidad de jugador en flotante
	float mSpeed = 70;

	//Banderas para determinar hacia donde moverse
	bool mIsMovingUp = false;
	bool mIsMovingDown = false;
	bool mIsMovingLeft = false;
	bool mIsMovingRight = false;
};

