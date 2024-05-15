#include<iostream>
#include<string>
#include "Board.h"

int main() {
    int width, height, num_mines;
    std::string mode;
    std::cout << "Enter game mode: EASY, MEDUIM OR HARD: ";
    std::cin >> mode;
    while (mode != "EASY" && mode != "MEDUIM" && mode != "HARD"){
        std::cout << "ERROR!!!! Enter correct mode in ALL CAPSs: \n";
        std::cout << "Enter game mode: EASY, MEDUIM OR HARD: ";
        std::cin >> mode;
    }
    if (mode == "EASY"){
        width = 10;
        height = 8;
        num_mines= 10;
    }else if (mode == "MEDUIM"){
        width = 18;
        height = 14;
        num_mines= 40;
    }else{
        width = 24;
        height = 20;
        num_mines= 99;
    }
    Board mines(height, width, num_mines);
    mines.revealed_board();
    int row, coln;
    std::cout << "Enter a row and colunm to dig: ";
     std::cin >> row >> coln;
    mines.place_mines(row, coln);
    mines.update_count();
    bool haveWon, haveLost;
    mines.recurse_tile(row, coln);
    haveWon = mines.have_won(row, coln);
    haveLost = mines.have_lost(row, coln);
    while ((!haveWon) && (!haveLost)){
        mines.revealed_board();
        std::cout << "Enter a row and colunm to dig: ";
        std::cin >> row >> coln;
        mines.recurse_tile(row, coln);
        haveWon = mines.have_won(row, coln);
        haveLost = mines.have_lost(row, coln);
        
    }
    return 0;
}