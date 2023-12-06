#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>


class Background {
public:
	Background(sf::Texture t, float scaleX, float scaleY)
	{
		background.setTexture(t);
		background.setScale(scaleX, scaleY);
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(background);
	}

private:
	sf::Sprite background;

};