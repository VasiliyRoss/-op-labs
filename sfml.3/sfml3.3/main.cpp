#include <SFML/Graphics.hpp>
#include <cmath>

struct Pupil
{
    sf::CircleShape head;
    sf::RectangleShape stem;
    sf::Vector2f position;
    float rotation = 0;
};

struct Eye
{
    sf::ConvexShape eyeball;
    Pupil pupil;
    sf::Vector2f position;
};

void initEye(Eye &eye, sf::Vector2f &position);
void initPupil(Pupil &pupil, sf::Vector2f &position);
sf::Vector2f toEuclidean(float radius, float angle);
float toDegrees(float radians);
void updatePupil(Pupil &pupil);
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

    sf::Vector2f pupilPosition = {200, 300};
    initPupil(eye.pupil, position);
}

// Инициализирует фигуру-стрелку
void initPupil(Pupil &pupil, sf::Vector2f &position)
{
    pupil.position = position;

    pupil.head.setRadius(10);
    pupil.head.setFillColor(sf::Color(0x0, 0x0, 0x0));
    pupil.head.setOrigin({0, 10});

    pupil.stem.setSize({80, 20});
    pupil.stem.setOrigin({40, 10});
    pupil.stem.setFillColor(sf::Color(0x0, 0x0, 0x0));

    updatePupil(pupil);
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

// Обновляет позиции и повороты частей стрелки согласно текущему
// состоянию стрелки
void updatePupil(Pupil &pupil)
{
    const sf::Vector2f headOffset = toEuclidean(15, pupil.rotation);
    pupil.head.setPosition(pupil.position + headOffset);
    pupil.head.setRotation(toDegrees(pupil.rotation));

    const sf::Vector2f stemOffset = toEuclidean(-10, pupil.rotation);
    pupil.stem.setPosition(pupil.position);
    pupil.stem.setRotation(toDegrees(pupil.rotation));
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
    const sf::Vector2f delta = mousePosition - eye.pupil.position;
    eye.pupil.rotation = atan2(delta.y, delta.x);
    if (eye.pupil.position != mousePosition)
        updatePupil(eye.pupil);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Eye &eyeL, Eye &eyeR)
{
    window.clear();
    window.draw(eyeL.eyeball);
    window.draw(eyeR.eyeball);
    window.draw(eyeL.pupil.head);
    window.draw(eyeR.pupil.head);
    window.display();
}
