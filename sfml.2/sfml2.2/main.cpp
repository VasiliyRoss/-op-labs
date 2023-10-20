#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    float speed = 100.f;

    sf::Clock clock;

    constexpr int pointCount = 200;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Polar Rose",
        sf::Style::Default, settings);
    sf::ConvexShape ellipse;
    ellipse.setFillColor(sf::Color(0xFF, 0x09, 0x80));

    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        float radius = 200 * std::sin(6 * angle);
        sf::Vector2f point = sf::Vector2f{
            radius * std::sin(angle),
            radius * std::cos(angle)};
        ellipse.setPoint(pointNo, point);
    }

    int i = 0;
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

        const float time = clock.getElapsedTime().asSeconds();
        const float centerX = 400;
        const float centerY = 320;
        const float orbiteRadius = 60;

        const float offsetX = centerX + (orbiteRadius * std::cos(time * speed * M_PI / 180));
        const float offsetY = centerY + (orbiteRadius * std::sin(time * speed * M_PI / 180));
        const sf::Vector2f offset = {offsetX, offsetY};

        ellipse.setPosition(offset);

        window.clear();
        window.draw(ellipse);
        window.display();
    }
}