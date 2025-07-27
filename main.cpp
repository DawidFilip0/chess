#include <SFML/Graphics.hpp>
#include "./graphics/window.h"
#include "./board/BitBoards.h"
#include "./board/Board.h"


#define WIDTH 600
#define HEIGTH 600


using namespace std;


void drawBoard();

int main()
{


    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "SZACHY 2000");
    Board board = Board();


    window.setActive(true);
    WindowManager* winManager = new WindowManager(WIDTH,HEIGTH,window,board);

    while (window.isOpen())
    {


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        winManager->draw();
        
        
    }


}

