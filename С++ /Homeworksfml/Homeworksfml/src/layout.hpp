#include "button.hpp"
#include <vector>
class Layout {
private:
    int number;
    std::vector<Button> buttons;

public:
    Layout(int number): number(number){
        int columns = 3;

        for (int i=0; i!=number; i++) {
            int row = i / columns;
            int col = i % columns;

            float x = 100 + col * 210;
            float y = 100 + row * 110;
            buttons.emplace_back(Button(sf::Vector2f(200,100), sf::Vector2f(x, y)));
            buttons.back().setOnClicked([](){std::cout << "dwhjdbnak";});
        }
    }
    void update(sf::RenderWindow& window) {
        for (Button& button : buttons) {
            button.update(window);
        }
    }
    void draw(sf::RenderWindow& window) {
        for (Button& button : buttons) {
            button.draw(window);
        }
    }
    int isClicked(sf::RenderWindow& window) {
        for (int i=0; i!=number; i++) {
            if (buttons[i].isClicked(window)) {
                return i+1;
            }
        }
        return -1;
    }
};
