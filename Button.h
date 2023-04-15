#pragma once

#include <SFML/Graphics.hpp>


class Button : public sf::Drawable, public sf::Transformable
{
private:
    sf::Texture texture;
    sf::RectangleShape m_buttonShape;
    sf::Text m_buttonText;
    sf::Sprite m_buttonSprite;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Button();

    Button(const std::string& buttonText, const sf::Vector2f& position, const sf::Font& font,
        const sf::Color& textColor, const sf::Color& buttonColor, const sf::Color& outlineColor, const sf::Vector2f& buttonSize);

    Button(std::string texturePath, const sf::Vector2f& position, const sf::Color& outlineColor, const sf::Vector2f& buttonSize);

    bool isClicked(const sf::RenderWindow* window) const;


    float getX();
    float getY();
    float getWidth();
    float getHeight();
};