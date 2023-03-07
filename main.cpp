#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"

sf::RectangleShape zrobCzarnyProstokat(int x, int y, int width, int height){
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setPosition(x, y);
    rectangle.setFillColor(sf::Color::Black);
    return rectangle;
}

sf::RectangleShape zrobBialyProstokat(int x, int y, int width, int height){
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setPosition(x, y);
    rectangle.setFillColor(sf::Color::White);
    return rectangle;
}

sf::RectangleShape zrobNiebieskiProstokat(int x, int y, int width, int height){
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setPosition(x, y);
    rectangle.setFillColor(sf::Color::Blue);
    return rectangle;
}

sf::RectangleShape zrobZielonyProstokat(int x, int y, int width, int height){
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setPosition(x, y);
    rectangle.setFillColor(sf::Color::Green);
    return rectangle;
}

sf::RectangleShape zrobCzerwonyProstokat(int x, int y, int width, int height){
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setPosition(x, y);
    rectangle.setFillColor(sf::Color::Red);
    return rectangle;
}

int main(int, char const**)
{
    sf::RenderWindow window(sf::VideoMode(3000, 1700), "SFML window");
    
    sf::RectangleShape rectangle2;
    rectangle2.setSize(sf::Vector2f(50, 50));
    rectangle2.setOutlineColor(sf::Color::Red);
    rectangle2.setPosition(2575, 300);
    rectangle2.setFillColor(sf::Color::White);
    
    sf::RectangleShape rectangle22;
    rectangle22.setSize(sf::Vector2f(250, 250));
    rectangle22.setOutlineColor(sf::Color::Red);
    rectangle22.setPosition(2475, 200);
    rectangle22.setFillColor(sf::Color::Black);
    
    sf::RectangleShape rectangle23;
    rectangle23.setSize(sf::Vector2f(300, 300));
    rectangle23.setOutlineColor(sf::Color::Red);
    rectangle23.setPosition(2450, 175);
    rectangle23.setFillColor(sf::Color::Yellow);
    
    sf::RectangleShape rectangle3;
    rectangle3.setSize(sf::Vector2f(50, 50));
    rectangle3.setOutlineColor(sf::Color::Red);
    rectangle3.setPosition(2450, 600);
    rectangle3.setFillColor(sf::Color::Green);
    
    sf::RectangleShape rectangle32;
    rectangle32.setSize(sf::Vector2f(150, 150));
    rectangle32.setOutlineColor(sf::Color::Red);
    rectangle32.setPosition(2400, 550);
    rectangle32.setFillColor(sf::Color::Black);
    
    sf::RectangleShape rectangle33;
    rectangle33.setSize(sf::Vector2f(200, 200));
    rectangle33.setOutlineColor(sf::Color::Red);
    rectangle33.setPosition(2375, 525);
    rectangle33.setFillColor(sf::Color::Yellow);
    
    sf::RectangleShape rectangle4;
    rectangle4.setSize(sf::Vector2f(50, 50));
    rectangle4.setOutlineColor(sf::Color::Red);
    rectangle4.setPosition(2700, 600);
    rectangle4.setFillColor(sf::Color::Red);
    
    sf::RectangleShape rectangle42;
    rectangle42.setSize(sf::Vector2f(150, 150));
    rectangle42.setOutlineColor(sf::Color::Red);
    rectangle42.setPosition(2650, 550);
    rectangle42.setFillColor(sf::Color::Black);
    
    sf::RectangleShape rectangle43;
    rectangle43.setSize(sf::Vector2f(200, 200));
    rectangle43.setOutlineColor(sf::Color::Red);
    rectangle43.setPosition(2625, 525);
    rectangle43.setFillColor(sf::Color::Yellow);
    
    sf::RectangleShape rectangle5;
    rectangle5.setSize(sf::Vector2f(150, 150));
    rectangle5.setOutlineColor(sf::Color::Red);
    rectangle5.setPosition(700, 1300);
    rectangle5.setFillColor(sf::Color::Green);
    
    sf::RectangleShape rectangle6;
    rectangle6.setSize(sf::Vector2f(150, 150));
    rectangle6.setOutlineColor(sf::Color::Red);
    rectangle6.setPosition(1000, 1300);
    rectangle6.setFillColor(sf::Color::Red);
    
    int tab[55][30];
    int i=1;
    int j=1;
    int n=1;
    srand(time(0));
    for(i=1; i<55; i++){
        for(j=1; j<30; j++){
            int a=rand()%2;
            tab[i][j]=1;
        }
    }
    while (window.isOpen())
    {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        window.clear();
        for(i=0; i<55; i++){
            for(j=0; j<30; j++){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&position.x<i*40+20&&position.x>i*40&&position.y>j*40&&position.y<j*40+20){
                        if(tab[i][j]==1&&n==1){
                            tab[i][j]=0;
                        }
                        else if(n==2){
                            tab[i][j]=2;
                        }
                        else if(n==3){
                            tab[i][j]=3;
                        }
                }
            }
        }
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&position.x<2625&&position.x>2575&&position.y>300&&position.y<350){
                n=1;
        }
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&position.x<2500&&position.x>2450&&position.y>600&&position.y<650){
                n=2;
        }
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&position.x<2750&&position.x>2700&&position.y>600&&position.y<650){
                n=3;
        }
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&position.x<1150&&position.x>1000&&position.y>1300&&position.y<1450){
            for(i=1; i<55; i++){
                for(j=1; j<30; j++){
                    tab[i][j]=1;
                }
            }
        }
        
        window.draw(zrobNiebieskiProstokat(0, 0, 3000, 1700));
        for(i=1; i<55; i++){
            for(j=1; j<30; j++){
                if(tab[i][j]==1){
                    window.draw(zrobCzarnyProstokat(i*40, j*40, 40, 40));
                }
                else if(tab[i][j]==0){
                    window.draw(zrobBialyProstokat(i*40, j*40, 40, 40));
                }
                else if(tab[i][j]==2){
                    window.draw(zrobZielonyProstokat(i*40, j*40, 40, 40));
                }
                else if(tab[i][j]==3){
                    window.draw(zrobCzerwonyProstokat(i*40, j*40, 40, 40));
                }
            }
        }
        
        window.draw(rectangle23);
        window.draw(rectangle22);
        window.draw(rectangle2);
        window.draw(rectangle33);
        window.draw(rectangle32);
        window.draw(rectangle3);
        window.draw(rectangle43);
        window.draw(rectangle42);
        window.draw(rectangle4);
        window.draw(rectangle5);
        window.draw(rectangle6);
        window.display();
    }
    return EXIT_SUCCESS;
}
