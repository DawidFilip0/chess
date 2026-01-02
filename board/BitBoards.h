
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

    Bitboard flip_vertical(Bitboard bb) {
    bb = ((bb & 0x00000000000000FFULL) << 56) |
         ((bb & 0x000000000000FF00ULL) << 40) |
         ((bb & 0x0000000000FF0000ULL) << 24) |
         ((bb & 0x00000000FF000000ULL) << 8)  |
         ((bb & 0x000000FF00000000ULL) >> 8)  |
         ((bb & 0x0000FF0000000000ULL) >> 24) |
         ((bb & 0x00FF000000000000ULL) >> 40) |
         ((bb & 0xFF00000000000000ULL) >> 56);
    return bb;
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

const Bitboard RANK1 = 0xFF00000000000000;
const Bitboard RANK2 = 0x00FF000000000000;
const Bitboard RANK3 = 0x0000FF0000000000;
const Bitboard RANK4 = 0x000000FF00000000;
const Bitboard RANK5 = 0x00000000FF000000;
const Bitboard RANK6 = 0x0000000000FF0000;
const Bitboard RANK7 = 0x000000000000FF00;
const Bitboard RANK8 = 0x00000000000000FF;

const Bitboard FILE_A = 0x8080808080808080;
const Bitboard FILE_B = 0x4040404040404040;
const Bitboard FILE_C = 0x2020202020202020;
const Bitboard FILE_D = 0x1010101010101010;
const Bitboard FILE_E = 0x0808080808080808;
const Bitboard FILE_F = 0x0404040404040404;
const Bitboard FILE_G = 0x0202020202020202;
const Bitboard FILE_H = 0x0101010101010101;


#endif 