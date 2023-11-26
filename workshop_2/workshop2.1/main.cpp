#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

constexpr float BALL_SIZE = 30;
constexpr int NUBER_OF_BALLS = 5;
constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

struct Circle
{
    sf::CircleShape shape;
    sf::Vector2f speed;
};

void redrawFrame(sf::RenderWindow &window, Circle *setOfCircles);
void updateMovingObject(Circle *setOfCircles, sf::Clock &clock);
void pollEvents(sf::RenderWindow &window);
void initSetOfCircles(Circle *setOfCircles);

int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Spheres", sf::Style::Default, settings);

    sf::Clock clock;
    Circle *setOfCircles = new Circle[NUBER_OF_BALLS];
    initSetOfCircles(setOfCircles);

    while (window.isOpen())
    {
        pollEvents(window);
        updateMovingObject(setOfCircles, clock);
        redrawFrame(window, setOfCircles);
    }
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, Circle *setOfCircles)
{
    window.clear();
    for (int i = 0; i < NUBER_OF_BALLS; i++)
    {
        window.draw(setOfCircles[i].shape);
    }
    window.display();
}

void initSetOfCircles(Circle *setOfCircles)
{

    const sf::Vector2f startPositions[NUBER_OF_BALLS] = {
        {50, 50},
        {190, 80},
        {350, 50},
        {75, 300},
        {300, 500}};

    const sf::Color circleColors[NUBER_OF_BALLS] = {
        {0xF2, 0x0, 0x0},
        {0xED, 0xFF, 0x0},
        {0x00, 0x8D, 0x0F},
        {0x02, 0x4e, 0x80},
        {0x78, 0x8d, 0x0}};

    const sf::Vector2f setOfSpeed[NUBER_OF_BALLS] = {
        {100.f, 0.f},
        {40.f, 20.f},
        {23.f, 11.f},
        {10.f, 23.f},
        {30.f, 45.f}};

    for (int i = 0; i < NUBER_OF_BALLS; i++)
    {
        Circle ball;
        ball.shape.setRadius(BALL_SIZE);
        ball.shape.setPosition(startPositions[i]);
        ball.shape.setFillColor(circleColors[i]);
        ball.speed = setOfSpeed[i];
        setOfCircles[i] = ball;
    }
}

void updateMovingObject(Circle *setOfCircles, sf::Clock &clock)
{
    const float dt = clock.restart().asSeconds();

    for (int i = 0; i < NUBER_OF_BALLS; i++)
    {

        sf::Vector2f position = setOfCircles[i].shape.getPosition();
        sf::Vector2f speed = setOfCircles[i].speed;

        position += speed * dt;

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed.x > 0))
        {
            speed.x = -speed.x;
        }
        if ((position.x < 0) && (speed.x < 0))
        {
            speed.x = -speed.x;
        }
        if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (speed.y > 0))
        {
            speed.y = -speed.y;
        }
        if ((position.y < 0) && (speed.y < 0))
        {
            speed.y = -speed.y;
        }

        setOfCircles[i].speed = speed;
        setOfCircles[i].shape.setPosition(position);
    }
}
