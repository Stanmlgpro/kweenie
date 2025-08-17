//
// Created by stan1 on 12/08/2025.
//

#include "GameRenderer.h"

GameRenderer::GameRenderer(Game* game, sf::RenderWindow* window) {
    this->game = game;
    this->window = window;
    this->view = window->getDefaultView();
    this->guiView = sf::View(window->getDefaultView());
    this->Load();
}

void GameRenderer::Load() {
    sf::Texture tileTexture;
    backgroundTileTexture.loadFromFile("../Resources/background_tile.png");
    backgroundTileTexture.setRepeated(true);

    sf::Vector2u size = window->getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;

    background = sf::RectangleShape(sf::Vector2f(width, height));
    background.setTexture(&backgroundTileTexture);
    background.setTextureRect(sf::IntRect(0, 0, width, height));
}

void GameRenderer::handleWindowView(const sf::Event& event) const {
    sf::View view = window->getDefaultView();
    view.setSize(event.size.width, event.size.height);
    view.setCenter(event.size.width / 2.0f, event.size.height / 2.0f);
    window->setView(view);
}

void GameRenderer::handleMousePress(const sf::Event &event) {
    if (event.mouseButton.button == sf::Mouse::Right) {
        isDragging = true;
        lastMousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        return;
    }

    sf::View oldView = window->getView();
    window->setView(guiView);

    sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    std::vector<uiButton>& stateButtons = this->game->getGUI()->getStateButtons();

    bool clicked = false;
    for (uiButton& button : stateButtons) {
        button.update(mousePos, true);
        if (!button.getShape().getGlobalBounds().contains(mousePos)) continue;
        clicked = true;
    }
    window->setView(oldView);
    if (clicked) return;

    mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    this->game->getGUI()->setState(this->game->getGUI()->worldClick(mousePos));
}

void GameRenderer::handleMouseRelease(const sf::Event &event) {
    if (event.mouseButton.button == sf::Mouse::Right) {
        isDragging = false;
        return;
    }

    // left release
}

void GameRenderer::handleKeyPress(const sf::Event &event) {
    switch (event.key.code) {
        case sf::Keyboard::Escape: {
            view.zoom(1.0f / zoom_factor);
            break;
        }
        case sf::Keyboard::K: {
            view.zoom(zoom_factor);
            break;
        }
        case sf::Keyboard::Space: {
            simulationPaused = !simulationPaused;
            break;
        }
        case sf::Keyboard::Q: {
            game->addProjectiles(game->getPlayer()->Q(mousePos));
            break;
        }
        case sf::Keyboard::W: {
                game->addProjectiles(game->getPlayer()->W(mousePos));
                break;
        }
        case sf::Keyboard::E: {
                game->addProjectiles(game->getPlayer()->E(mousePos));
                break;
        }
        case sf::Keyboard::R: {
                game->addProjectiles(game->getPlayer()->R(mousePos));
                break;
        }
        default: {
            std::cerr << "No event found" << std::endl;
            break;
        }
    }
}

void GameRenderer::handleWheelMoved(const sf::Event& event) {
    sf::Vector2i mousePixel = sf::Mouse::getPosition(*window);
    sf::Vector2f mouseWorld = window->mapPixelToCoords(mousePixel, view);
    if (event.mouseWheel.delta > 0) {
        view.zoom(1.0f / zoom_factor);
    }
    if (event.mouseWheel.delta < 0) {
        view.zoom(zoom_factor);
    }
    sf::Vector2f newMouseWorld = window->mapPixelToCoords(mousePixel, view);
    sf::Vector2f offset = mouseWorld - newMouseWorld;
    view.move(offset);
    window->setView(view);
}

void GameRenderer::handleMouseMove(const sf::Event &event) {
    window->setView(guiView);
    mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    for (uiButton& button : this->game->getGUI()->getStateButtons()) {
        button.update(mousePos, false);
    }
    window->setView(view);
    if (this->game->getGUI()->getState() == DEFAULT) {
        mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        return;
    }
    // if (renderState == DRAW_ROAD) return simulationBuilder->ghostRoadCoordinate(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
    // if (renderState == DRAW_TRAFFICLIGHT) return simulationBuilder->ghostTrafficlightCoordinate(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
}


void GameRenderer::handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::Resized:
                handleWindowView(event);
                break;
            case sf::Event::MouseButtonPressed:
                handleMousePress(event);
                break;
            case sf::Event::MouseButtonReleased:
                handleMouseRelease(event);
                break;
            case sf::Event::KeyPressed:
                handleKeyPress(event);
                break;
            case sf::Event::MouseWheelMoved:
                handleWheelMoved(event);
                break;
            case sf::Event::MouseMoved:
                handleMouseMove(event);
                break;
            default:
                break;
        }
    }
}

void GameRenderer::updateCameraView() {
    if (!isDragging) return;
    const sf::Vector2f newMousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

    view.move(lastMousePosition - newMousePosition);
    window->setView(view);

    lastMousePosition = newMousePosition;
}

Game* GameRenderer::getGame() {
    return game;
}
sf::RenderWindow* GameRenderer::getWindow() {
    return window;
}
sf::View GameRenderer::getView() {
    return view;
}
sf::View GameRenderer::getGUIView() {
    return guiView;
}

void GameRenderer::fixBackground() {
    // Get current view rectangle in world coordinates
    sf::FloatRect viewRect(
        view.getCenter().x - view.getSize().x / 2.f,
        view.getCenter().y - view.getSize().y / 2.f,
        view.getSize().x,
        view.getSize().y
    );

    // Resize and move the background shape to cover the entire view
    background.setPosition(viewRect.left, viewRect.top);
    background.setSize(sf::Vector2f(viewRect.width, viewRect.height));

    // Update texture rect so the texture repeats correctly within this rect
    background.setTextureRect(sf::IntRect(
        static_cast<int>(viewRect.left),
        static_cast<int>(viewRect.top),
        static_cast<int>(viewRect.width),
        static_cast<int>(viewRect.height)
    ));
}

void GameRenderer::draw() {
    fixBackground();
    window->draw(background);
    for (Projectile& projectile : this->game->getProjectilePool()) {
        if (projectile.isActive()) projectile.render(window);
    }
    for (AreaEffect& areaEffect : this->game->getAreaEffectPool()) {
        if (areaEffect.isActive()) areaEffect.render(window);
    }
    for (Entity* entity : this->game->getEntities()) {
        entity->render(this->window);
    }
}


void GameRenderer::render() {
    handleEvents();
    updateCameraView();

    this->window->clear();
    draw();
    window->setView(guiView);
    this->game->getGUI()->render();
    window->setView(view);
    this->window->display();
}
