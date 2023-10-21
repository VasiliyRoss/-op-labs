#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

float toDegrees(float radians);
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition);
void init(sf::ConvexShape &pointer);
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition);
void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, sf::Clock &time);
void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer);

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Ponter follows mouse",
        sf::Style::Default, settings);

    sf::Vector2f mousePosition;
    sf::ConvexShape pointer;
    sf::Clock time;

    init(pointer);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, pointer, time);
        redrawFrame(window, pointer);
    }
}

float toDegrees(float radians)
{
    return float(double(radians) * 180 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse"
              << " x = " << event.x
              << ", y = " << event.y
              << std::endl;
    mousePosition = {float(event.x),
                     float(event.y)};
}

void init(sf::ConvexShape &pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, {40, 0});
    pointer.setPoint(1, {-20, -20});
    pointer.setPoint(2, {-20, 20});
    pointer.setPosition({400, 300});
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &pointer, sf::Clock &time)
{
    const sf::Vector2f delta = mousePosition - pointer.getPosition();
    float angle = toDegrees(atan2(delta.y, delta.x));
    const float dt = time.restart().asSeconds();
    const float rotationLimit = 15.f;
    const float rotationSpeed = rotationLimit * dt;

    if (angle < 0)
        angle = 360 + angle;

    const float currentAngle = pointer.getRotation();

    if (angle != currentAngle)
    {
        float deltaAngle = angle - currentAngle;
        if (deltaAngle > 0 && deltaAngle < 180 || deltaAngle < -180)
            pointer.rotate(rotationSpeed);
        else
            pointer.rotate(-rotationSpeed);
    }
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}