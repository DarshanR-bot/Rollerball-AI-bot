#include <algorithm>
#include <random>
#include <iostream>
#include <thread>

#include "board.hpp"
#include "engine.hpp"
#include "butils.hpp"
using namespace std;
int nodes;
map<vector<U8>, int> stateMap;

int black_rook_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -50
    };
int black_rook_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -50
    };
int black_king[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10 
        };
int black_bishop[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -42
    };
int black_knight_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -40
    };
int black_knight_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -40
    };
int black_pawn_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int black_pawn_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int black_pawn_3[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int black_pawn_4[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };

int white_rook_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -50
    };
int white_rook_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -50
    };
int white_king[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10    
        };
int white_bishop[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -42
    };
int white_knight_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -40
    };
int white_knight_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -40
    };
int white_pawn_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int white_pawn_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int white_pawn_3[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int white_pawn_4[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };


int bblack_rook_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -50
    };
int bblack_rook_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -50
    };
int bblack_king[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10 
        };
int bblack_bishop[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -42
    };
int bblack_knight_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -40
    };
int bblack_knight_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -40
    };
int bblack_pawn_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int bblack_pawn_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int bblack_pawn_3[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int bblack_pawn_4[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };

int bwhite_rook_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -50
    };
int bwhite_rook_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -50
    };
int bwhite_king[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10    
        };
int bwhite_bishop[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -42
    };
int bwhite_knight_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -40
    };
int bwhite_knight_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -40
    };
int bwhite_pawn_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int bwhite_pawn_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int bwhite_pawn_3[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int bwhite_pawn_4[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };


int cblack_rook_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -50
    };
int cblack_rook_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -50
    };
int cblack_king[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10 
        };
int cblack_bishop[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -42
    };
int cblack_knight_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -40
    };
int cblack_knight_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -40
    };
int cblack_pawn_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int cblack_pawn_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int cblack_pawn_3[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int cblack_pawn_4[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };

int cwhite_rook_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -50
    };
int cwhite_rook_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -50
    };
int cwhite_king[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10    
        };
int cwhite_bishop[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -42
    };
int cwhite_knight_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -40
    };
int cwhite_knight_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -40
    };
int cwhite_pawn_1[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int cwhite_pawn_2[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int cwhite_pawn_3[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };
int cwhite_pawn_4[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, -10
    };







bool addState(const Board &source, bool toAdd){
    // For each variable, you want to add to the state vector, use emplace_back:
    vector<U8> state;
    state.emplace_back(source.data.b_rook_1);
    state.emplace_back(source.data.b_rook_2);
    state.emplace_back(source.data.b_king);
    state.emplace_back(source.data.b_bishop);
    state.emplace_back(source.data.b_pawn_1);
    state.emplace_back(source.data.b_pawn_2);
    state.emplace_back(source.data.w_rook_1);
    state.emplace_back(source.data.w_rook_2);
    state.emplace_back(source.data.w_king);
    state.emplace_back(source.data.w_bishop);
    state.emplace_back(source.data.w_pawn_1);
    state.emplace_back(source.data.w_pawn_2);

    if(source.data.board_type!=SEVEN_THREE){
        state.emplace_back(source.data.b_pawn_3);
        state.emplace_back(source.data.b_pawn_4);
        state.emplace_back(source.data.w_pawn_3);
        state.emplace_back(source.data.w_pawn_4);
    }
    if(source.data.board_type==EIGHT_TWO){

        state.emplace_back(source.data.b_knight_1);
        state.emplace_back(source.data.b_knight_2);
        state.emplace_back(source.data.w_knight_1);
        state.emplace_back(source.data.w_knight_2);
    }
    if(stateMap.find(state)!=stateMap.end() && stateMap[state]>=2){
        //cout<<"stateMap : "<<stateMap[state]<<endl;
        return false;
    }
    else if(toAdd){
        if(stateMap.find(state)==stateMap.end())stateMap[state]=1;
        else stateMap[state]+=1;
    }
    return true;

}
int evaluatePosition1(int i, int j, const Board& board, PlayerColor player)
{
    U8 piece = board.data.board_0[pos(i,j)];

    int pawnPositionScore[8][8] = {
        { 10, 10,  0, 200, 200, 200, 200,  0 },
        { 10, 15,  0, 200, 200, 200, 200,  0 },
        { 20, 25,  0,  0,    0, 200, 200,  0 },
        { 30, 35,  0,  0,    0, 200,  200,  0 },
        { 40, 45,  0,  0,    0, 200,  200,  0 },
        { 50, 55, 80, 90,  200, 200,  200,  0 },
        { 60, 70, 80, 90,  200, 200,  200,  0 },
        {  0,  0,  0,  0,  0,   0,    0, 0}
    };
    int rookPositionScore[8][8] = {
        { 100, 100,  100,  90,  0,  10,  15,  0 },
        { 100, 100,  100,  90, 0,  15, 15,  0 },
        { 100, 100,   0,  0,  0,  20, 20,  0 },
        { 100, 100,   0,  0,  0,  35, 35,  0 },
        { 100, 100,   0,  0,  0,  50, 50,  0 },
        { 100, 100, 100, 90, 80,  70, 70,  0 },
        { 100, 100, 100, 90, 80,  70, 70,  0 },
        { 0,  0,  0,  0,  0,  0,  0, 0}
    };
    int bishopPositionScore[8][8] = {
        { 0, 40, 0,  0,  0,  30,  0,  0 },
        { 40, 0, 80,  0, 20,  0, 30,  0 },
        { 0, 50,  0,  0,  0, 50,  0,  0 },
        { 50, 0,  0,  0,  0,  0, 50,  0 },
        { 0, 50,  0,  0,  0, 50,  0,  0 },
        { 30, 0, 30,  0, 40,  0, 40,  0 },
        { 0, 30, 0, 40,  0, 40,  0,   0 },
        { 0,  0,  0,  0,  0,  0,  0, 0}
    };

    int kingPositionScore[8][8] = { //flip horizontally
        { 10, 0, 10,  0, 10,  0, 10,  0 },
        { 10, 30,  0,  10, 20,  10, 0, 0 },
        { 30, 10,  0,  0,  0,  0, 10,  0 },
        { 20, 30,  0,  0,  0,  10, 0,  0 },
        { 20, 10,  0,  0,  0,  0, 10,  0 },
        { 0,  10,  0, 10, 0, 10,  0,  0 },
        { 10,  0, 10, 0, 10,  0, 10,  0 },
        { 0,  0,  0,  0,  0,  0,  0,  0 }
    };

    PieceType pieceType = static_cast<PieceType>(piece & 0x1E); 
    PlayerColor pieceColor = static_cast<PlayerColor>(piece & (PlayerColor::WHITE | PlayerColor::BLACK)); 
    if(pieceColor==BLACK){
        i=6-i;
        j=6-j;
    }

    int scr = 0;
    switch (pieceType)
    {
        case PAWN:
            scr = 300+pawnPositionScore[j][i];
            break;
        case ROOK:
            scr = 1200+rookPositionScore[j][i];
            break;
        case BISHOP:
            scr = 800+bishopPositionScore[j][i];
            break;
        case KING:
            scr = 10000+kingPositionScore[j][i];
            break;
        default:
            break;
    }
    if(player!=pieceColor)scr*=-1;
    
    return scr;
}

int evaluatePosition2(int i, int j, const Board& board, PlayerColor player)
{
    U8 piece = board.data.board_0[pos(i,j)];

    PieceType pieceType = static_cast<PieceType>(piece & 0x1E); 
    PlayerColor pieceColor = static_cast<PlayerColor>(piece & (PlayerColor::WHITE | PlayerColor::BLACK)); 

    int scr = 0;
    switch (pieceType)
    {
        case PAWN:
            scr = 300;
            break;
        case ROOK:
            scr = 1200;
            break;
        case BISHOP:
            scr = 800;
            break;
        case KING:
            scr = 10000;
            break;
        default:
            break;
    }
    if(player!=pieceColor)scr*=-1;
    
    return scr;
}

int evaluatePosition3(int i, int j, const Board& board, PlayerColor player)
{
    U8 piece = board.data.board_0[pos(i,j)];

    PieceType pieceType = static_cast<PieceType>(piece & 0x1E); 
    PlayerColor pieceColor = static_cast<PlayerColor>(piece & (PlayerColor::WHITE | PlayerColor::BLACK)); 

    int scr = 0;
    switch (pieceType)
    {
        case PAWN:
            scr = 300;
            break;
        case ROOK:
            scr = 1200;
            break;
        case BISHOP:
            scr = 800;
            break;
        case KING:
            scr = 10000;
            break;
        default:
            break;
    }
    if(player!=pieceColor)scr*=-1;
    
    return scr;
}

int newEvaluate(const Board &board, PlayerColor player){
    int pieceScore = 0;

    if (board.data.board_type == SEVEN_THREE) {
        pieceScore += black_rook_1[board.data.b_rook_1];
        pieceScore += black_rook_2[board.data.b_rook_2];
        pieceScore += black_king[board.data.b_king];
        pieceScore += black_bishop[board.data.b_bishop];
        pieceScore += black_pawn_1[board.data.b_pawn_1];
        pieceScore += black_pawn_2[board.data.b_pawn_2];

        pieceScore -= white_rook_1[board.data.w_rook_1];
        pieceScore -= white_rook_2[board.data.w_rook_2];
        pieceScore -= white_king[board.data.w_king];
        pieceScore -= white_bishop[board.data.w_bishop];
        pieceScore -= white_pawn_1[board.data.w_pawn_1];
        pieceScore -= white_pawn_2[board.data.w_pawn_2];
    }
    else if(board.data.board_type == EIGHT_FOUR){

        pieceScore += bblack_rook_1[board.data.b_rook_1];
        pieceScore += bblack_rook_2[board.data.b_rook_2];
        pieceScore += bblack_king[board.data.b_king];
        pieceScore += bblack_bishop[board.data.b_bishop];
        pieceScore += bblack_pawn_1[board.data.b_pawn_1];
        pieceScore += bblack_pawn_2[board.data.b_pawn_2];
        pieceScore += bblack_pawn_3[board.data.b_pawn_3];
        pieceScore += bblack_pawn_4[board.data.b_pawn_4];

        pieceScore -= bwhite_rook_1[board.data.w_rook_1];
        pieceScore -= bwhite_rook_2[board.data.w_rook_2];
        pieceScore -= bwhite_king[board.data.w_king];
        pieceScore -= bwhite_bishop[board.data.w_bishop];
        pieceScore -= bwhite_pawn_1[board.data.w_pawn_1];
        pieceScore -= bwhite_pawn_2[board.data.w_pawn_2];
        pieceScore -= bwhite_pawn_3[board.data.w_pawn_3];
        pieceScore -= bwhite_pawn_4[board.data.w_pawn_4];

    }
    else{
        pieceScore += cblack_rook_1[board.data.b_rook_1];
        pieceScore += cblack_rook_2[board.data.b_rook_2];
        pieceScore += cblack_king[board.data.b_king];
        pieceScore += cblack_bishop[board.data.b_bishop];
        pieceScore += cblack_pawn_1[board.data.b_pawn_1];
        pieceScore += cblack_pawn_2[board.data.b_pawn_2];
        pieceScore += cblack_pawn_3[board.data.b_pawn_3];
        pieceScore += cblack_pawn_4[board.data.b_pawn_4];

        pieceScore -= cwhite_rook_1[board.data.w_rook_1];
        pieceScore -= cwhite_rook_2[board.data.w_rook_2];
        pieceScore -= cwhite_king[board.data.w_king];
        pieceScore -= cwhite_bishop[board.data.w_bishop];
        pieceScore -= cwhite_pawn_1[board.data.w_pawn_1];
        pieceScore -= cwhite_pawn_2[board.data.w_pawn_2];
        pieceScore -= cwhite_pawn_3[board.data.w_pawn_3];
        pieceScore -= cwhite_pawn_4[board.data.w_pawn_4];
    }
    if(board.data.player_to_play==WHITE)pieceScore=-pieceScore;
    return pieceScore;

}

int evaluate(const Board &board, PlayerColor player)
{
    return newEvaluate(board, player);
    int evaluation = 0;
    //position score
    int positionScore = 0;
    if(board.data.board_type==SEVEN_THREE){
        for(int i=0; i<7; i++){
            for(int j=0; j<7; j++){
                if(i>1 && j>1 && j<5 && i<5)continue;
                positionScore += evaluatePosition1(i,j, board, player);
            }
        } 
    } 
    else if(board.data.board_type==EIGHT_FOUR){
        for(int i=0; i<7; i++){
            for(int j=0; j<7; j++){
                if(i>1 && j>1 && j<5 && i<5)continue;
                positionScore += evaluatePosition2(i,j, board, player);
            }
        } 
    }  
    else {
        for(int i=0; i<7; i++){
            for(int j=0; j<7; j++){
                if(i>1 && j>1 && j<5 && i<5)continue;
                positionScore += evaluatePosition3(i,j, board, player);
            }
        } 
    }
    evaluation+=positionScore;

    return evaluation;
}



int minimax(const Board& board, int depth, int alpha, int beta, PlayerColor player) {
    nodes++;
    if (depth == 0) {
        // Base case: evaluate the current board position
        return evaluate(board, player);
    }
    auto moveset = board.get_legal_moves();

    std::vector<U16> movess;
    for(auto it : moveset){
        movess.push_back(it);
    }

    // // Sort the moves using the custom sorting function
    // std::sort(movess.begin(), movess.end(), [&board](const U16& move1, const U16& move2) {
    //     return sortByOpponentPieceValue(move1, move2, board);
    // });


    bool inCheck = board.in_check();

    if(moveset.size()==0){
        if(inCheck){
            if(board.data.player_to_play==player)return std::numeric_limits<int>::min()/2 - depth;
            else return std::numeric_limits<int>::max()/2 - depth;
        }
        else return 0;
    }

    if (player == board.data.player_to_play) {
        int max_eval = std::numeric_limits<int>::min();
        for (auto move : movess) {
            // Simulate the move
            Board new_board = Board(board); // Make a copy of the board
            new_board.do_move_(move);

            int eval;
            eval = minimax(new_board, depth - 1, alpha, beta, player);
            max_eval = std::max(max_eval, eval);
            alpha = std::max(alpha, eval);

            if (beta <= alpha) {
                break; // Beta cut-off
            }
        }
        return max_eval;
    } else {
        int min_eval = std::numeric_limits<int>::max();
        for (auto move : movess) {
            // Simulate the move
            Board new_board = Board(board);
            new_board.do_move_(move);
            int eval;
            eval = minimax(new_board, depth - 1, alpha, beta, player);
            min_eval = std::min(min_eval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha) {
                break; // Alpha cut-off
            }
        }
        return min_eval;
    }
}

void Engine::find_best_move(const Board& b) {

    // pick a random move
    addState(b, true);

    // Start measuring time
    auto start_time = std::chrono::high_resolution_clock::now();
    auto moveset = b.get_legal_moves();
    if (moveset.size() == 0) {
        std::cout << "Could not get any moves from board!\n";
        std::cout << board_to_str(&b.data);
        this->best_move = 0;
    }
    else {
        
        std::vector<U16> moves;
        std::cout << show_moves(&b.data, moveset) << std::endl;
        for (auto m : moveset) {
            std::cout << move_to_str(m) << " ";
        }
        std::cout << std::endl;
        std::sample(
            moveset.begin(),
            moveset.end(),
            std::back_inserter(moves),
            1,
            std::mt19937{std::random_device{}()}
        );
        this->best_move = moves[0];
        std::vector<U16> movess;
        for(auto it : moveset){
            movess.push_back(it);
        }
        // std::sort(movess.begin(), movess.end(), [&b](const U16& move1, const U16& move2) {
        //     return sortByOpponentPieceValue(move1, move2, b);
        // });
        int max_eval = std::numeric_limits<int>::min();
        nodes=0;
        for (auto move : movess) {
            // Simulate the move
            Board new_board =  Board(b);
            new_board.do_move_(move);
            int eval = minimax(new_board, /* depth */ 3, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), b.data.player_to_play);
            bool flag = addState(new_board, false);
            if (eval > max_eval && flag) {
                max_eval = eval;
                best_move = move;
            }
            else if(!flag && max_eval<0){
                best_move = move;
            }
        }

        Board new_board =  Board(b);
        new_board.do_move_(best_move);
        addState(new_board, true);

    }
    // Stop measuring time
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    std::chrono::duration<double> elapsed_time = end_time - start_time;

    // Convert duration to seconds and output the result
    std::cout << "Time taken: " << elapsed_time.count() << " seconds, nodes"<< nodes<< std::endl;

    // just for debugging, to slow down the moves
    // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}
