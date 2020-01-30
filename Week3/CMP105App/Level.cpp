#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	circle.setFillColor(sf::Color::White);
	circle.setRadius(25);
	circle.setPosition(hwnd->getSize().x / 2, hwnd->getSize().y / 2);
	circle.setOrigin(25, 25);
	player = circle;
	velocityCircle = sf::Vector2f(150, 200);
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{

}

// Update game objects
void Level::update(float dt)
{
	if (circle.getPosition().x+circle.getRadius() > window->getSize().x)
	{
		circle.setPosition(window->getSize().x - circle.getRadius(), circle.getPosition().y);
		velocityCircle.x = -velocityCircle.x;
	}
	else if (circle.getPosition().x < circle.getRadius())
	{
		circle.setPosition(circle.getRadius(), circle.getPosition().y);
		velocityCircle.x = -velocityCircle.x;
	}
	if (circle.getPosition().y + circle.getRadius() > window->getSize().y)
	{
		circle.setPosition(circle.getPosition().x, window->getSize().y - circle.getRadius());
		velocityCircle.y = -velocityCircle.y;
	}
	else if (circle.getPosition().y < circle.getRadius())
	{
		circle.setPosition(circle.getPosition().x, circle.getRadius());
		velocityCircle.y = -velocityCircle.y;
	}

	circle.setPosition(circle.getPosition() + dt * velocityCircle);
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(circle);
	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}