#include <SFML/Graphics.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(800,600), "SFML Application");
    sf::CircleShape shape;
    shape.setRadius(67.f);
    shape.setPosition(sf::Vector2f(200.f, 300.f));
    shape.setFillColor(sf::Color::Cyan);
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();
        window.draw(shape);
        window.display();
    }
}