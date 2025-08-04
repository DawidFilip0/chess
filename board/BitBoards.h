
#ifndef BITBOARDS_H
#define BITBOARDS_H

#include <cstdint>
#include "../enums.h"

using Bitboard = uint64_t;

struct PieceInfo{
    int color;
    int type;
};


struct Bitboards {
    Bitboard boards[COLOR_NB][PIECE_TYPE_NB];
    Bitboard blackOccupancy;
    Bitboard whiteOccupancy;
    Bitboard allOccupancy;


    void clear() {
        for(int color = WHITE; color < COLOR_NB; color++){
            for(int piece = PAWN; piece < PIECE_TYPE_NB; piece++){
                boards[color][piece] = 0;
            }
        }

    }


    void setupStartingPosition(){
        clear();
        boards[WHITE][PAWN] = 0x00FF000000000000;
        boards[WHITE][KNIGHT] = 0x4200000000000000;
        boards[WHITE][ROOK] = 0x8100000000000000;
        boards[WHITE][BISHOP] = 0x2400000000000000;
        boards[WHITE][QUEEN] = 0x0800000000000000;
        boards[WHITE][KING] = 0x1000000000000000;

        boards[BLACK][PAWN] = 0x000000000000FF00;
        boards[BLACK][KNIGHT] = 0x0000000000000042;
        boards[BLACK][ROOK] = 0x0000000000000081;
        boards[BLACK][BISHOP] = 0x0000000000000024;
        boards[BLACK][QUEEN] = 0x0000000000000008;
        boards[BLACK][KING] = 0x0000000000000010;

        calculateOccpancy();

    }

    void calculateOccpancy(){
        whiteOccupancy = boards[WHITE][PAWN] |  boards[WHITE][KNIGHT] | boards[WHITE][ROOK] |boards[WHITE][BISHOP] | boards[WHITE][QUEEN] |  boards[WHITE][KING];
        blackOccupancy = boards[BLACK][PAWN] |  boards[BLACK][KNIGHT] | boards[BLACK][ROOK] |boards[BLACK][BISHOP] | boards[BLACK][QUEEN] |  boards[BLACK][KING];;
        allOccupancy = whiteOccupancy | blackOccupancy;
    }

    PieceInfo findPieceType(Bitboard square){
        for(int color = WHITE; color < COLOR_NB; color++){
            for(int piece = PAWN; piece < PIECE_TYPE_NB; piece++ ){
                if((boards[color][piece] & square) > 0){
                    return {color,piece};
                }

            }
        }
        return {-1,-1}; //empty square
    }



};

#endif 