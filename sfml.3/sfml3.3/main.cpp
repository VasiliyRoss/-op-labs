#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Eye
{
    sf::ConvexShape eyeball;
    sf::CircleShape pupil;
    sf::Vector2f position;
};

void initEye(Eye &eye, sf::Vector2f &position);
sf::Vector2f toEuclidean(float radius, float angle);
float toDegrees(float radians);
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition);
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition);
void update(const sf::Vector2f &mousePosition, Eye &eye);
void redrawFrame(sf::RenderWindow &window, Eye &eyeL, Eye &eyeR);

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Eyes follow the mouse", sf::Style::Default, settings);

    Eye leftEye;
    Eye rightEye;

    sf::Vector2f mousePosition;

    sf::Vector2f leftEyePosition = {350, 300};
    sf::Vector2f rightEyePosition = {500, 300};

    initEye(leftEye, leftEyePosition);
    initEye(rightEye, rightEyePosition);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, leftEye);
        update(mousePosition, rightEye);
        redrawFrame(window, leftEye, rightEye);
    }
}

void initEye(Eye &eye, sf::Vector2f &position)
{
    constexpr int pointCount = 200;
    eye.position = position;
    const sf::Vector2f eyeRadius = {40.f, 80.f};
    eye.eyeball.setPosition(position);
    eye.eyeball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eye.eyeball.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = sf::Vector2f{
            eyeRadius.x * std::sin(angle),
            eyeRadius.y * std::cos(angle)};
        eye.eyeball.setPoint(pointNo, point);
    }

    eye.pupil.setRadius(10);
    eye.pupil.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    eye.pupil.setPosition(position);
}

// Переводит полярные координаты в декартовы
sf::Vector2f toEuclidean(float radius, float angle)
{
    return {
        radius * std::cos(angle),
        radius * std::sin(angle)};
}

float toDegrees(float radians)
{
    return float(double(radians) * 180 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x),
                     float(event.y)};
}

// Опрашивает и обрабатывает доступные события в цикле.
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

// Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, Eye &eye)
{
    const float radius = eye.pupil.getRadius();
    const sf::Vector2f initPosition = eye.position;
    sf::Vector2f position = {mousePosition.x - radius, mousePosition.y - radius};
    if (initPosition.x - position.x <= -15)
        position.x = initPosition.x + 15;
    else if (initPosition.x - position.x >= 20)
        position.x = initPosition.x - 20;
    if (initPosition.y - position.y <= -10)
        position.y = initPosition.y + 10;
    else if (initPosition.y - position.y >= 10)
        position.y = initPosition.y - 10;
    eye.pupil.setPosition(position);
}
// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Eye &eyeL, Eye &eyeR)
{
    window.clear();
    window.draw(eyeL.eyeball);
    window.draw(eyeR.eyeball);
    window.draw(eyeL.pupil);
    window.draw(eyeR.pupil);
    window.display();
}
