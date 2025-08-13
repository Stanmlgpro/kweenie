//
// Created by stan1 on 12/08/2025.
//

#ifndef GAMERENDERER_H
#define GAMERENDERER_H
#include "Game.h"
#include "RenderState.h"


class Game;
class GameRenderer {
private:
    Game* game = nullptr;
    sf::RenderWindow* window;

    sf::View view;
    sf::View guiView;
    sf::Vector2f mousePos;
    sf::RectangleShape background;
    sf::Texture backgroundTileTexture;

    bool simulationPaused = false;

    sf::Vector2f lastMousePosition;
    bool isDragging = false;
    float zoom_factor = 1.16;
public:
    GameRenderer(Game* game, sf::RenderWindow* window);

    void Load();

    void fixBackground();

    void handleEvents();
    void handleWindowView(const sf::Event& event) const;
    void handleMousePress(const sf::Event& event);
    void handleMouseRelease(const sf::Event& event);
    void handleKeyPress(const sf::Event& event);
    void handleWheelMoved(const sf::Event& event);
    void handleMouseMove(const sf::Event& event);

    void updateCameraView();

    Game* getGame();
    sf::RenderWindow* getWindow();
    sf::View getView();
    sf::View getGUIView();

    void render();
    void draw();
};



#endif //GAMERENDERER_H
