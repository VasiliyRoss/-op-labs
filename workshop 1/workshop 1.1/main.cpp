#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

struct Arrow
{
    sf::ConvexShape body;
    sf::Vector2f position;
};

void initArrow(Arrow &arrow, sf::Vector2f &position)
{
    arrow.body.setOutlineThickness(2);
    arrow.body.setPosition(position);
    arrow.body.setPointCount(7);
    arrow.body.setPoint(0, {-50, 50});
    arrow.body.setPoint(1, {0, 0});
    arrow.body.setPoint(2, {50, 50});
    arrow.body.setPoint(3, {25, 50});
    arrow.body.setPoint(4, {25, 100});
    arrow.body.setPoint(5, {-25, 100});
    arrow.body.setPoint(6, {-25, 50});
    arrow.body.setFillColor(sf::Color(0xFF, 0xFF, 0));
    arrow.body.setOutlineColor(sf::Color(0, 0, 0));
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

void redrawFrame(sf::RenderWindow &window, Arrow &arrow)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(arrow.body);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::Vector2f arrowPosition = {400, 300};

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Yellow Arrow", sf::Style::Default, settings);

    Arrow arrow;

    initArrow(arrow, arrowPosition);

    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, arrow);
    }
}