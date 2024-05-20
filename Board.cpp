#include<iostream>
#include<string>
#include "Tile.h"
#include<cstdlib>
#include "Board.h"
#include<ctime>
#include<iomanip>
#include<array>

const std::string green_bg = "\033[42m";
const std::string red_bg = "\033[41m";
const std::string white_bg = "\037[47m";
const std::string brown_bg = "\033[48;2;60;29;10m"; // RGB: 139, 69, 19
const std::string black_bg = "\033[40m";
const std::string reset_color = "\033[0m";
const std::string blue_fg = "\033[34m";
const std::string red_fg = "\033[31m";
const std::string purple_fg = "\033[35m";
const std::string green_fg = "\033[36m";
const std::string white_fg = "\033[97m";

Board::Board(int m_height, int m_width, int num_mines){
    count = 0;
    height = m_height;
    width = m_width;
    mine_count = num_mines;
    lost = false;
    int size = (height * width);
    board = new tile [size];
    
        
}

bool Board::is_valid_mine_placement(int row, int coln, int random_rowNum, int random_colnNum) {
    // Check if the randomly chosen tile is not the first tile and its neighbors
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            int n = row + x;
            int m = coln + y;
            if (n == random_rowNum && m == random_colnNum) {
                return false;
            }
        }
    }

    // Ensure that the tile does not already contain a mine
    if (board[(width * random_rowNum) + random_colnNum].get_tileValue() == -1) {
        return false;
    }

    return true;
}


void Board::place_mines(int row, int coln){
    //function to create 10 random number numbers and place them randomly in an array. 
    //All tiles are set to zero and tiles with mines will be changes to "-1"
    srand(time(0));
    int i {0};
    while (i < mine_count){
        int random_rowNum {rand() %  (height)};
        int random_colnNum {rand() %  (width)};
        if (is_valid_mine_placement(row, coln, random_rowNum, random_colnNum)) {
            board[(width * random_rowNum) + random_colnNum].set_tileValue(-1);
            i++;
        }
    }
       
}

void Board::update_count() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // Skip counting if the current cell is a mine
            if (board[width*i+j].get_tileValue() != -1) {
                 // Count the number of mines in neighboring cells
                int m_count = 0;
                for (int x = -1; x <= 1; ++x) {
                    for (int y = -1; y <= 1; ++y) {
                        // Calculate neighbor coordinates
                        int n = i + x;
                        int m = j + y;
                        if (n >= 0 && n < height && m >= 0 && m < width && board[width *n +m].get_tileValue() == -1) {
                            m_count++;
                        }
                    }
                }
                // Update the current cell with the count
                board[width * i +j].set_tileValue(m_count);
            }
           
        }
    }
}

void Board::revealed_board(){
    //This method displays the board 
    //but just for this project, the location of the mines will be displayed

     // ANSI escape codes for colors
    for (int i=0; i< height; i++){
        std::cout << '|';

        for (int j{0}; j < width ; j++){
            std::cout << green_bg << white_fg;
            std::cout <<"---|";
            std::cout << reset_color;
        }
        std::cout << '\n';
        std::cout << '|';
        for (int j = 0; j < width ; j++){
            if (lost == true && board[width * i +j].get_tileValue() == -1){
                std::cout <<  std::setw(2) << red_bg << " M" <<" |";
            }
            else if (board[(width * i)+j].get_tileIsRevealed() == false ){
                std::cout <<  green_bg ;
                std::cout  <<  std::setw(2) << "  "  <<" |" ;
            }else if (board[width * i +j].get_tileValue() == 1){
                std::cout   <<  brown_bg << green_fg;
                 std::cout << std::right<< std::setw(2) << board[width * i +j].get_tileValue() << " |";
            }else if (board[width * i +j].get_tileValue() == 2){
                std::cout   <<  brown_bg << blue_fg;
                 std::cout << std::right<< std::setw(2) << board[width * i +j].get_tileValue() << " |";
            }else if (board[width * i +j].get_tileValue() == 3){
                std::cout   <<  brown_bg << red_fg;
                 std::cout << std::right<< std::setw(2) << board[width * i +j].get_tileValue() << " |";
            }else if (board[width * i +j].get_tileValue() == 4){
                std::cout   <<  brown_bg << purple_fg;
                 std::cout << std::right<< std::setw(2) << board[width * i +j].get_tileValue() << " |";
            }else {
                std::cout <<  brown_bg;
                std::cout << std::right<< std::setw(2) << "  " << " |";
            }
            std::cout << reset_color;
        }
        std ::cout << '\n';
    }
    std::cout << '|';
    for (int i{0}; i < width ; i++){
        std::cout << green_bg << white_fg;
        std::cout <<"---|";
        std::cout << reset_color;
        
    }std::cout << '\n';
}

bool Board::reveal_tile(int row, int coln){
    //to reveal the choosen tile.
    if ((board[(width * row) + coln].get_tileIsRevealed() != true)){
        board[(width * row) + coln].set_tileIsRevealed();
        return true;
    }     
    return false;
}


bool Board::have_won(int row, int coln){
    //To check if user has won the game
    if (count == (height * width - mine_count)){
        std::cout << "\nYOU HAVE WON!!!\n";
        std::cout << "Final Board\n";
        revealed_board();
        return true;
    }else {
        return false;
    }
}

bool Board::have_lost(int row, int coln){
    //To check if user has lost the game
    if (board[width * row + coln].get_tileValue() == -1){
        lost = true;
        std::cout << "\nYOU'VE LOST!!!!!!!\n";
        std::cout << "Final Board\n";
        revealed_board();
        return true;
    }else {
        return false;
    }
}

void Board::recurse_tile(int row, int coln) {
    // Check if the tile is already revealed or out of bounds
    if (row < 0 || row >= height || coln < 0 || coln >= width || board[(width * row) + coln].get_tileIsRevealed()) {
        return;
    }
    //  reveal the current tile.
    bool revealed = reveal_tile(row, coln);
    if (revealed) {
        count++;
    }
    // If the tile is a mine or has a non-zero value, stop recursion
    if (board[(width * row) + coln].get_tileValue() == -1 || board[(width * row) + coln].get_tileValue() >= 1) {
        return;
    }
    // If the tile value is 0, recursively reveal all neighboring tiles
    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            // Skip the current tile itself
            if (x == 0 && y == 0) {
                continue;
            }
            int newRow = row + x;
            int newColn = coln + y;

            // Check if new coordinates are within bounds
            if (newRow >= 0 && newRow < height && newColn >= 0 && newColn < width) {
                recurse_tile(newRow, newColn);
            }
        }
    }
}



Board::~Board() {
    // Deallocate memory for the board

    delete[] board;
}