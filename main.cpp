
#include "Engine.h"

sf::RectangleShape createRectangle(int x, int y, int width, int height, sf::Color fillColor) {
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setPosition(x, y);
    rectangle.setFillColor(fillColor);
    return rectangle;
}

//void initializeMazeTable(int mazeTable[][MAZE_TABLE_ROWS]) {
//    for (int i = 0; i < MAZE_TABLE_COLUMNS; i++) {
//        for (int j = j = 0; j < MAZE_TABLE_ROWS; j++) {
//            mazeTable[i][j] = 1;
//        }
//    }
//}

int main(int, char const**)
{

    Engine engine;
    engine.start();
    /*sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML window");
    
    sf::RectangleShape rectangle2 = createRectangle(1650, 300, 50, 50, sf::Color::White);
    sf::RectangleShape rectangle22 = createRectangle(1550, 200, 250, 250, sf::Color::Black);
    sf::RectangleShape rectangle23 = createRectangle(1525, 175, 300, 300, sf::Color::Yellow);

    
    sf::RectangleShape rectangle3;
    rectangle3.setSize(sf::Vector2f(50, 50));
    rectangle3.setOutlineColor(sf::Color::Red);
    rectangle3.setPosition(1525, 600);
    rectangle3.setFillColor(sf::Color::Green);
    
    sf::RectangleShape rectangle32;
    rectangle32.setSize(sf::Vector2f(150, 150));
    rectangle32.setOutlineColor(sf::Color::Red);
    rectangle32.setPosition(1475, 550);
    rectangle32.setFillColor(sf::Color::Black);
    
    sf::RectangleShape rectangle33;
    rectangle33.setSize(sf::Vector2f(200, 200));
    rectangle33.setOutlineColor(sf::Color::Red);
    rectangle33.setPosition(1450, 525);
    rectangle33.setFillColor(sf::Color::Yellow);
    
    sf::RectangleShape rectangle4;
    rectangle4.setSize(sf::Vector2f(50, 50));
    rectangle4.setOutlineColor(sf::Color::Red);
    rectangle4.setPosition(1775, 600);
    rectangle4.setFillColor(sf::Color::Red);
    
    sf::RectangleShape rectangle42;
    rectangle42.setSize(sf::Vector2f(150, 150));
    rectangle42.setOutlineColor(sf::Color::Red);
    rectangle42.setPosition(1725, 550);
    rectangle42.setFillColor(sf::Color::Black);
    
    sf::RectangleShape rectangle43;
    rectangle43.setSize(sf::Vector2f(200, 200));
    rectangle43.setOutlineColor(sf::Color::Red);
    rectangle43.setPosition(1700, 525);
    rectangle43.setFillColor(sf::Color::Yellow);
    
    sf::RectangleShape rectangle5;
    rectangle5.setSize(sf::Vector2f(150, 150));
    rectangle5.setOutlineColor(sf::Color::Red);
    rectangle5.setPosition(300, 900);
    rectangle5.setFillColor(sf::Color::Green);
    
    sf::RectangleShape rectangle6;
    rectangle6.setSize(sf::Vector2f(150, 150));
    rectangle6.setOutlineColor(sf::Color::Red);
    rectangle6.setPosition(600, 900);
    rectangle6.setFillColor(sf::Color::Red);
    
    int mazeTable[MAZE_TABLE_COLUMNS][MAZE_TABLE_ROWS];
    int n = 1;

    initializeMazeTable(mazeTable);

   
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
        for(int i = 0; i < MAZE_TABLE_COLUMNS; i++){
            for(int j = 0; j < MAZE_TABLE_ROWS; j++){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&position.x<i*TABLE_CELL_SIZE+20&&position.x>i*TABLE_CELL_SIZE&&position.y>j*TABLE_CELL_SIZE&&position.y<j*TABLE_CELL_SIZE+20){
                        if(mazeTable[i][j]==1&&n==1){
                            mazeTable[i][j]=0;
                        }
                        else if(n==2){
                            mazeTable[i][j]=2;
                        }
                        else if(n==3){
                            mazeTable[i][j]=3;
                        }
                }
            }
        }
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&position.x<1700&&position.x>1650&&position.y>300&&position.y<350){
                n=1;
        }
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&position.x<1575&&position.x>1525&&position.y>600&&position.y<650){
                n=2;
        }
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&position.x<1825&&position.x>1775&&position.y>600&&position.y<650){
                n=3;
        }
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&position.x<750&&position.x>600&&position.y>900&&position.y<1050){
            for(int i = 1; i < MAZE_TABLE_COLUMNS; i++){
                for(int j = 1; j < MAZE_TABLE_ROWS; j++){
                    mazeTable[i][j]=1;
                }
            }
        }
        
        window.draw(createRectangle(0, 0, 1920, 1080, sf::Color::Blue));
        for(int i=0; i < MAZE_TABLE_COLUMNS; i++){
            for(int j = 0; j < MAZE_TABLE_ROWS; j++){
                if(mazeTable[i][j]==1){
                    window.draw(createRectangle(i * TABLE_CELL_SIZE, j * TABLE_CELL_SIZE, TABLE_CELL_SIZE, TABLE_CELL_SIZE, sf::Color::Black));
                }
                else if(mazeTable[i][j]==0){
                    window.draw(createRectangle(i*TABLE_CELL_SIZE, j*TABLE_CELL_SIZE, TABLE_CELL_SIZE, TABLE_CELL_SIZE, sf::Color::White));
                }
                else if(mazeTable[i][j]==2){
                    window.draw(createRectangle(i*TABLE_CELL_SIZE, j*TABLE_CELL_SIZE, TABLE_CELL_SIZE, TABLE_CELL_SIZE, sf::Color::Green));
                }
                else if(mazeTable[i][j]==3){
                    window.draw(createRectangle(i*TABLE_CELL_SIZE, j*TABLE_CELL_SIZE, TABLE_CELL_SIZE, TABLE_CELL_SIZE, sf::Color::Red));
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
    }*/
    return EXIT_SUCCESS;
}
