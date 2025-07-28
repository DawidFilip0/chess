#include <SFML/Graphics.hpp>
#include "./graphics/window.h"
#include "./board/BitBoards.h"
#include "./board/Board.h"
#include "./userInput/inputHandler.h"


#define WIDTH 600
#define HEIGTH 600


using namespace std;


void drawBoard();

int main()
{


    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "SZACHY 2000");
    Board board = Board();
    window.setActive(true);
    
    InputHandler inputHandler = InputHandler(window,board);
    WindowManager winManager = WindowManager(WIDTH,HEIGTH,window,board);


    while (window.isOpen())
    {


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        winManager.draw();
       
        
        
    }


}

