

#include "inputHandler.h"


InputHandler::InputHandler(WindowManager winManager,sf::RenderWindow& window, Board& board)
:winManager(winManager),window(window),board(board){
    
}


void InputHandler::handleMouse(int width){

    sf::Vector2<int> pos;
    pos = sf::Mouse::getPosition(window);
    int sq_width = width/8;
    int xsq = (int)(pos.x/sq_width);
    int ysq = (int)(pos.y/sq_width);
    

    winManager.colorSquare(ysq,xsq,sf::Color::Blue);

}
