#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Pong", sf::Style::Titlebar | sf::Style::Close);
    sf::Event event;
    sf::RectangleShape paddle1(sf::Vector2f(20.f, 115.f));
    sf::RectangleShape paddle2(sf::Vector2f(20.f, 115.f));
    sf::RectangleShape button(sf::Vector2f(100.f, 50.f)), buttonExit(sf::Vector2f(100.f, 50.f));
    sf::CircleShape ball(5.f);
    float ballSpeedx = 0,ballSpeedy = 0;
    sf::Color softblack(24, 26, 24);
    sf::Font font;
    sf::Text mainText,buttonText,buttonExitText,winner,escForMainMenu;
    sf::Image icon;
    sf::SoundBuffer sb;
    sf::Sound pong;
    int sign[2] = {-1, 1};
    srand(time(NULL));
    bool gameStart = false,win = false;

    

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
    mainText.setPosition(320.f, 150.f);

    winner.setFont(font);
    winner.setCharacterSize(40);
    winner.setFillColor(sf::Color::Red);
    winner.setPosition(250.f, 200.f);

    escForMainMenu.setFont(font);
    escForMainMenu.setString("press esc to go back to the main menu");
    escForMainMenu.setCharacterSize(30);
    escForMainMenu.setFillColor(sf::Color::Red);
    escForMainMenu.setPosition(30.f, 300.f);

    buttonText.setFont(font);
    buttonText.setString("play");
    buttonText.setCharacterSize(30);
    buttonText.setFillColor(softblack);
    buttonText.setPosition(450.f, 375.f);
    buttonText.setLetterSpacing(0.3);

    button.setOutlineThickness(10.f);
    button.setOutlineColor(sf::Color(40,40,40));
    button.setFillColor(sf::Color::Red);
    button.setPosition(450.f, 370.f);

    buttonExit.setOutlineThickness(10.f);
    buttonExit.setOutlineColor(sf::Color(40, 40, 40));
    buttonExit.setFillColor(sf::Color::Red);
    buttonExit.setPosition(450.f, 450.f);

    buttonExitText.setFont(font);
    buttonExitText.setString("exit");
    buttonExitText.setCharacterSize(30);
    buttonExitText.setFillColor(softblack);
    buttonExitText.setPosition(450.f, 450.f);
    buttonExitText.setLetterSpacing(0.3);

    ball.setFillColor(sf::Color::Yellow);
    ball.setPosition(495.f, 395.f);

    sb.loadFromFile("../collision.wav");
    pong.setBuffer(sb);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {   //button press
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&& sf::Mouse::getPosition(window).x > 460.f &&
                sf::Mouse::getPosition(window).x < 540.f && sf::Mouse::getPosition(window).y > 380.f && sf::Mouse::getPosition(window).y < 410)
                gameStart = true;
            //close window
            if (event.type == sf::Event::Closed || sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Mouse::getPosition(window).x > 460.f &&
                sf::Mouse::getPosition(window).x < 540.f && sf::Mouse::getPosition(window).y > 460.f && sf::Mouse::getPosition(window).y < 490 && !gameStart && !win)
                window.close();
            //pause while playing pressing esc
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                gameStart = false;
                if (win) {
                    win = false;
                    ball.setPosition(495.f, 395.f);
                    ballSpeedx = 0;
                    ballSpeedy = 0;
                    paddle1.setPosition(50.f, 342.5);
                    paddle2.setPosition(930.f, 342.5);
                }
            }
        }
        if (gameStart) {
            //paddles movement(outside of event listener to avoid delay while pressing keys for longer)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && paddle1.getPosition().y < 685.f)
                paddle1.move(0.f, 10.f);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && paddle1.getPosition().y >= 10.f)
                paddle1.move(0.f, -10.f);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && paddle2.getPosition().y < 685.f)
                paddle2.move(0.f, 10.f);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && paddle2.getPosition().y >= 10.f)
                paddle2.move(0.f, -10.f);
        }
        //start moving the ball
        if (gameStart && ballSpeedx == 0) {
            //set horizontal speed
            ballSpeedx = sign[rand() % 2];
            //set vertical speed
            ballSpeedy = sign[rand() % 2];
        }
        else if (gameStart && ballSpeedx != 0) {
            //bounce when hitting top or bottom wall
            if (ball.getGlobalBounds().top <= 0 || ball.getGlobalBounds().top + ball.getGlobalBounds().height >= 800) {
                ballSpeedy = -ballSpeedy;
                pong.play();
            }
            else if (paddle1.getGlobalBounds().contains(ball.getPosition()) || paddle2.getGlobalBounds().contains(ball.getPosition())) {
                ballSpeedx = -ballSpeedx;
                ballSpeedy *= sign[rand() % 2];
                pong.play();
            }
            else if (ball.getGlobalBounds().left <= 0) {
                gameStart = false;
                win = true;
                winner.setString("Player 2 wins");
            }
            else if (ball.getGlobalBounds().left + ball.getGlobalBounds().width >= 1000) {
                gameStart = false;
                win = true;
                winner.setString("Player 1 wins");
            }

            ball.move(ballSpeedx, ballSpeedy);
            if (ballSpeedx < 0)
                ballSpeedx -= 0.01;
            else
                ballSpeedx += 0.01;
            if (ballSpeedy < 0)
                ballSpeedy -= 0.01;
            else
                ballSpeedy += 0.01;

        }

        //"pause" menu
        if (!gameStart && !win) {
            window.clear(softblack);
            window.draw(mainText);
            window.draw(button);
            window.draw(buttonText);
            window.draw(buttonExit);
            window.draw(buttonExitText);
            window.display();
        }
        else if (!winner.getString().isEmpty() && win) {
            //win screen
            window.clear(softblack);
            window.draw(winner);
            window.draw(escForMainMenu);
            window.display();
        }
        else {//game stage
            window.clear(softblack);
            window.draw(paddle1);
            window.draw(paddle2);
            window.draw(ball);
            window.display();
        }
    }

    return 0;
}