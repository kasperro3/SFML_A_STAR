#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

class Board {
	int width;
	int height;
	sf::Vector2f cubeSize;
	sf::RenderWindow* target;
	std::vector<std::vector<sf::RectangleShape>> BoardArray;
public:
	enum Type { Default, Wall, StartNode, EndNode, Path };

	Board(int , int, sf::Vector2f, sf::RenderWindow*);
	void Mark(sf::Vector2<int>, Type);
	void Draw();
};