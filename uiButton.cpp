//
// Created by kipteam on 4/24/25.
//
#include <iostream>

#include "uiButton.h"


uiButton::uiButton() {};

sf::RectangleShape& uiButton::getShape() {
    return this->shape;
}

sf::Text& uiButton::getLabel() {
    return this->label;
}

void uiButton::setOnClick(std::function<void()> callback) {
    this->onClick = callback;
}

void uiButton::click() {
    return this->onClick();
}

void uiButton::update(const sf::Vector2f& mousePos, bool mousePressed) {
    if (shape.getGlobalBounds().contains(mousePos)) {
        isHovered = true;
        if (mousePressed) {
            click();
        }
    } else {
        isHovered = false;
    }

    if (isHovered) {
        shape.setFillColor(hoverColor);
    } else {
        shape.setFillColor(normalColor);
    }
}
