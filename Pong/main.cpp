#include <SFML/Graphics.hpp>
#include <windows.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000,800), "Pong");
    sf::Event event;
    sf::RectangleShape paddle1(sf::Vector2f(20.f,115.f));
    sf::RectangleShape paddle2(sf::Vector2f(20.f, 115.f));
    sf::RectangleShape button(sf::Vector2f(100.f,50.f));
    sf::CircleShape ball(5.f);
    sf::Color softblack(24, 26, 24);
    sf::Font font;
    sf::Text mainText,buttonText;
    sf::Image icon;

    bool gameStart = false;

    if (!icon.loadFromFile("../icon.png")) {
        MessageBox(NULL, (LPCWSTR)L"couldn't find window icon", NULL, MB_OK);
        return EXIT_FAILURE;
    }

    window.setFramerateLimit(60);
    window.setIcon(64, 57, icon.getPixelsPtr());

    paddle1.setFillColor(sf::Color::Yellow);
    paddle1.setPosition(50.f, 342.5);

    paddle2.setFillColor(sf::Color::Yellow);
    paddle2.setPosition(930.f, 342.5);

    if (!font.loadFromFile("../Akira Expanded Demo.ttf")) {
        MessageBox(NULL, (LPCWSTR)L"couldn't find font file", NULL, MB_OK);
        return EXIT_FAILURE;
    }
    mainText.setFont(font);
    mainText.setString("PONG");
    mainText.setCharacterSize(100);
    mainText.setFillColor(sf::Color::Red);
    mainText.setPosition(320.f,150.f);

    buttonText.setFont(font);
    buttonText.setString("play");
    buttonText.setCharacterSize(30);
    buttonText.setFillColor(softblack);
    buttonText.setPosition(450.f, 375.f);
    buttonText.setLetterSpacing(0.3);

    button.setOutlineThickness(10.f);
    button.setOutlineColor(sf::Color(40,40,40));
    button.setFillColor(sf::Color::Red);
    button.setPosition(450.f,370.f);

    ball.setFillColor(sf::Color::Yellow);
    ball.setPosition(495.f,395.f);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(window).x > 460.f &&
                sf::Mouse::getPosition(window).x < 540.f && sf::Mouse::getPosition(window).y > 380.f && sf::Mouse::getPosition(window).y < 410)
                gameStart = true;

            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                gameStart = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddle1.getPosition().y < 685.f)
                paddle1.move(0.f,10.f);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle1.getPosition().y >= 10.f)
                paddle1.move(0.f, -10.f);
        }
        //"pause" menu
        if (!gameStart) {
            window.clear(softblack);
            window.draw(mainText);
            window.draw(button);
            window.draw(buttonText);
            window.display();
        }
        else {//start the game
            window.clear(softblack);
            window.draw(paddle1);
            window.draw(paddle2);
            window.draw(ball);
            window.display();
        }
    }

    return 0;
}