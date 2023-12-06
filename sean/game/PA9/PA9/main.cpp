//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <iostream>
//
//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(700, 500), "SFML works!");
//    sf::CircleShape shape(100.f);
//    sf::RectangleShape rectangle(sf::Vector2f(120, 50));
//    shape.setFillColor(sf::Color::Green);
//
//    sf::Texture menuChar;
//    menuChar.loadFromFile("Dude_Monster_Idle_4.png");
//
//    sf::IntRect rectSourceSprite(32, 0, 32, 32);
//    sf::Sprite sprite(menuChar, rectSourceSprite);
//    sprite.setScale(10, 10);
//
//
//
//    //sf::Texture menuChar2;
//    //menuChar2.loadFromFile("Shot_1.png");
//
//    //sf::IntRect rect2SourceSprite(116, 0, 116, 128);
//    //sf::Sprite sprite2(menuChar2, rect2SourceSprite);
//
//    //
//    //sf::Listener list;
//
//    //list.setDirection(10.f, 0.f, 0.f);
//    //list.setPosition(10.f, 0.f, 5.f);
//    
//    //sf::Sound music;
//    //sf::SoundBuffer buffer;
//    //buffer.loadFromFile("TownTheme.mp3");
//    //music.setBuffer(buffer);
//
//    //music.setMinDistance(5.f);
//    //music.setAttenuation(10.f);
//
//    //music.play();
//
//    int startMenu = 1;
//
//    while (window.isOpen())
//    {
//       
//        
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//
//            while (startMenu == 1)
//            {
//
//            }
//          /*  music.setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y, -5.f);*/
//
//
//            if (rectSourceSprite.left == 64)
//                rectSourceSprite.left = 0;
//            else
//                rectSourceSprite.left += 32;
//
//            sprite.setTextureRect(rectSourceSprite);
//
//
//            //if (rect2SourceSprite.left == 232)
//            //    rect2SourceSprite.left = 0;
//            //else
//            //    rect2SourceSprite.left += 116;
//           
//
//            //sprite2.setTextureRect(rect2SourceSprite);
//
//            std::cout << "X:" << shape.getPosition().x << ", Y:" << shape.getPosition().y << std::endl;
//
//            if (startMenu == 0)
//            {
//
//                if (shape.getPosition().y != 0)
//                {
//                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//                    {
//                        shape.move(0, -20);
//
//
//
//                    }
//                }
//
//                if (shape.getPosition().y != 300)
//                {
//                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//                    {
//                        shape.move(0, 20);
//                    }
//                }
//
//                if (shape.getPosition().x != 0)
//                {
//                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//                    {
//                        shape.move(-20, 0);
//                    }
//                }
//
//
//                if (shape.getPosition().x != 500)
//                {
//                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//                    {
//                        shape.move(20, 0);
//                    }
//                }
//
//            }
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
//            {
//                startMenu = 0;
//            }
//
//
//
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//
//        if (startMenu == 0)
//        {
//            window.draw(shape);
//        }
//        else {
//        
//        }
//   
//        window.display();
//    }
//
//    return 0;
//}
//
//
//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include "Textbox.h"
//#include "Button.h"
//
//int main() {
//	sf::RenderWindow window;
//
//	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);
//
//	window.create(sf::VideoMode(900, 900), "SFML Textbox", sf::Style::Titlebar | sf::Style::Close);
//	window.setPosition(centerWindow);
//
//	window.setKeyRepeatEnabled(true);
//
//	sf::Font font;
//	if (!font.loadFromFile("arial.ttf"))
//		std::cout << "Font not found!\n";
//
//	Textbox text1(20, sf::Color::White, true);
//	text1.setPosition({ 100, 100 });
//	text1.setLimit(true, 30);
//	text1.setFont(font);
//
//	Button btn1("Enter", { 200, 100 }, 30, sf::Color::Green, sf::Color::Black);
//	btn1.setFont(font);
//	btn1.setPosition({ 100, 300 });
//
//	Button btn2("Exit", { 200, 100 }, 30, sf::Color::Green, sf::Color::Black);
//	btn2.setFont(font);
//	btn2.setPosition({ 100, 600 });
//
//	//Main Loop:
//	while (window.isOpen()) {
//
//		sf::Event Event;
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
//			text1.setSelected(true);
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
//			text1.setSelected(false);
//		}
//
//		//Event Loop:
//		while (window.pollEvent(Event)) {
//			switch (Event.type) {
//
//			case sf::Event::Closed:
//				window.close();
//			case sf::Event::TextEntered:
//				text1.typedOn(Event);
//			case sf::Event::MouseMoved:
//				if (btn1.isMouseOver(window)) {
//					btn1.setBackColor(sf::Color::Magenta);
//				}
//				else {
//					btn1.setBackColor(sf::Color::Green);
//				}
//				break;
//			case sf::Event::MouseButtonPressed:
//				if (btn1.isMouseOver(window)) {
//					std::cout << "Hello " << text1.getText() << "\n";
//				}
//				else if (btn2.isMouseOver(window)) {
//					window.close();
//				}
//			}
//		}
//		window.clear();
//		text1.drawTo(window);
//		btn1.drawTo(window);
//		btn2.drawTo(window);
//		window.display();
//	}
//}


#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <iostream>

int main()
{
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;


	char connType;

	std::cin >> connType;
	sf::Packet p3;
	if (connType == 's')
	{
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
	

	
	}
	else { socket.connect(ip, 2000);
	
	}


	
	sf::RectangleShape rect1, rect2;

	rect1.setSize(sf::Vector2f(20, 20));
	rect2.setSize(sf::Vector2f(20, 20));
	sf::RenderWindow window(sf::VideoMode(800, 600), "Packets");

	sf::Vector2f prevPov, p2Position;
	bool update = false;
	
	socket.setBlocking(false);
	while (window.isOpen())
	{
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed || Event.key.code == sf::Keyboard::Escape)
				window.close();

			else if (Event.type == sf::Event::GainedFocus)
				update = true;

			else if (Event.type == sf::Event::LostFocus)
				update = false;
		}
		prevPov = rect1.getPosition();

		if (update)
		{
		

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				rect1.move(0.2f, 0.0f);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				rect1.move(-0.2f, 0.0f);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				rect1.move(0.0f, 0.2f);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				rect1.move(0.0f, -0.2f);
		}
		sf::Packet packet;
		if (prevPov != rect1.getPosition())
		{
			packet << rect1.getPosition().x << rect1.getPosition().y;
			socket.send(packet);
		}
		socket.receive(packet);

		if (packet >> p2Position.x >> p2Position.y)
		{
			rect2.setPosition(p2Position);

		}

		window.draw(rect1);
		window.draw(rect2);
		
		window.display();
		window.clear();

	}

}