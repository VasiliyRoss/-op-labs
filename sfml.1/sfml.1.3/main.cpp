#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 800;

sf::RectangleShape drawRectangle(float posX, float posY, float width, float height, float rotation)
{
    sf::RectangleShape shape;
    shape.setSize({width, height});
    shape.setRotation(rotation);
    shape.setPosition({posX, posY});

    return shape;
}

sf::CircleShape drawCircle(float posX, float posY, float radius)
{
    sf::CircleShape shape(radius);
    shape.setPosition({posX, posY});

    return shape;
}

sf::ConvexShape drawTrapeze(float posX, float posY)
{
    sf::ConvexShape trapeze;
    trapeze.setPosition({posX, posY});
    trapeze.setPointCount(4);
    trapeze.setPoint(0, {-200, 0});
    trapeze.setPoint(1, {+200, 0});
    trapeze.setPoint(2, {400, 200});
    trapeze.setPoint(3, {-400, 200});

    return trapeze;
}

void drawSmoke(float posX, float posY, int clouds, sf::RenderWindow &window)
{
    float radius = 20;
    for (int i = 0; i < clouds; i++)
    {
        sf::CircleShape cloud = drawCircle(posX, posY, radius);
        cloud.setFillColor(sf::Color(0xBF, 0xBF, 0xBF));
        window.draw(cloud);
        posX = posX + radius;
        posY = posY - radius;
        radius = radius + 5;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "The House");
    window.clear(sf::Color::White);

    sf::RectangleShape basement = drawRectangle(100, 460, 600, 300, 0);
    basement.setFillColor(sf::Color(0x4D, 0x2E, 0x0B));
    window.draw(basement);

    sf::RectangleShape door = drawRectangle(150, 560, 100, 200, 0);
    door.setFillColor(sf::Color(0x18, 0x17, 0x17));
    window.draw(door);

    sf::ConvexShape roof = drawTrapeze(400, 300);
    roof.setFillColor(sf::Color(0x5D, 0x1E, 0x17));
    window.draw(roof);

    drawSmoke(480, 205, 4, window);

    sf::ConvexShape stovepipe;
    stovepipe.setFillColor(sf::Color(0x3B, 0x38, 0x38));
    stovepipe.setPosition({500, 240});
    stovepipe.setPointCount(8);
    stovepipe.setPoint(0, {-50, 0});
    stovepipe.setPoint(1, {50, 0});
    stovepipe.setPoint(2, {50, 50});
    stovepipe.setPoint(3, {25, 50});
    stovepipe.setPoint(4, {25, 80});
    stovepipe.setPoint(5, {-25, 80});
    stovepipe.setPoint(6, {-25, 50});
    stovepipe.setPoint(7, {-50, 50});
    window.draw(stovepipe);

    window.display();

    sf::sleep(sf::seconds(3));
    return 0;
}
