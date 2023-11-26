#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

void initArrow(sf::ConvexShape &arrow, sf::Vector2f &position);
void pollEvents(sf::RenderWindow &window);
void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &arrow);
sf::Vector2f toEuclidean(float radius, float angle);
float toDegrees(float radians);
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition);
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition);
void update(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, sf::Clock &clock);

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::Vector2f arrowPosition = {400, 300};

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Yellow Arrow is moving", sf::Style::Default, settings);

    sf::ConvexShape arrow;
    sf::Vector2f mousePosition;
    sf::Clock clock;

    initArrow(arrow, arrowPosition);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, arrow, clock);
        redrawFrame(window, arrow);
    }

    return 0;
}

void initArrow(sf::ConvexShape &arrow, sf::Vector2f &position)
{
    arrow.setOutlineThickness(2);
    arrow.setPosition(position);
    arrow.setPointCount(7);
    arrow.setPoint(0, {-50, 50});
    arrow.setPoint(1, {0, 0});
    arrow.setPoint(2, {50, 50});
    arrow.setPoint(3, {25, 50});
    arrow.setPoint(4, {25, 100});
    arrow.setPoint(5, {-25, 100});
    arrow.setPoint(6, {-25, 50});
    arrow.setFillColor(sf::Color(0xFF, 0xFF, 0));
    arrow.setOutlineColor(sf::Color(0, 0, 0));
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

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &arrow)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(arrow);
    window.display();
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x),
                     float(event.y)};
}

float toDegrees(float radians)
{
    return float(double(radians) * 180 / M_PI);
}

sf::Vector2f toEuclidean(float radius, float angle)
{
    return {
        radius * std::cos(angle),
        radius * std::sin(angle)};
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &shape, sf::Clock &clock)
{
    constexpr float movementSpeed = 200.f;
    constexpr float rotationSpeed = 90.f;
    const float deltaTime = clock.restart().asSeconds();
    const sf::Vector2f currentPosition = shape.getPosition();

    if (currentPosition != mousePosition)
    {
        const sf::Vector2f motion = mousePosition - currentPosition;
        const float vectorLength = std::sqrt(motion.x * motion.x + motion.y * motion.y);
        const sf::Vector2f direction = {
            motion.x / vectorLength,
            motion.y / vectorLength};
        const float distance = movementSpeed * deltaTime;
        shape.setPosition(currentPosition + direction * distance);
        float angle = toDegrees(atan2(motion.y, motion.x));
        const float currentAngle = shape.getRotation();
        if (angle < 0)
        {
            angle = 360 + angle;
        }
        if (angle != currentAngle)
        {
            float deltaAngle = angle - currentAngle;
            if (deltaAngle > 0 && deltaAngle < 180 || deltaAngle < -180)
            {
                shape.rotate(rotationSpeed * deltaTime);
            }
            else
            {
                shape.rotate(-(rotationSpeed * deltaTime));
            }
        }
    }
}
