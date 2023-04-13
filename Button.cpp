#include "Button.h"
#include <iostream>

Button::Button() {};

Button::Button(const std::string& buttonText, const sf::Vector2f& position, const sf::Font& font,
    const sf::Color& textColor, const sf::Color& buttonColor, const sf::Color& outlineColor, const sf::Vector2f& buttonSize)
{
    m_buttonShape.setPosition(position);
    m_buttonShape.setSize(buttonSize);
    m_buttonShape.setFillColor(buttonColor);
    m_buttonShape.setOutlineThickness(2);
    m_buttonShape.setOutlineColor(outlineColor);

    m_buttonText.setFont(font);
    m_buttonText.setString(buttonText);
    m_buttonText.setCharacterSize(24);
    m_buttonText.setFillColor(textColor);
    m_buttonText.setOrigin(m_buttonText.getLocalBounds().width / 2, m_buttonText.getLocalBounds().height / 2);
    m_buttonText.setPosition(position + buttonSize / 2.0f);
}

/*Button::Button(const sf::Texture& buttonTexture, const sf::Vector2f& position, const sf::Color& outlineColor, const sf::Vector2f& buttonSize)
{
    m_buttonSprite.setTexture(buttonTexture);
    m_buttonSprite.setPosition(position);
    m_buttonSprite.setScale(buttonSize.x / buttonTexture.getSize().x, buttonSize.y / buttonTexture.getSize().y);

    m_buttonShape.setSize(buttonSize);
    m_buttonShape.setPosition(position);
}*/

Button::Button(const char* buttonTexture, const sf::Vector2f& position, const sf::Color& outlineColor, const sf::Vector2f& buttonSize)
{
    sf::Texture texture;
    printf("%s\n", buttonTexture);
    if (!texture.loadFromFile(buttonTexture))
    {
    }
    m_buttonSprite.setTexture(texture);
    m_buttonSprite.setPosition(position);
    m_buttonSprite.setScale(buttonSize.x / texture.getSize().x, buttonSize.y / texture.getSize().y);

    m_buttonShape.setSize(buttonSize);
    m_buttonShape.setPosition(position);
}

bool Button::isClicked(const sf::RenderWindow* window) const
{
    return m_buttonShape.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    if (m_buttonSprite.getTexture() != nullptr)
    {
        target.draw(m_buttonSprite, states);
    }
    else
    {
        target.draw(m_buttonShape, states);
        target.draw(m_buttonText, states);
    }
}