#include "window.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>


WindowManager::WindowManager(int width, int height, sf::RenderWindow& win, Board& board):window(win),board(board)
{

    this -> width = width;
    this -> heigth = heigth;
    std::string path;
   

    for(int color = 0; color < COLOR_NB; color++){
    for(int p = 0; p < PIECE_TYPE_NB; p++){
        if(color == WHITE){
            path = "./graphics/textures/w" + std::to_string(p) + ".png" ;
        }
        else{
           path = "./graphics/textures/b" +  std::to_string(p)  + ".png";
        }

        if (!this->textures[color][p].loadFromFile(path)) { // path is considered from executable file location, not this file
                std::cout << "Error loading texture!" << std::endl;
                
        }


    }
    }







}

void WindowManager::draw(){
        window.clear();
        drawBoard();
        drawPieces(WHITE);
        window.display();
}


void WindowManager::drawBoard(){
        int square_width = (int)width/8;      
        sf::Color brown(181, 136, 99);  
        sf::Color light(240, 217, 181);  

        

        sf::RectangleShape shape2({square_width,square_width});
        for(int i = 0; i < 8; i++){
            for(int j = 0; j<8; j++){
                shape2.setPosition(i*square_width,j*square_width);
                if((i+j) %2 == 0){
                shape2.setFillColor(light);
                }
                else{
                shape2.setFillColor(brown);
                }
            window.draw(shape2);
            }
        }

}

void WindowManager::drawPieces(int side){

        int square_width = (int)width/8;
        sf::RectangleShape shape2({square_width,square_width});
        sf::RectangleShape shape3({square_width,square_width});

                    


        for(int color = WHITE; color < COLOR_NB; color++){
            for(int piece = PAWN; piece < PIECE_TYPE_NB; piece++ ){

                Bitboard bb = board.getAllPieces().boards[color][piece];
                while(bb){
                    int sq = __builtin_ctzll(bb); 

                    bb &= bb-1; // a trick to pop least significant bit     0b1100 - 1 = 0b1011, 0b1100 & 0b1011 = 0b1000
                    int x = 0;
                    int y = 0;
                    if(side == BLACK){
                        y =  7 - (sq / 8);
                        x =  7 - (sq % 8); 
                    }
                    else{
                        y = sq / 8;   
                        x =  sq % 8;  
                    }

                    
                    shape2.setTexture(&textures[color][piece]);
                    shape2.setPosition(x*square_width,y*square_width);
                    window.draw(shape2);

                }

            }
        }


        Bitboard wP = board.getAllPieces().boards[WHITE][PAWN];
   

        Bitboard last_bit = wP & -wP;

        Bitboard av_m = board.gen_p_mv(last_bit,WHITE);
        shape3.setFillColor(sf::Color::Blue);
        while(av_m){
                int sq = __builtin_ctzll(av_m); 

                av_m &= av_m-1; // a trick to pop least significant bit     0b1100 - 1 = 0b1011, 0b1100 & 0b1011 = 0b1000
                int x = 0;
                int y = 0;
                if(side == BLACK){
                    y =  7 - (sq / 8);   
                    x =  7 - (sq % 8); 
                }
                else{
                    y = sq / 8;   
                    x =  sq % 8;  
                }

                    
 
                shape3.setPosition(x*square_width,y*square_width);
                window.draw(shape3);
        }
    
}




void WindowManager::colorSquare(int y, int x, sf::Color col){

    int square_width = (int)width/8;
    sf::RectangleShape shape3({square_width,square_width});
    shape3.setFillColor(sf::Color::Transparent);
    shape3.setOutlineColor(col);
    shape3.setOutlineThickness(3);

    shape3.setPosition(x*square_width,y*square_width);
    window.draw(shape3);
    window.display();


}
