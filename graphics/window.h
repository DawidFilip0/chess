#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include "../board/BitBoards.h"
#include "../board/Board.h"



class WindowManager{
public:
    WindowManager(int width, int height,sf::RenderWindow& window, Board& board);
    // ~WindowManager();
    void createWindow();
    void draw();
    void colorSquare(int y, int x, sf::Color col);


;
private:
    int width;
    int heigth;
    sf::Texture textures[COLOR_NB][PIECE_TYPE_NB];

    
    sf::RenderWindow& window;
    Board& board;
    sf::Mouse mouse;
    void drawBoard();
    void handleMouse(); //change the name later
    void drawPieces(int side);

}
;



#endif