#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

void drawRectangle(float posX, float posY, float height, float width, float rotation, const std::string &color, sf::RenderWindow &window)
{
    sf::RectangleShape shape;
    shape.setSize({width, height});
    shape.setRotation(rotation);
    shape.setPosition({posX, posY});
    if (color == "brown")
        shape.setFillColor(sf::Color(0xFF, 0x00, 0x0));
    else if (color == "black")
        shape.setFillColor(sf::Color(0x0, 0x0, 0x0));
    else if (color == "grey")
        shape.setFillColor(sf::Color(0x61, 0x0, 0x0));

    window.draw(shape);
}

void drawCircle(float posX, float posY, float radius, const std::string &color, sf::RenderWindow &window)
{
    sf::CircleShape shape(radius);
    shape.setPosition({posX, posY});
    if (color == "red")
        shape.setFillColor(sf::Color(0xFF, 0x00, 0x0));
    else if (color == "yellow")
        shape.setFillColor(sf::Color(0xFF, 0xFB, 0x0));
    else if (color == "green")
        shape.setFillColor(sf::Color(0x00, 0xCF, 0x1C));
    else if (color == "grey")
        shape.setFillColor(sf::Color(0xd0, 0xd0, 0xd0));

    window.draw(shape);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({600, 600}), "The House");

    window.clear(sf::Color::White);

    drawRectangle(10, 240, 300, 500, 0, "brown", window);

    window.display();

    sf::sleep(sf::seconds(5));
    return 0;
}
