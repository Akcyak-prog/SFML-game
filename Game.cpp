#include "Game.hpp"

const float Game::PlayerSpeed = 670.f; 
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f); //частота обновления игры

Game::Game() //логика игры
: mWindow(sf::VideoMode(640, 480), "SFML Application")
, mPlayer()
, mIsMovingDown(false)
, mIsMovingLeft(false)
, mIsMovingRight(false)
, mIsMovingUp(false)
{
    mPlayer.setRadius(40.f);
    mPlayer.setPosition(100.f,100.f);
    mPlayer.setFillColor(sf::Color::Cyan);
}

void Game::run() //запуск игры(игровой цикл)
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart(); //считаем время с последнего обновления
        while (timeSinceLastUpdate > TimePerFrame) //сравниваем с постоянным значением TimePerFrame ~ 16мс
        {
            timeSinceLastUpdate -= TimePerFrame; //убираем лишнее время вычитанием
            processEvents();
            update(TimePerFrame); //все это время обновляем по постоянному значению
        }
        render();
    }
}
void Game::processEvents() //принимает ввод игрока
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                handlePLayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePLayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
            default:
                break;
        }
    }
}
void Game::handlePLayerInput(sf::Keyboard::Key key, bool isPressed) //обработка движения на WASD
{
    if (key == sf::Keyboard::W)
        mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S)
        mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::A)
        mIsMovingLeft = isPressed;
    else if (key == sf::Keyboard::D)
        mIsMovingRight = isPressed;
}

void Game::update(sf::Time deltaTime) //обновляет игровые события и переменные(все что происходит в игре)
{
    sf::Vector2f movement (0.f, 0.f);
    if (mIsMovingUp)
        movement.y -= PlayerSpeed;
    if (mIsMovingDown)
        movement.y += PlayerSpeed;
    if (mIsMovingLeft)
        movement.x -= PlayerSpeed;
    if (mIsMovingRight)
        movement.x += PlayerSpeed;

    mPlayer.move(movement * deltaTime.asSeconds()); //просчитываем движение игрока
}

void Game::render() //рисует игру на экран
{
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}