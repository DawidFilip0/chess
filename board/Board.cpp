#include "Board.h"

Board::Board():allPieces{}{
    allPieces.setupStartingPosition();
};

bool Board::singleBitIsOn(Bitboard square){
    return (square != 0 && (square & (square - 1)) == 0); // makes sure only one bit is set to 1

}

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

void Board::movePieceValidate(Bitboard from, Bitboard to){
    if(!(singleBitIsOn(from) && singleBitIsOn(to))){return;}
    if((get_moves_from_square(from) & to) == 0){return;}
    movePiece(from,to);
}

void Board::movePiece(Bitboard from, Bitboard to){
    PieceInfo info = allPieces.findPieceType(from);
    PieceInfo infoTo = allPieces.findPieceType(to);
    if(infoTo.color != -1){allPieces.boards[infoTo.color][infoTo.type]  = allPieces.boards[infoTo.color][infoTo.type] & ~to;}
    allPieces.boards[info.color][info.type]  = allPieces.boards[info.color][info.type] & ~from;
    allPieces.boards[info.color][info.type]  = allPieces.boards[info.color][info.type] | to;
    allPieces.calculateOccpancy();
}

Bitboard Board::gen_p_mv(Bitboard pawn, int side){
    Bitboard legal_moves = 0;
    Bitboard tentative_moves = 0;
    Bitboard tentative_attacks = 0;

    if(side == WHITE){
        tentative_moves = pawn;
        
        tentative_moves = (tentative_moves >> 8);
        if(pawn & RANK2){ tentative_moves = tentative_moves | (tentative_moves >> 8) ;}

        tentative_attacks = pawn;
        tentative_attacks = (pawn >> 7);
        tentative_attacks = tentative_attacks | (pawn >> 9);
        
        legal_moves = tentative_attacks &  allPieces.blackOccupancy;
        tentative_moves = (tentative_moves &  ~allPieces.allOccupancy);
        legal_moves = tentative_moves | legal_moves;
    }
    else{
        tentative_moves = pawn;
        
        tentative_moves = (tentative_moves << 8);
        if(pawn & RANK7){ tentative_moves = tentative_moves | (tentative_moves << 8) ;}
        
        tentative_attacks = pawn;
        tentative_attacks = (pawn << 7);
        tentative_attacks = tentative_attacks | (pawn << 9);
        
        legal_moves = tentative_attacks &  allPieces.whiteOccupancy;
        tentative_moves = (tentative_moves &  ~allPieces.allOccupancy);
        legal_moves = tentative_moves | legal_moves;
    }

    return legal_moves;
}

                                   
Bitboard Board::gen_n_mv(Bitboard knight, int side){ //knight
    Bitboard moves = 0;
    int sq = __builtin_ctzll(knight); 
    if(sq % 8 != 7 && sq % 8 != 6){moves = moves | (knight >> 6) |(knight << 10);}
    if(sq % 8 != 7){moves = moves | (knight >> 15)  | (knight << 17)   ;}

    if(sq % 8 != 0 && sq % 8 != 1){moves = moves | (knight >> 10)| (knight << 6);  }
    if(sq % 8 != 0){moves = moves | (knight >> 17) |(knight << 15)  ;}

    moves = (side == WHITE) ? moves & ~allPieces.whiteOccupancy : moves & ~allPieces.blackOccupancy;
    return moves;
}

Bitboard Board::gen_r_mv(Bitboard rook, int side){
    Bitboard moves = 0;
    Bitboard move_pos = 0;
    Bitboard friendly = ((side == WHITE) ? allPieces.whiteOccupancy : allPieces.blackOccupancy);
    Bitboard enemy = ((side == WHITE) ? allPieces.blackOccupancy : allPieces.whiteOccupancy);

    move_pos = rook;
    for(int i = 1 ; i < 8; i++){
        move_pos = move_pos << 8;
        if((move_pos & friendly) != 0){break;}
        moves |= move_pos;
        if((move_pos & enemy) != 0){break;}

    }

    move_pos = rook;
    for(int i = 1; i < 8; i++){
        if(__builtin_ctzll(move_pos) % 8 == 0){break;}
        move_pos = move_pos >> 1;
        if((move_pos & friendly) != 0){break;}
        moves |= move_pos;
        if((move_pos & enemy) != 0){break;}

    }   

    move_pos = rook;
    for(int i = 1 ; i < 8; i++){
        move_pos = move_pos >> 8;
        if((move_pos & friendly) != 0){break;}
        moves |= move_pos;
        if((move_pos & enemy) != 0){break;}

    }

    move_pos = rook;
    for(int i = 1; i< 8; i++){
        if(__builtin_ctzll(move_pos) % 8 == 7){break;}
        move_pos = move_pos << 1;
        if((move_pos & friendly) != 0){break;}
        moves |= move_pos;
        if((move_pos & enemy) != 0){break;}

    }
    return moves;
}


Bitboard Board::gen_b_mv(Bitboard bishop, int side){
    Bitboard moves = 0;
    Bitboard move_pos = 0;

    Bitboard friendly = ((side == WHITE) ? allPieces.whiteOccupancy : allPieces.blackOccupancy);
    Bitboard enemy = ((side == WHITE) ? allPieces.blackOccupancy : allPieces.whiteOccupancy);

    move_pos = bishop;
    for(int i = 1; i< 8; i++){
        if(__builtin_ctzll(move_pos) % 8 == 7){break;}
        move_pos = move_pos << 9;
        if((move_pos & friendly) != 0){break;}
        moves |= move_pos;
        if((move_pos & enemy) != 0){break;}
    }

    move_pos = bishop;
    for(int i = 1; i< 8; i++){
        if(__builtin_ctzll(move_pos) % 8 == 0){break;}
        move_pos = move_pos << 7;
        if((move_pos & friendly) != 0){break;}
        moves |= move_pos;
        if((move_pos & enemy) != 0){break;}
    }

    move_pos = bishop;
    for(int i = 1; i< 8; i++){
        if(__builtin_ctzll(move_pos) % 8 == 0){break;}
        move_pos = move_pos >> 9;
        if((move_pos & friendly) != 0){break;}
        moves |= move_pos;
        if((move_pos & enemy) != 0){break;}
    }

    move_pos = bishop;
    for(int i = 1; i< 8; i++){
        if(__builtin_ctzll(move_pos) % 8 == 7){break;}
        move_pos = move_pos >> 7;
        if((move_pos & friendly) != 0){break;}
        moves |= move_pos;
        if((move_pos & enemy) != 0){break;}
    }

    return moves;

}


Bitboard Board::gen_k_mv(Bitboard king, int side){
    Bitboard moves = 0;

    Bitboard friendly = ((side == WHITE) ? allPieces.whiteOccupancy : allPieces.blackOccupancy);
    int slides[] = {1,7,8,9};

    Bitboard move_pos = king;
    for(int i = 0; i < 4 ; i++){
        move_pos = king << slides[i];
        if((move_pos & friendly) != 0){continue;}
        moves |= move_pos;
    }

    move_pos = king;
    for(int i = 0; i < 4 ; i++){
        move_pos = king >> slides[i];
        if((move_pos & friendly) != 0){continue;}
        moves |= move_pos;
    }

    return moves;
}


Bitboard Board::get_moves_from_square(Bitboard square){
    Bitboard possible_moves = 0;
    if(!singleBitIsOn(square)){return possible_moves;} // makes sure only one bit is set to 1
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
    case KNIGHT:
        return gen_n_mv(square,side);
    case ROOK:
        return gen_r_mv(square,side);
    case BISHOP:
        return gen_b_mv(square,side);
    case QUEEN:
        return ( gen_r_mv(square,side) | gen_b_mv(square,side));
        break;
    case KING:
        return gen_k_mv(square, side);
        break;
    default:
        return defult_return;
    }
    return defult_return;
}
