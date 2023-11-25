#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

void initSprite(sf::Sprite &sprite, sf::Texture &texture, sf::Vector2f &position)
{
    if (!texture.loadFromFile("assets/cat.png"))
    {
        std::cout << "Failed to load image" << std::endl;
        return;
    }

    sprite.setTexture(texture);
    sprite.setPosition(position);
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

void redrawFrame(sf::RenderWindow &window, sf::Sprite &sprite)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(sprite);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Kitty", sf::Style::Default, settings);

    sf::Sprite cat;
    sf::Texture texture;
    sf::Vector2f position = {400, 300};

    initSprite(cat, texture, position);

    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, cat);
    }
}