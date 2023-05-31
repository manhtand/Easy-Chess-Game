#include "board.hpp"
#include <iostream>
#include <iomanip>
#include <array>
#include <string>
#include "piece.hpp"

using std::setw;
using std::right;

Board::Board()
{
    initBoard();
    printBoard();
}

Board::~Board()
{
    for (int r = 0; r < edge; r++)
    {
        for (int c = 0; c < edge; c++)
        {
            delete [] TYP[r][c];
        }
        delete [] TYP[r];
    }
    delete [] TYP;
}

Board::Board(const Board& board)
{
    TYP = new Piece** [edge];
    for (int r = 0; r < edge; r++)
    {
        TYP[r] = new Piece* [edge];
    }
    TYP = board.TYP;
}

void Board::initBoard()
{
    TYP = new Piece** [edge];
    for (int r = 0; r < edge; r++)
    {
        TYP[r] = new Piece* [edge];
        for (int c = 0; c < edge; c++)
        {
            TYP[r][c] = nullptr;
        }
    }
    
    for (int r = 0; r < edge; r++)
    {
        for (int c = 0; c < edge; c++)
        {
            if (r == 1)
            {
                TYP[r][c] = new Pawn(Color::Black);
            }
            else if (r == 6)
            {
                TYP[r][c] = new Pawn(Color::White);
            }
            else if (r == 0)
            {
                if ((c == 0)||(c==7))
                {
                    TYP[r][c] = new Rook(Color::Black);
                }
                else if ((c == 1)||(c == 6))
                {
                    TYP[r][c] = new Knight(Color::Black);
                }
                else if ((c == 2)||(c == 5))
                {
                    TYP[r][c] = new Bishop(Color::Black);
                }
                else if (c == 3)
                {
                    TYP[r][c] = new Queen(Color::Black);
                }
                else
                {
                    TYP[r][c] = new King(Color::Black);
                }
            }
            else if (r == 7)
            {
                if ((c == 0)||(c == 7))
                {
                    TYP[r][c] = new Rook(Color::White);
                }
                else if ((c == 1)||(c == 6))
                {
                    TYP[r][c] = new Knight(Color::White);
                }
                else if ((c == 2)||(c == 5))
                {
                    TYP[r][c] = new Bishop(Color::White);
                }
                else if (c == 3)
                {
                    TYP[r][c] = new Queen(Color::White);
                }
                else
                {
                    TYP[r][c] = new King(Color::White);
                }
            }
            else
            {
                TYP[r][c] = new Piece("------", Color::Empty);
            }
        }
    }
}

void Board::printBoard()
{
    std::cout << setw(6) << right << "a" << setw(7) << right << "b" << setw(7) << right << "c" << setw(7) << right << "d" << setw(7) << right << "e" << setw(7) << right << "f" << setw(7) << right << "g" << setw(7) << right << "h" << std::endl;
    for (int r = 0; r < edge; r++)
    {
        std::cout << 8 - r << " ";
        for (int c = 0; c < edge; c++)
        {
            std::cout << setw(7) << TYP[r][c] -> toString();
        }
        std::cout << setw(3) << 8 - r << std::endl;
    }
    std::cout << setw(6) << right << "a" << setw(7) << right << "b" << setw(7) << right << "c" << setw(7) << right << "d" << setw(7) << right << "e" << setw(7) << right << "f" << setw(7) << right << "g" << setw(7) << right << "h" << std::endl << std::endl;
}

Board::Move Board::declareMove(std::string input)
{
    Board::Move move;
    move.before.col = static_cast<int>(input[0] - 'a');
    move.before.row = 7 - static_cast<int>(input[1] - 49);
    move.after.col = static_cast<int>(input[2] - 'a');
    move.after.row = 7 - static_cast<int>(input[3] - 49);

    return move;
}

void Board::makeMove(Board::Move move)
{
    if (TYP[move.after.row][move.after.col] -> toString() != "------")
    {
        std::cout << TYP[move.after.row][move.after.col] -> toString() << " is defeated." << std::endl;
    }
    delete TYP[move.after.row][move.after.col];
    TYP[move.after.row][move.after.col] = TYP[move.before.row][move.before.col];
    TYP[move.before.row][move.before.col] = new Piece {"------", Color::Empty};
}

void Board::play(const Board& board)
{
    bool playerTurn = 1;
    std::string player;
    std::cout << "Move: with a2a5 moves the figure from a2 to a5" << std::endl;
    while (1)
    {
        if (playerTurn)
        {
            player = "White";
        }
        else
        {
            player = "Black";
        }
        std::cout << player << "'s turn: ";
        std::string input;
        std::cin >> input;
        
        Move playerMove;
        
        if (checkInput(input))
        {
            playerMove = declareMove(input);
        }
        
        if (checkColor(playerTurn, playerMove) == 1)
        {
            if ((TYP[playerMove.before.row][playerMove.before.col] -> isMovePossible(*this, playerMove) == 0) && (TYP[playerMove.after.row][playerMove.after.col] -> isMovePossible(*this, playerMove) == 0))
            {
                std::cout << "Invalid. Try again." << std::endl;
                continue;
            }
        }
        
        if (checkColor(playerTurn, playerMove) == 0)
        {
            std::cout << "Invalid. Try again." << std::endl;
            continue;
        }
        playerTurn = !playerTurn;
        makeMove(playerMove);
        printBoard();
        
        int gameStatus = checkKing(board);
        switch (gameStatus)
        {
            case(1):
                std::cout << "White wins." << std::endl;
                delete [] TYP;
                break;
            case(2):
                std::cout << "Black wins." << std::endl;
                delete [] TYP;
                break;
        }
        if (gameStatus)
        {
            break;
        }
    }
}

bool Board::checkColor(bool playerTurn, Move move)
{
    if (playerTurn == 1)
    {
        return TYP[move.before.row][move.before.col] -> isWhite();
    }
    else
    {
        return TYP[move.before.row][move.before.col] -> isBlack();
    }
}

int Board::checkKing(const Board &board)
{
    int i = 3;
    for (int r = 0; r < edge; r++)
    {
        for (int c = 0; c < edge; c++)
        {
            if (board.TYP[r][c] -> toString() == "w_King")
            {
                i -= 2;
            }
            if (board.TYP[r][c] -> toString() == "b_King")
            {
                i -= 1;
            }
        }
    }
    return i;
}

bool Board::checkInput(std::string input)
{
    int col1 = static_cast<int>(input[0] - 'a');
    int row1 = 7 - static_cast<int>(input[1] - 49);
    int col2 = static_cast<int>(input[2] - 'a');
    int row2 = 7 - static_cast<int>(input[3] - 49);
    
    if ((col1 >= 0) && (col1 < edge) && (row1 >= 0) && (row1 < edge) && (col2 >= 0) && (col2 < edge) && (row2 >= 0) && (row2 < edge))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
