//
// Created by stan1 on 12/08/2025.
//

#ifndef GUI_H
#define GUI_H
#include "Game.h"
#include <unordered_map>
#include "RenderState.h"
#include "uiButton.h"
#include <iomanip>

class Game;
class GUI {
private:
    Game* game = nullptr;

    std::unordered_map<RenderState, std::vector<uiButton>> buttons;
    std::vector<sf::Text> text;
    RenderState renderState = DEFAULT;
    RenderState previousState = DEFAULT;
    sf::Font font;
public:
    GUI(Game* game);

    Game* getGame();
    RenderState getState();
    std::vector<uiButton>&  getStateButtons();

    void setState(RenderState renderstate);

    RenderState worldClick(sf::Vector2f mousePos);

    void updateText();

    void render();
};



#endif //GUI_H
