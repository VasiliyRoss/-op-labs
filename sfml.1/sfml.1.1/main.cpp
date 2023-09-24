#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

void drawCircle(float x, float y, std::string color, sf::RenderWindow &window)
{
    sf::CircleShape shape(100);
    shape.setPosition({x, y});
    if (color == "red")
        shape.setFillColor(sf::Color(0xFF, 0x00, 0x0));
    else if (color == "yellow")
        shape.setFillColor(sf::Color(0xFF, 0xFB, 0x0));
    else if (color == "green")
        shape.setFillColor(sf::Color(0x00, 0xCF, 0x1C));

    window.draw(shape);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({300, 700}), "Traffic Light");

    window.clear();

    sf::RectangleShape trafficLight;
    trafficLight.setSize({270, 670});
    trafficLight.setPosition({15, 15});
    trafficLight.setFillColor(sf::Color(0x3D, 0x3D, 0x3D));
    window.draw(trafficLight);

    drawCircle(50, 30, "red", window);
    drawCircle(50, 250, "yellow", window);
    drawCircle(50, 470, "green", window);

    window.display();

    sf::sleep(sf::seconds(5));
    return 0;
}
