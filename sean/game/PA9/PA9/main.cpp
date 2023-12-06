
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string.h>
#include "Textbox.h"
#include "Button.h"
#include "Background.h"
#include "playerCount.h"

int main() {
		sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;


	playerCount pC;






	std::cout << "Please select a networking type:\ns = Server mode\nc = Client mode\nn = Disable Networking\n*The only current networking is within the Menu.\n\nChoice: ";

	char connType;

	std::cin >> connType;
	if (connType == 's')
	{
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
	}
	else if (connType == 'c') 
	{ 
		socket.connect(ip, 2000);
	
	}
	else if (connType == 'n') 
	{
		std::cout << "Networking disabled" << std::endl;
	}

	pC.addPlayer();

	sf::Vector2f prevPov, p2Position;



	sf::RenderWindow window;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

	
	    // prepare the request
 //   sf::Http::Request request("/Players", sf::Http::Request::Get);
 //   sf::Http http("http://api.seanmh.net", 80);
	//sf::Http::Request nrequest("/nPlayer", sf::Http::Request::Get);
	//sf::Http nhttp("http://api.seanmh.net", 80);

	

//	sf::Http::Response nresponse = nhttp.sendRequest(nrequest);
//	std::cout << nresponse.getStatus() << std::endl << nresponse.getBody();

	window.create(sf::VideoMode(900, 900), "Battleship", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);


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


	window.setKeyRepeatEnabled(true);
	sf::Image icon;
	icon.loadFromFile("icon.png"); // File/Image/Pixel
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


	sf::Text TitleText;


	TitleText.setCharacterSize(48);
	TitleText.setFillColor(sf::Color::White);
	TitleText.setPosition({ 225, 100 });
	TitleText.setFont(font);
	TitleText.setString("Battleship");

	sf::Text playerCountText;
	std::string resp;
	std::string pCount;
	std::string ugh;



	playerCountText.setFont(font);

	playerCountText.setCharacterSize(20);
	playerCountText.setFillColor(sf::Color::White);
	playerCountText.setPosition({ 550, 850 });

	if (connType == 's' ||  connType == 'c'){socket.setBlocking(false);} // If client or server set blocking to false.


	bool update = true; // If window is not in focus, the keyboard inputs wont be taken.


	//Main Loop:
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

	

			//case sf::Event::TextEntered:
			//	text1.typedOn(Event);
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
					std::cout << "Play Pressed" << std::endl;
				}
				else if (btn2.isMouseOver(window)) {

					window.close();
				//	pC.minusPlayer();
				}
			

			
			}
		}
		prevPov = ship.getPosition();

		if (update)
		{


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				ship.move(2.0f, 0.0f);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				ship.move(-2.0f, 0.0f);

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




//		sf::Http::Response response = http.sendRequest(request);
		
		playerCountText.setString(pC.getPlayers());
	



		window.clear();
		//text1.drawTo(window);
     	window.draw(s);
		btn1.drawTo(window);
		btn2.drawTo(window);
		window.draw(playerCountText);
		window.draw(TitleText);
		window.draw(ship);

		if (connType == 'n') {

		}
		else {
			window.draw(shipTwo);
		}
		window.display();
	
	}

	pC.minusPlayer();

}

//
//#include <SFML/Graphics.hpp>
//#include <SFML/Network.hpp>
//#include <string>
//#include <iostream>
//
//int main()
//{
//	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
//	sf::TcpSocket socket;
//
//
//	
//
//	char connType;
//
//	std::cin >> connType;
//	sf::Packet p3;
//	if (connType == 's')
//	{
//		sf::TcpListener listener;
//		listener.listen(2000);
//		listener.accept(socket);
//	
//
//	
//	}
//	else { socket.connect(ip, 2000);
//	
//	}
//
//
//	
//	sf::RectangleShape rect1, rect2;
//
//	rect1.setSize(sf::Vector2f(20, 20));
//	rect2.setSize(sf::Vector2f(20, 20));
//	sf::RenderWindow window(sf::VideoMode(800, 600), "Packets");
//
//	sf::Vector2f prevPov, p2Position;
//	bool update = false;
//	
//	socket.setBlocking(false);
//	while (window.isOpen())
//	{
//		sf::Event Event;
//		while (window.pollEvent(Event))
//		{
//			if (Event.type == sf::Event::Closed || Event.key.code == sf::Keyboard::Escape)
//				window.close();
//
//			else if (Event.type == sf::Event::GainedFocus)
//				update = true;
//
//			else if (Event.type == sf::Event::LostFocus)
//				update = false;
//		}
//		prevPov = rect1.getPosition();
//
//		if (update)
//		{
//		
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//				rect1.move(0.2f, 0.0f);
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//				rect1.move(-0.2f, 0.0f);
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//				rect1.move(0.0f, 0.2f);
//
//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//				rect1.move(0.0f, -0.2f);
//		}
//		sf::Packet packet;
//		if (prevPov != rect1.getPosition())
//		{
//			packet << rect1.getPosition().x << rect1.getPosition().y;
//			socket.send(packet);
//		}
//		socket.receive(packet);
//
//		if (packet >> p2Position.x >> p2Position.y)
//		{
//			rect2.setPosition(p2Position);
//
//		}
//
//		window.draw(rect1);
//		window.draw(rect2);
//		
//		window.display();
//		window.clear();
//
//	}
//
//}

//#include <SFML/Network.hpp>
//#include <iostream>
//
//int main()
//{

//
//    return 0;
//}