

#include "inputHandler.h"


InputHandler::InputHandler(sf::RenderWindow& window, Board& board)
:window(window),board(board){}


void InputHandler::getHoveredSquare(int width, int& y, int& x){
    sf::Vector2<int> pos;
    pos = sf::Mouse::getPosition(window);
    int sq_width = width/8;
    x = (int)(pos.x/sq_width);
    y = (int)(pos.y/sq_width);
}

void InputHandler::selectSquare(sf::Event event){
    if(event.mouseButton.button == sf::Mouse::Left){
        isSquareSelected = true;
        getHoveredSquare(600,selectedSquare[0],selectedSquare[1]);
        Bitboard maks = getMask(selectedSquare[0],selectedSquare[1]);
        possibleMoves = board.get_moves_from_square(maks);
        if(isPieceSelected){
            //in future: applyUserMove(from, to)
        }
    }
    else if (event.mouseButton.button == sf::Mouse::Right){
        isSquareSelected = false;
        selectedSquare[0] = 1;
        selectedSquare[1] = 1;
    }
}


Bitboard InputHandler::getMask(int y, int x){
Bitboard mask = 1;
int shift = y*8 + x;
mask = mask << shift;
return mask;
}