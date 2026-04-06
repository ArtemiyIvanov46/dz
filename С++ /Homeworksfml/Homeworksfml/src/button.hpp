#pragma once
#include <SFML/Graphics.hpp>

class Button {
private:
    sf::RectangleShape shape;

    sf::Color normalColor = sf::Color::Blue;
    sf::Color hoverColor = sf::Color::Green;

public:
    Button(sf::Vector2f size, sf::Vector2f position) {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(normalColor);
    }
    template<typename Func>
    void setOnClicked(Func func) {
        this->func = func;
    }
    void update(sf::RenderWindow& window) {
        // позиция мыши
        auto mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mouse = {(float)mousePos.x, (float)mousePos.y};

        // проверка: мышь внутри кнопки
        if (shape.getGlobalBounds().contains(mouse)) {
            shape.setFillColor(hoverColor);
        } else {
            shape.setFillColor(normalColor);/Users/rootadmin/Desktop/Информатика/С++ /Homeworksfml/Homeworksfml/src/main.cpp
        }
    }

    bool isClicked(sf::RenderWindow& window) {
        auto mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mouse = {(float)mousePos.x, (float)mousePos.y};

        if (shape.getGlobalBounds().contains(mouse) &&
            sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            return true;
        }
        return false;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }
};

