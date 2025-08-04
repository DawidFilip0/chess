#include "Board.h"


Board::Board():allPieces{}{
    allPieces.setupStartingPosition();
};

Bitboards Board::getAllPieces(){
    return allPieces;
}   

void Board::switchSide(){
    if(WHITE){sideToMove = BLACK;}
    else{sideToMove = WHITE;}
}

void Board::movePieceNoValidate(Bitboard from, Bitboard to){ //does not take validation into account
    movePiece(from,to);
}

void Board::movePiece(Bitboard from, Bitboard to){
    PieceInfo info = allPieces.findPieceType(from);
    allPieces.boards[info.color][info.type]  = allPieces.boards[info.color][info.type] & ~from;
    allPieces.boards[info.color][info.type]  = allPieces.boards[info.color][info.type] | to;
}

Bitboard Board::gen_p_mv(Bitboard pawn, int side){
    Bitboard legal_moves = 0;
    Bitboard tentative_moves = 0;
    Bitboard tentative_attacks = 0;
    int sq = __builtin_ctzll(pawn);


    if(side == WHITE){
        tentative_moves = pawn;
        
        tentative_moves = (tentative_moves >> 8);
        if((sq / 8) == 6){ tentative_moves = tentative_moves | (tentative_moves >> 8) ;}
        
       

        tentative_attacks = pawn;
        if(sq % 8 != 7){ tentative_attacks = (pawn >> 7);}
        if(sq % 8 != 0){tentative_attacks = tentative_attacks | (pawn >> 9);}
        
        legal_moves = tentative_attacks &  allPieces.blackOccupancy;
        tentative_moves = (tentative_moves &  ~allPieces.allOccupancy);
        legal_moves = tentative_moves | legal_moves;
    }
    else{
        tentative_moves = pawn;
        
        tentative_moves = (tentative_moves << 8);
        if((sq / 8) == 1){ tentative_moves = tentative_moves | (tentative_moves << 8) ;}
        
       

        tentative_attacks = pawn;
        if(sq % 8 != 0){ tentative_attacks = (pawn << 7);}
        if(sq % 8 != 7){tentative_attacks = tentative_attacks | (pawn << 9);}
        
        legal_moves = tentative_attacks &  allPieces.blackOccupancy;
        tentative_moves = (tentative_moves &  ~allPieces.allOccupancy);
        legal_moves = tentative_moves | legal_moves;
    }
    
    




    
    return legal_moves;
}



Bitboard Board::get_moves_from_square(Bitboard square){
    Bitboard possible_moves = 0;
    if(square != 0 && (square & (square - 1)) != 0){return possible_moves;} // makes sure only one bit is set to 1
    PieceInfo info = allPieces.findPieceType(square);
    if(info.color == -1){return possible_moves;};
    return apply_gen_funciton(info.color,square,info.type);
}

Bitboard Board::apply_gen_funciton(int side, Bitboard square, int piece_type){
    Bitboard defult_return = 0;
    switch (piece_type)
    {
    case PAWN:
        return gen_p_mv(square,side);
        break;
    default:
        return defult_return;
    }
    return defult_return;
}
