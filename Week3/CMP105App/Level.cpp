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
	player.setPosition(100,100);
	velocityCircle = sf::Vector2f(150, 200);
	velocityPlayer = sf::Vector2f(0,0);
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	velocityPlayer = sf::Vector2f(0, 0);
	if (input->isKeyDown(sf::Keyboard::Left)) { velocityPlayer.x = -300; }
	else if (input->isKeyDown(sf::Keyboard::Right)) { velocityPlayer.x = 300; }
	if (input->isKeyDown(sf::Keyboard::Up)) { velocityPlayer.y = -300; }
	else if (input->isKeyDown(sf::Keyboard::Down)) { velocityPlayer.y = 300; }

	if (input->isKeyDown(sf::Keyboard::Q)) { velocityCircle = velocityCircle * (1.0f + 0.2f * dt); }
	if (input->isKeyDown(sf::Keyboard::E)) { velocityCircle = velocityCircle / (1.0f + 0.2f * dt); }
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
	player.setPosition(player.getPosition() + dt * velocityPlayer);
	sf::Vector2f playerRestrict = player.getPosition();
	if (playerRestrict.x + circle.getRadius() > window->getSize().x) { playerRestrict.x = window->getSize().x - circle.getRadius(); }
	else if (playerRestrict.x < circle.getRadius()) { playerRestrict.x = circle.getRadius(); }
	if (playerRestrict.y + circle.getRadius() > window->getSize().y) { playerRestrict.y = window->getSize().y - circle.getRadius(); }
	else if (playerRestrict.y < circle.getRadius()) { playerRestrict.y = circle.getRadius(); }
	player.setPosition(playerRestrict);
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(circle);
	window->draw(player);
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