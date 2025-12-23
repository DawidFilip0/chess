#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include "../board/BitBoards.h"
#include "../board/Board.h"
#include "../userInput/inputHandler.h"



class WindowManager{
public:
    WindowManager(int width, int height,sf::RenderWindow& window, Board& board,InputHandler& inputHandler );
    // ~WindowManager();
    void createWindow();
    void draw();
    void colorSquare(int y, int x, sf::Color col);




private:
    int width;
    int heigth;
    int square_width;
    sf::Texture textures[COLOR_NB][PIECE_TYPE_NB];


    InputHandler& inputHandler; 
    sf::RenderWindow& window;
    Board& board;
    sf::Mouse mouse;
    void drawBoard();
    void drawHighlight();
    void drawSelect();
    void drawPossibleMoves(int perspective);
    void drawPieces(int perspective);

}
;



#endif