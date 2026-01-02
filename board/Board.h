#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include "BitBoards.h"



class Board{
    public:
    
        Board();
        void switchSide();
        void movePieceValidate(Bitboard from, Bitboard to);
        void movePieceNoValidate(Bitboard from, Bitboard to);
        bool checkIfKingChecked(int side);
        Bitboards getAllPieces();

        
        //move generation
        Bitboard get_moves_from_square(Bitboard square);
        Bitboard apply_gen_funciton(int side, Bitboard sqare, int piece_type);
        Bitboard gen_p_mv(Bitboard piece, int side);
        Bitboard gen_b_mv(Bitboard piece, int side);
        Bitboard gen_k_mv(Bitboard piece, int side); //king
        Bitboard gen_n_mv(Bitboard piece, int side); //knight
        Bitboard gen_q_mv(Bitboard piece, int side);
        Bitboard gen_r_mv(Bitboard piece, int side);
        Bitboard add_castling_if_possible(int side);
    private:
        bool sideToMove;
        bool blackQueenSideCastlingPossible; // as in, legal right has not been forefited yet
        bool blackKingSideCastlingPossible;
        bool whiteQueenSideCastlingPossible;
        bool whiteKingSideCastlingPossible;
        bool isBlackChecked;
        bool isWhiteChecked;
        short int move_number;
        Bitboards allPieces;
        
        bool checkIfAttacked(Bitboard square, int side);
        bool singleBitIsOn(Bitboard sq);
        void movePiece(Bitboard from, Bitboard to);

};

#endif