#ifndef INPUTHANDLER_H
#define INPUTHANDER_H

#include <SFML/Graphics.hpp>
#include "../graphics/window.h"
#include "../board/Board.h"

class InputHandler{
public:

    InputHandler(WindowManager winManager,sf::RenderWindow& window, Board& board);
    void handleMouse(int width);

private:
    sf::RenderWindow& window;
    Board& board;
    WindowManager& winManager;



};


#endif