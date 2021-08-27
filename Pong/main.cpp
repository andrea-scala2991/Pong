#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000,800), "Pong");
    window.setFramerateLimit(60);

    sf::Event event;
    sf::RectangleShape paddle1(sf::Vector2f(20.f,115.f));
    paddle1.setFillColor(sf::Color::Yellow);
    paddle1.setPosition(50.f, 50.f);

    while (window.isOpen())
    {
        
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddle1.getPosition().y < 685.f)
                paddle1.move(0.f,10.f);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle1.getPosition().y >= 10.f)
                    paddle1.move(0.f, -10.f);
        }

        window.clear();
        window.draw(paddle1);
        window.display();
    }

    return 0;
}