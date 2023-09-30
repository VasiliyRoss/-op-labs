#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
#include <iostream>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr float BALL_SIZE = 40;
    float posX = 0;
    float speedX = 100.f;
    sf::Clock clock, clockX;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball");
    sf::Vector2f position = {0, 350};
    sf::CircleShape ball(BALL_SIZE);

    ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        constexpr float amplitudeY = 80.f;
        constexpr float periodY = 2;
        const float time = clock.getElapsedTime().asSeconds();
        const float wavePhase = time * float(2 * M_PI);
        const float posY = amplitudeY * std::sin(wavePhase / periodY);
        const float timeX = clockX.restart().asSeconds();

        if ((posX + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speedX > 0))
        {
            speedX = -speedX;
        }
        if ((posX < 0) && (speedX < 0))
        {
            speedX = -speedX;
        }

        posX += speedX * timeX;
        const sf::Vector2f offset = {posX, posY};

        ball.setPosition(position + offset);

        window.clear();
        window.draw(ball);
        window.display();
    }
}