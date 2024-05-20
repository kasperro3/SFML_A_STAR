#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Board {
	int width;
	int height;
public:
	enum Type { Default, Wall, StartNode, EndNode };

	Board(int width, int height, sf::RenderWindow &target);
	void Mark(sf::Vector2<int> point, Type typ);
};