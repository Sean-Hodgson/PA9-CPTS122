// Main.cpp
// Sean, Martin, Tomas, Vincent
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <time.h>
#include <string.h>
#include "Button.h"
#include "Background.h"
#include "playerCount.h"
#include "BattleshipGame.h"


int main() {
	srand((unsigned int)time(NULL));


	time_t start, end, end2; 
	time(&start);// start timer for playerCount
	sf::IpAddress ip = sf::IpAddress::getLocalAddress(); 
	sf::TcpSocket socket;
	playerCount pC;

	std::cout << "Please select a networking type:\ns = Server mode\nc = Client mode\nn = Disable Networking\n*The only current networking is within the Menu.\n\nChoice: ";

	char connType;

	std::cin >> connType;
	if (connType == 's') // init server
	{
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
	}
	else if (connType == 'c') // init client
	{ 
		socket.connect(ip, 2000);
	}
	else if (connType == 'n') //disable networking
	{
		std::cout << "Networking disabled" << std::endl;
	}

	pC.addPlayer(); // update playerCount
	sf::Vector2f prevPov, p2Position;



	sf::RenderWindow window, window2;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);
	window.create(sf::VideoMode(900, 900), "Battleship", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);

	// texture loading
	 sf::Texture t;
	t.loadFromFile("background.jpg");
	sf::Sprite s(t);
	 s.setScale(1, 1.1);



	sf::Texture ship1;
	ship1.loadFromFile("ship.png");
	sf::Sprite ship(ship1);
	ship.setScale(.25, .25);
	ship.setPosition(0, 750);


	sf::Texture ship2;
	ship2.loadFromFile("ship.png");
	sf::Sprite shipTwo(ship2);
	shipTwo.setScale(.25, .25);
	shipTwo.setPosition(0, 750);
	int ii = 0;

	window.setKeyRepeatEnabled(true);
	sf::Image icon;
	icon.loadFromFile("icon.png"); 
	window.setIcon(200, 200, icon.getPixelsPtr());

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		std::cout << "Font not found!\n";



	Button btn1("Play", { 200, 100 }, 30, sf::Color::Green, sf::Color::Black);
	btn1.setFont(font);
	btn1.setPosition({ 550, 300 });

	Button btn2("Exit", { 200, 100 }, 30, sf::Color::Green, sf::Color::Black);
	btn2.setFont(font);
	btn2.setPosition({ 150, 300 });

	// Battleship Text
	sf::Text TitleText;
	TitleText.setCharacterSize(48);
	TitleText.setFillColor(sf::Color::White);
	TitleText.setPosition({ 225, 100 });
	TitleText.setFont(font);
	TitleText.setString("Battleship");

	sf::Text playerCountText;



	playerCountText.setFont(font);

	playerCountText.setCharacterSize(20);
	playerCountText.setFillColor(sf::Color::White);
	playerCountText.setPosition({ 550, 850 });
	playerCountText.setString(pC.getPlayers());

	if (connType == 's' ||  connType == 'c'){socket.setBlocking(false);} // If client or server set blocking to false.


	bool update = true; // If window is not in focus, the keyboard inputs wont be taken.

	bool check = false;

	while (window.isOpen()) {

		sf::Event Event;
		
		//Event Loop:
		while (window.pollEvent(Event)) {

			switch (Event.type) {

			case sf::Event::GainedFocus:
				update = true;
				break;
			case sf::Event::LostFocus:
				update = false;
				break;

			case sf::Event::Closed:
			{
				window.close();
				
			}

			case sf::Event::MouseMoved:
				if (btn1.isMouseOver(window)) {
					btn1.setBackColor(sf::Color::Magenta);
				}
				else {
					btn1.setBackColor(sf::Color::Green);
				} 
				if (btn2.isMouseOver(window)) {
					btn2.setBackColor(sf::Color::Magenta);
				}
				else {
					btn2.setBackColor(sf::Color::Green);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (btn1.isMouseOver(window)) {
					window.close();

					BattleshipGame app;
					app.runApp();
				}
				else if (btn2.isMouseOver(window)) {

					window.close();
				}
			}
		}
		prevPov = ship.getPosition();

		if (update)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				ship.move(0.5f, 0.0f);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				ship.move(-0.5f, 0.0f);
		}

		if (connType == 'c' || connType == 's') {
			sf::Packet packet;
			if (prevPov != ship.getPosition())
			{
				packet << ship.getPosition().x << ship.getPosition().y;
				socket.send(packet);
			}

			socket.receive(packet);

			if (packet >> p2Position.x >> p2Position.y)
			{
				shipTwo.setPosition(p2Position);

			}
		}
	


		time(&end);
		double dif = difftime(end, start);
		if (int(dif) % 5 == 0)
		{

			if (check == false)
			{
				time(&end2);
				playerCountText.setString(pC.getPlayers());
				check = true;
			}
			
		}

		double dif2 = difftime(end2, end);
		if (int(dif2) % 10)
		{
			check = false;
		}

		


		window.clear();
     	window.draw(s);
		btn1.drawTo(window);
		btn2.drawTo(window);
		window.draw(playerCountText);
		window.draw(TitleText);
		window.draw(ship);

		if (connType == 's' || connType == 'c') 
		{
			window.draw(shipTwo);
		}
		window.display();
	
	}

	pC.minusPlayer();

}
