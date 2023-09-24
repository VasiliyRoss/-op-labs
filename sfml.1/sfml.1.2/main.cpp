#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

void drawRectangle(float posX, float posY, float height, float rotation, sf::RenderWindow &window)
{
    sf::RectangleShape shape;
    shape.setSize({height, 25});
    shape.setRotation(rotation);
    shape.setPosition({posX, posY});
    shape.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    window.draw(shape);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({550, 250}), "Name");

    window.clear();

    drawRectangle(100, 80, 100, 45, window);
    drawRectangle(222, 100, 75, 135, window);

    drawRectangle(300, 80, 100, 90, window);

    drawRectangle(380, 80, 100, 90, window);
    drawRectangle(360, 130, 80, -40, window);
    drawRectangle(380, 110, 80, 40, window);

    window.display();

    sf::sleep(sf::seconds(5));
    return 0;
}
