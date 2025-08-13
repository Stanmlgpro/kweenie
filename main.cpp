#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Game");
    window.setFramerateLimit(60);
    Game* game = new Game();
    GameRenderer* renderer = new GameRenderer(game, &window);
    game->setGameRenderer(renderer);
    GUI* gui = new GUI(game);
    game->setGUI(gui);
    while (window.isOpen()) {
        game->update();
    }
    return 0;
}