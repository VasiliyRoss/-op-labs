#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>

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

    delete[] setOfCircles; // Release allocated memory
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

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> speedDistribution(50.0f, 150.0f);

    for (int i = 0; i < NUBER_OF_BALLS; i++)
    {
        Circle ball;
        ball.shape.setRadius(BALL_SIZE);
        ball.shape.setPosition(startPositions[i]);
        ball.shape.setFillColor(circleColors[i]);
        ball.speed = {speedDistribution(gen), speedDistribution(gen)};
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

        // Проверка столкновений с границами окна и отскок
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

        for (int j = 0; j < NUBER_OF_BALLS; j++)
        {
            if (i != j)
            {
                sf::Vector2f otherPosition = setOfCircles[j].shape.getPosition();
                float distance = std::sqrt(std::pow(position.x - otherPosition.x, 2) + std::pow(position.y - otherPosition.y, 2));

                if (distance < 2 * BALL_SIZE)
                {
                    sf::Vector2f delta = position - otherPosition;
                    float angle = std::atan2(delta.y, delta.x);
                    speed = sf::Vector2f(std::cos(angle), std::sin(angle)) * std::sqrt(speed.x * speed.x + speed.y * speed.y);

                    float overlap = 2 * BALL_SIZE - distance;
                    position += 0.5f * overlap * sf::Vector2f(std::cos(angle), std::sin(angle));
                }
            }
        }

        setOfCircles[i].speed = speed;
        setOfCircles[i].shape.setPosition(position);
    }
}
