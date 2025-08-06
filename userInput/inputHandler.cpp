

#include "inputHandler.h"
#include <iostream>


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
        if(isPieceSelected){
            isSquareSelected = false;
            isPieceSelected = false;
            Bitboard from = getMask(selectedSquare[0],selectedSquare[1]);
            int y;
            int x;
            getHoveredSquare(600,y,x);
            Bitboard to = getMask(y,x);
            std::cout << "im doing something!" << std::endl;
            board.movePieceValidate(from,to);
            return;
        }

        getHoveredSquare(600,selectedSquare[0],selectedSquare[1]);
        Bitboard maks = getMask(selectedSquare[0],selectedSquare[1]);
        if(board.getAllPieces().findPieceType(maks).color != -1){isPieceSelected = true;}
        isSquareSelected = true;
        possibleMoves = board.get_moves_from_square(maks);

    }
    else if (event.mouseButton.button == sf::Mouse::Right){
        isSquareSelected = false;
        isPieceSelected = false;
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