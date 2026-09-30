#include "Game.hpp"

const float Game::PlayerSpeed = 100.f; 
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f); //частота обновления игры

Game::Game() //логика игры
: mWindow(sf::VideoMode(640, 480), "SFML Application")
, mTexture()
, mPlayer()
, mFont()
, mTextFps()
, mTextRenderedFrames()
, mIsResetingStats(false)
, mIsMovingDown(false)
, mIsMovingLeft(false)
, mIsMovingRight(false)
, mIsMovingUp(false)
{
    mWindow.setFramerateLimit(240);

    if(!mTexture.loadFromFile("/home/akcyak/Documents/Eagle.png"))
    {
        // Ловим ошибки загрузки текстуры
    }
    mPlayer.setTexture(mTexture);
    mPlayer.setPosition(100.f,100.f);

    if(!mFont.loadFromFile("/home/akcyak/Documents/Sansation.ttf"))
    {
        // Ловим ошибку загрузки шрифта
    }
    mTextFps.setFont(mFont);
    mTextFps.setPosition(5.f,5.f);
    mTextFps.setCharacterSize(14);
    mTextFps.setString("FPS: 0");


    mTextRenderedFrames.setFont(mFont);
    mTextRenderedFrames.setPosition(5.f,25.f);
    mTextRenderedFrames.setCharacterSize(14);
    mTextRenderedFrames.setString("OVERALL FRAMES: 0");

}

void Game::run() //запуск игры(игровой цикл)
{
    sf::Clock renderedFramesClock;
    int framesRendered = 0;

    sf::Clock FpsClock;
    int frameCount = 0;

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        processEvents();
        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime; //считаем время с последнего обновления
        while (timeSinceLastUpdate > TimePerFrame) //сравниваем с постоянным значением TimePerFrame ~ 16мс
        {
            timeSinceLastUpdate -= TimePerFrame; //убираем лишнее время вычитанием
            update(TimePerFrame); //все это время обновляем по постоянному значению

            
        }

        ++frameCount; // увеличиваем количество прошедших кадров, т.е. итераций
        if(FpsClock.getElapsedTime() >= sf::seconds(1.f)) //если время всех итераций с начала дошло до 1с
        {
                
            int fps = frameCount;
            mTextFps.setString("FPS: " + std::to_string(fps));
            frameCount = 0;
            FpsClock.restart();
        }
        
        ++framesRendered;
        if(renderedFramesClock.getElapsedTime() >= sf::seconds(0.2))
        {
            mTextRenderedFrames.setString("OVERALL FRAMES: " + std::to_string(framesRendered));
            renderedFramesClock.restart();
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
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
            default:
                break;
        }
    }
}
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) //обработка движения на WASD
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
    mWindow.setKeyRepeatEnabled(false);
    mWindow.draw(mPlayer);
    mWindow.draw(mTextFps);
    mWindow.draw(mTextRenderedFrames);
    mWindow.display();

}