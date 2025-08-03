#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include "BitBoards.h"



class Board{
    public:
    
        Board();
        void switchSide();
        void movePiece();
        Bitboards getAllPieces();
        
        //move generation
        Bitboard get_moves_from_square(Bitboard square);
        Bitboard gen_p_mv(Bitboard piece, int side);
        Bitboard gen_b_mv(Bitboard piece, int side);
        Bitboard gen_k_mv(Bitboard piece, int side); //king
        Bitboard gen_n_mv(Bitboard piece, int side); //knight
        Bitboard gen_q_mv(Bitboard piece, int side);
        Bitboard gen_r_mv(Bitboard piece, int side);
    private:

        bool sideToMove;
        bool isBlackChecked;
        bool isWhiteChecked;
        short int move_number;
        Bitboards allPieces;

};

#endif