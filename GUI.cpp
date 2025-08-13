//
// Created by stan1 on 12/08/2025.
//

#include "GUI.h"

GUI::GUI(Game* game) {
    this->game = game;

    std::unordered_map<RenderState, std::vector<std::string>> stateLabels = {
        {DEFAULT, {"Structures", "Lorem Ipsum", "Lorem Ipsum", "Lorem Ipsum"}},
        {STRUCTURES, {"Barrack", "Lorem Ipsum", "Back", "Lorem Ipsum", "Lorem Ipsum", "Lorem Ipsum"}}
    };
    std::vector<std::string> abilities = {"Q : Sword", "W : Shield", "E : Dash", "R : Bomb"};
    font.loadFromFile("../Resources/geist_mono.ttf");

    constexpr float buttonHeight = 40;
    constexpr float buttonWidth = 175;
    constexpr float spacing = 20;

    float totalWidth = abilities.size() * buttonWidth + (abilities.size() - 1) * spacing;
    float x = (this->game->getGameRenderer()->getWindow()->getSize().x - totalWidth) / 2.f;
    float y = this->game->getGameRenderer()->getWindow()->getSize().y - buttonHeight - 20;

    std::vector<uiButton> abilitie_buttons;
    for (const std::string& label : abilities) {
        uiButton button{};
        button.getShape().setSize({buttonWidth, buttonHeight});
        button.getShape().setPosition({x, y});
        button.getShape().setFillColor(sf::Color(85, 85, 85));

        button.getLabel().setFont(font);
        button.getLabel().setString(label);
        button.getLabel().setCharacterSize(16);
        button.getLabel().setFillColor(sf::Color::White);

        const sf::FloatRect textRect = button.getShape().getLocalBounds();
        button.getShape().setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
        button.getShape().setPosition(x + buttonWidth / 2.f, y + buttonHeight / 2.f);
        button.getShape().setOutlineThickness(2.f);
        button.getShape().setOutlineColor(sf::Color::White);

        sf::Text& text = button.getLabel();
        const sf::FloatRect labelBounds = text.getLocalBounds();
        text.setOrigin(labelBounds.left + labelBounds.width / 2.f, labelBounds.top + labelBounds.height / 2.f);
        text.setPosition(button.getShape().getPosition());

        this->game->getGameRenderer()->getWindow()->setView(this->game->getGameRenderer()->getView());
        sf::Vector2f mousePos = this->game->getGameRenderer()->getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*this->game->getGameRenderer()->getWindow()));
        if (label == "Q : Sword") {
            button.setOnClick([&]() {
                auto mousePos = this->game->getGameRenderer()->getWindow()->mapPixelToCoords(
                    sf::Mouse::getPosition(*this->game->getGameRenderer()->getWindow())
                );
                this->getGame()->addProjectile(this->game->getPlayer()->Q(mousePos));
            });
        }
        if (label == "W : Shield") {
            button.setOnClick([&]() {
                auto mousePos = this->game->getGameRenderer()->getWindow()->mapPixelToCoords(
                    sf::Mouse::getPosition(*this->game->getGameRenderer()->getWindow())
                );
                this->getGame()->addProjectile(this->game->getPlayer()->W(mousePos));
            });
        }
        if (label == "E : Dash") {
            button.setOnClick([&]() {
                auto mousePos = this->game->getGameRenderer()->getWindow()->mapPixelToCoords(
                    sf::Mouse::getPosition(*this->game->getGameRenderer()->getWindow())
                );
                this->getGame()->addProjectile(this->game->getPlayer()->E(mousePos));
            });
        }
        if (label == "R : Bomb") {
            button.setOnClick([&]() {
                auto mousePos = this->game->getGameRenderer()->getWindow()->mapPixelToCoords(
                    sf::Mouse::getPosition(*this->game->getGameRenderer()->getWindow())
                );
                this->getGame()->addProjectile(this->game->getPlayer()->R(mousePos));
            });
        }
        x += buttonWidth + spacing;
        abilitie_buttons.push_back(button);
    }
    x = 470;
    y = game->getGameRenderer()->getWindow()->getSize().y - buttonHeight - 35;

    for (int i = 0; i < 4; i++) {

        sf::Text text;
        text.setFont(font);
        text.setString("Hello, SFML!");
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        x += buttonWidth + spacing;
        text.setPosition({x, y});

        this->text.push_back(text);
    }

    for (const auto& [state, labels]: stateLabels) {
        constexpr float buttonHeight = 40;
        constexpr float buttonWidth = 175;
        constexpr float spacing = 20;

        float y = 5;
        float x = 5;

        for (const std::string& label : labels) {
            uiButton button{};
            button.getShape().setSize({buttonWidth, buttonHeight});
            button.getShape().setPosition({x, y});
            button.getShape().setFillColor(sf::Color(85, 85, 85));

            button.getLabel().setFont(font);
            button.getLabel().setString(label);
            button.getLabel().setCharacterSize(16);
            button.getLabel().setFillColor(sf::Color::White);

            const sf::FloatRect textRect = button.getShape().getLocalBounds();
            button.getShape().setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
            button.getShape().setPosition(x + buttonWidth / 2.f, y + buttonHeight / 2.f);
            button.getShape().setOutlineThickness(2.f);
            button.getShape().setOutlineColor(sf::Color::White);

            sf::Text& text = button.getLabel();
            const sf::FloatRect labelBounds = text.getLocalBounds();
            text.setOrigin(labelBounds.left + labelBounds.width / 2.f, labelBounds.top + labelBounds.height / 2.f);
            text.setPosition(button.getShape().getPosition());

            if (label == "Structures") button.setOnClick([&]() {setState(STRUCTURES);});
            if (label == "Back") button.setOnClick([&]() {setState(previousState);});
            if (label == "Lorem Ipsum") button.setOnClick([&]() {setState(DEFAULT);});

            buttons[state].push_back(button);
            for (uiButton button_ : abilitie_buttons) {
                buttons[state].push_back(button_);
            }
            y += buttonHeight + spacing;
        }
    }
}

Game* GUI::getGame() {
    return game;
}

void GUI::render() {
    updateText();
    std::vector<uiButton> stateButtons = buttons[renderState];
    for (uiButton& button : stateButtons) {
        this->game->getGameRenderer()->getWindow()->draw(button.getShape());
        this->game->getGameRenderer()->getWindow()->draw(button.getLabel());
    }
    for (sf::Text& text : text) {
        this->game->getGameRenderer()->getWindow()->draw(text);
    }
}
void GUI::setState(RenderState renderstate) {
    previousState = renderState;
    renderState = renderstate;
}
RenderState GUI::getState() {
    return renderState;
}
std::vector<uiButton>&  GUI::getStateButtons() {
    return buttons[renderState];
}
RenderState GUI::worldClick(sf::Vector2f mousePos) {
    if (renderState == DEFAULT) {
        this->game->getPlayer()->setTargetPosition(mousePos);
    }
    return DEFAULT;
}
void GUI::updateText() {
    auto updateOne = [&](sf::Text& t, float value) {
        std::string text_;
        if (value > 0) {
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(1) << value;
            text_ = ss.str();
        }
        else {
            text_ = "READY";
        }
        t.setString(text_);
        sf::FloatRect bounds = t.getLocalBounds();
        t.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    };

    updateOne(text[0], this->game->getPlayer()->getQ_time());
    updateOne(text[1], this->game->getPlayer()->getW_time());
    updateOne(text[2], this->game->getPlayer()->getE_time());
    updateOne(text[3], this->game->getPlayer()->getR_time());
}
