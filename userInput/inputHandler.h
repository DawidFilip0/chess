#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SFML/Graphics.hpp>
#include "../board/Board.h"

class InputHandler{
public:
    int mousePos[2] = {0};
    int selectedSquare[2] = {0}; // y,x
    bool isSquareSelected = false;
    bool isPieceSelected = false;
    Bitboard possibleMoves = 0;

    InputHandler(sf::RenderWindow& window, Board& board);
    void getHoveredSquare(int width, int& y, int& x);
    void selectSquare(sf::Event event);
    void selectPiece();
    Bitboard getMask(int y, int x);


private:
    sf::RenderWindow& window;
    Board& board;

};


#endif