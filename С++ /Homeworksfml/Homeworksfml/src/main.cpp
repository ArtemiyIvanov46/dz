#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "layout.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Button");

    Layout layout(5);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        layout.update(window);

        if (layout.isClicked(window)!=-1) {
            std::cout << "Clicked button number:" << layout.isClicked(window) << std::endl;
        }

        window.clear();
        layout.draw(window);
        window.display();
    }
}
