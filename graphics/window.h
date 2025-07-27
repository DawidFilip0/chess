#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include "../board/BitBoards.h"
#include "../board/Board.h"



class WindowManager{
public:
    WindowManager(int width, int height,sf::RenderWindow& window, Board& board);
    ~WindowManager();
    void createWindow();
    void draw();

;
private:
    int width;
    int heigth;
    sf::Texture textures[COLOR_NB][PIECE_TYPE_NB];

    
    sf::RenderWindow& window;
    Board& board;
    void drawBoard();
    void drawPieces(int side);

}
;



#endif