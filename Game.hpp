#pragma once

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

private:
    void processEvents(); // проверяет ввод игрока
    void update(sf::Time deltaTime);
    void render();
    void handlePLayerInput(sf::Keyboard::Key key, bool isPressed);

private:
    static const float PlayerSpeed;
    static const sf::Time TimePerFrame;

    sf::RenderWindow mWindow;
    sf::CircleShape  mPlayer;

    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
};