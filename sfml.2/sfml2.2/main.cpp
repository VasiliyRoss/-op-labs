#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr int pointCount = 200;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Polar Rose",
        sf::Style::Default, settings);
    sf::ConvexShape ellipse;
    ellipse.setFillColor(sf::Color(0xFF, 0x09, 0x80));

    ellipse.setPosition({400, 320});

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
        window.clear();
        window.draw(ellipse);
        window.display();
    }
}