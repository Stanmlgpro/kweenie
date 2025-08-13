//
// Created by kipteam on 4/24/25.
//

#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>

class uiButton {
public:
	uiButton();

	sf::RectangleShape& getShape();
	sf::Text& getLabel();

	void setOnClick(std::function<void()> callback);
	void click();
	void update(const sf::Vector2f& mousePos, bool mousePressed);

private:
	sf::RectangleShape shape;
    sf::Text label;
    std::function<void()> onClick;

	sf::Color normalColor = sf::Color(85, 85, 85);
	sf::Color hoverColor = sf::Color(120, 120, 120);

	bool isHovered = false;
};



#endif //UIBUTTON_H
