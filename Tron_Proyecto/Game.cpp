#include "Game.h"



Game::Game()
	: mWindow(sf::VideoMode(GameWith, GameHeigth), "TRON")
{
	//player 1
	Player1.P1.setSize(sf::Vector2f(5, 5));
	Player1.P1.setPosition(sf::Vector2f(GameWith / 2, 690));
	Player1.P1.setFillColor(sf::Color::Blue);
	Player1.mIsMovingUp = true;

	//player 2
	Player2.P2.setSize(sf::Vector2f(5, 5));
	Player2.P2.setPosition(sf::Vector2f(GameWith / 2, 20));
	Player2.P2.setFillColor(sf::Color::Red);
	Player2.mIsMovingDown = true;
}

void Game::run()
{
	sf::IpAddress IP=IP.getLocalAddress();
	sf::TcpSocket P1;
	sf::TcpSocket P2;
	P1.setBlocking(false);
	P2.setBlocking(false);

	std::cin >> Decision;

	for (int i = 0; i < Decision.size(); i++)
	{
		Decision[i] = tolower(Decision[i]);
	}

	if (Decision == "host")
	{
		sf::TcpListener server;
		server.listen(45000);
		server.accept(P1);
		server.accept(P2);
	}

	else if(Decision == "player")
	{
		P1.connect(IP,45000);
		P2.connect(IP, 45000);
	}

	sf::Vector2f PrePosition1 = Player1.P1.getPosition();
	sf::Vector2f PrePosition2 = Player2.P2.getPosition();
	sf::Vector2f Position1;
	sf::Vector2f Position2;

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			sf::Packet Pac1;
			sf::Packet Pac2;
			
			if (Decision == "player")
			{
				if (PrePosition2 != Player2.P2.getPosition())
				{
					Pac2 << Player2.P2.getPosition().x << Player2.P2.getPosition().y;
					P2.send(Pac2);
				}

				P1.receive(Pac1);
				if (Pac1 >> Position1.x >> Position1.y)
				{
					Player1.P1.setPosition(Position1);
				}
				PrePosition1 = Player1.P1.getPosition();
			}
			
			if (Decision == "host")
			{
				if (PrePosition1 != Player1.P1.getPosition())
				{
					Pac1 << Player1.P1.getPosition().x << Player1.P1.getPosition().y;
					P1.send(Pac1);
				}
				P2.receive(Pac2);

				if (Pac2 >> Position2.x >> Position2.y)
				{
					Player2.P2.setPosition(Position2);
				}
				PrePosition2 = Player2.P2.getPosition();
			}

			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}

}

void Game::update(sf::Time deltaTime)//falta arreglar coliciones
{
	if (Player1.mSpeed == 0 || Player2.mSpeed == 0)
	{
		GameOver();
	}
	IsColi(Player1.P1,Player1);
	IsColi(Player2.P2,Player2);
	//Px1 = Player1.P1.getPosition().x-1;
	//Py1 = Player1.P1.getPosition().y-1;

	//Px2 = Player2.P2.getPosition().x-1;
	//Py2 = Player2.P2.getPosition().y-1;

	////colisiones player 1 
	//	if (GameZone[Px1][Py1])
	//	{
	//		Player1.mSpeed = 0;
	//	}
	//	else
	//	{
	//		GameZone[Px1][Py1] = true;
	//	}
	//
	////colisiones player 2 
	//	if (GameZone[Px2][Py2])
	//	{
	//		Player2.mSpeed = 0;
	//	}
	//	else
	//	{
	//		GameZone[Px2][Py2] = true;
	//	}


	sf::Vector2f movement1(0.f, 0.f);
	sf::Vector2f movement2(0.f, 0.f);

	//colisiones contra las paredes player 1
	if (Player1.P1.getPosition().y < 0 || Player1.P1.getPosition().y > GameHeigth)
	{
		Player1.mSpeed = 0;
	}
	if (Player1.P1.getPosition().x < 0 || Player1.P1.getPosition().x > GameWith)
	{
		Player1.mSpeed = 0;
	}

	//colisiones contra las paredes player 2
	if (Player2.P2.getPosition().y < 0 || Player2.P2.getPosition().y > GameHeigth)
	{
		Player2.mSpeed = 0;
	}
	if (Player2.P2.getPosition().x < 0 || Player2.P2.getPosition().x > GameWith)
	{
		Player2.mSpeed = 0;
	}

	//movimiento player 1
	if (Decision == "host")
	{
		if (Player1.mIsMovingUp)
		{
			movement1.y -= Player1.mSpeed;
		}

		if (Player1.mIsMovingDown)
		{
			movement1.y += Player1.mSpeed;
		}

		if (Player1.mIsMovingLeft)
		{
			movement1.x -= Player1.mSpeed;
		}

		if (Player1.mIsMovingRight)
		{
			movement1.x += Player1.mSpeed;
		}
		Player1.P1.move(movement1 * deltaTime.asSeconds());
	}

	//movimiento player 2
	if (Decision == "player")
	{
		if (Player2.mIsMovingUp)
		{
			movement2.y -= Player2.mSpeed;
		}

		if (Player2.mIsMovingDown)
		{

			movement2.y += Player2.mSpeed;
		}

		if (Player2.mIsMovingLeft)
		{
			movement2.x -= Player2.mSpeed;
		}

		if (Player2.mIsMovingRight)
		{
			movement2.x += Player2.mSpeed;
		}

		Player2.P2.move(movement2 * deltaTime.asSeconds());
	}
	
} //arreglar colisiones   

void Game::render()
{
	//mWindow.clear();
	mWindow.draw(Player1.P1);
	mWindow.draw(Player2.P2);
	mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key)
{
	if (Decision == "host")
	{
		if (key == sf::Keyboard::W)
		{
			if (!Player1.mIsMovingDown)
			{
				Player1.mIsMovingUp = true;
				Player1.mIsMovingLeft = false;
				Player1.mIsMovingRight = false;
			}
		}

		else if (key == sf::Keyboard::S)
		{
			if (!Player1.mIsMovingUp)
			{
				Player1.mIsMovingDown = true;
				Player1.mIsMovingLeft = false;
				Player1.mIsMovingRight = false;
			}
		}

		else if (key == sf::Keyboard::A)
		{
			if (!Player1.mIsMovingRight)
			{
				Player1.mIsMovingLeft = true;
				Player1.mIsMovingDown = false;
				Player1.mIsMovingUp = false;
			}
		}

		else if (key == sf::Keyboard::D)
		{
			if (!Player1.mIsMovingLeft)
			{
				Player1.mIsMovingRight = true;
				Player1.mIsMovingDown = false;
				Player1.mIsMovingUp = false;
			}
		}
	}
	
	if (Decision == "player")
	{
		if (key == sf::Keyboard::Up)
		{
			if (!Player2.mIsMovingDown)
			{
				Player2.mIsMovingUp = true;
				Player2.mIsMovingLeft = false;
				Player2.mIsMovingRight = false;
			}
		}

		else if (key == sf::Keyboard::Down)
		{
			if (!Player2.mIsMovingUp)
			{
				Player2.mIsMovingDown = true;
				Player2.mIsMovingLeft = false;
				Player2.mIsMovingRight = false;
			}
		}

		else if (key == sf::Keyboard::Left)
		{
			if (!Player2.mIsMovingRight)
			{
				Player2.mIsMovingLeft = true;
				Player2.mIsMovingDown = false;
				Player2.mIsMovingUp = false;
			}
		}

		else if (key == sf::Keyboard::Right)
		{
			if (!Player2.mIsMovingLeft)
			{
				Player2.mIsMovingRight = true;
				Player2.mIsMovingDown = false;
				Player2.mIsMovingUp = false;
			}
		}
	}
	
}

void Game::GameOver() 
{
	sf::RenderWindow window(sf::VideoMode(300, 300), "Game Over");

	sf::Font fuente;

	// Intentamos cargarla
	
	if (!fuente.loadFromFile("Font/Real Brush.otf"))
	{
		//
	}

	// Creamos un objeto texto
	sf::Text texto;
	// Creamos un objeto String
	sf::String Frase;
	

	if (Player1.mSpeed == 0)
	{
		mWindow.close();
		Frase = "Jugador 2 Gano";
		texto.setString(Frase);
		texto.setFont(fuente);
		texto.setPosition(50, 50);
		texto.setCharacterSize(30);

		while (window.isOpen())
		{
			window.clear();
			window.draw(texto);
			window.display();
		}
	}

	else if (Player2.mSpeed == 0)
	{
		mWindow.close();
		Frase = "Jugador 1 Gano";
		texto.setString(Frase);
		texto.setFont(fuente);
		texto.setPosition(50, 50);
		texto.setCharacterSize(30);

		while (window.isOpen())
		{
			window.clear();
			window.draw(texto);
			window.display();
		};
	}
}

void Game::IsColi(sf::RectangleShape P, jugador PP)
{
	Px1 = P.getPosition().x;
	Py1 = P.getPosition().y;

	 if (GameZone[Px1][Py1])
	{
		PP.mSpeed = 0;
	
	}
	else
	{
		GameZone[Px1][Py1] = true;
	}
}

Game::~Game()
{
}
