#include "piece.hpp"
#include <iostream>
#include <string>

Piece::Piece(const std::string& displayString, Color color) : displayString(displayString), color(color)
{}

bool Piece::isWhite() const
{
    return (color == Color::White);
}

bool Piece::isBlack() const
{
    return (color == Color::Black);
}

bool Piece::isEmpty() const
{
    return (color == Color::Empty);
}

std::string Piece::toString() const
{
    if (color == Color::White)
    {
        return "w_" + displayString;
    }
    if (color == Color::Black)
    {
        return "b_" + displayString;
    }
    return displayString;
}

Color Piece::getColor() const
{
    return color;
}

bool Piece::isMovePossible(const Board &board, const Board::Move &move)
{
    bool startPiece = 1;
    bool friendPiece = 1;
    bool noCollision = 1;
    bool figuresMove = 1;
    
    int row1 = move.before.row;
    int col1 = move.before.col;
    int row2 = move.after.row;
    int col2 = move.after.col;
    
    startPiece = !(board.TYP[row1][col1] -> isEmpty());
    
    if (board.TYP[row1][col1] -> getColor() == board.TYP[row2][col2] -> getColor())
    {
        friendPiece = 0;
    }
    
    if ((board.TYP[row1][col1] -> toString() == "w_Rook") || (board.TYP[row1][col1] -> toString() == "b_Rook"))
    {
        if (row1 == row2)
        {
            if (col1 < col2)
            {
                for (int i = col2 - 1; i > col1; i--)
                {
                    if (board.TYP[row1][i] -> isEmpty() == 0)
                    {
                        noCollision = 0;
                        break;
                    }
                }
            }
            if (col1 > col2)
            {
                for (int i = col1 - 1; i > col2; i--)
                {
                    if (board.TYP[row1][i] -> isEmpty() == 0)
                    {
                        noCollision = 0;
                        break;
                    }
                }
            }
        }
        if (col1 == col2)
        {
            if (row1 < row2)
            {
                for (int i = row2 - 1; i > row1; i--)
                {
                    if (board.TYP[i][col1] -> isEmpty() == 0)
                    {
                        noCollision = 0;
                        break;
                    }
                }
            }
            if (row1 > row2)
            {
                for (int i = row2 + 1; i < row1; i++)
                {
                    if (board.TYP[i][col1] -> isEmpty() == 0)
                    {
                        noCollision = 0;
                        break;
                    }
                }
            }
        }
        figuresMove = ((row1 == row2) || (col1 == col2)) && noCollision;
    }
    
    if ((board.TYP[row1][col1] -> toString() == "w_Bshp") || (board.TYP[row1][col1] -> toString() == "b_Bshp"))
    {
        if ((row2 < row1) && (col2 > col1))
        {
            for (int i = 1; i < row1 - row2; i++)
            {
                if (board.TYP[row1 - i][col1 + i] -> isEmpty() == 0)
                {
                    noCollision = 0;
                    break;
                }
            }
        }
        if ((row2 < row1) && (col2 < col1))
        {
            for (int i = 1; i < row1 - row2; i++)
            {
                if (board.TYP[row1 - i][col1 - i] -> isEmpty() == 0)
                {
                    noCollision = 0;
                    break;
                }
            }
        }
        if ((row2 > row1) && (col2 > col1))
        {
            for (int i = 1; i < row2 - row1; i++)
            {
                if (board.TYP[row1 + i][col1 + 1] -> isEmpty() == 0)
                {
                    noCollision = 0;
                    break;
                }
            }
        }
        if ((row2 > row1) && (col2 < col1))
        {
            for (int i = 1; i < row2 - row1; i++)
            {
                if (board.TYP[row1 + i][col1 - i] -> isEmpty() == 0)
                {
                    noCollision = 0;
                    break;
                }
            }
        }
        
        figuresMove = (((row2 - row1) / (col2 - col1) == 1) or ((row2 - row1) / (col2 - col1) == -1)) && noCollision;
    }
    
    if ((board.TYP[row1][col1] -> toString() == "w_Kght") || (board.TYP[row1][col1] -> toString() == "b_Kght"))
    {
        figuresMove = 0;
        for (int i = -2; i < 3; i += 4)
        {
            for (int j = -1; j < 2; j += 2)
            {
                if ((row1 + i == row2) && (col1 + j == col2))
                {
                    figuresMove = 1;
                }
                if ((row1 + j == row2) && (col1 + i == col2))
                {
                    figuresMove = 1;
                }
            }
        }
    }
    
    
    if ((board.TYP[row1][col1] -> toString() == "w_Quen") || (board.TYP[row1][col1] -> toString() == "b_Quen"))
    {
        if ((row2 < row1) && (col2 > col1))
        {
            for (int i = 1; i < row1 - row2; i++)
            {
                if (board.TYP[row1 - i][col1 + i] -> isEmpty() == 0)
                {
                    noCollision = 0;
                    break;
                }
            }
            figuresMove = (((row2 - row1) / (col2 - col1) == 1) or ((row2 - row1) / (col2 - col1) == -1)) && noCollision;
        }
        if ((row2 < row1) && (col2 < col1))
        {
            for (int i = 1; i < row1 - row2; i++)
            {
                if (board.TYP[row1 - i][col1 - i] -> isEmpty() == 0)
                {
                    noCollision = 0;
                    break;
                }
            }
            figuresMove = (((row2 - row1) / (col2 - col1) == 1) or ((row2 - row1) / (col2 - col1) == -1)) && noCollision;
        }
        if ((row2 > row1) && (col2 > col1))
        {
            for (int i = 1; i < row2 - row1; i++)
            {
                if (board.TYP[row1 + i][col1 + 1] -> isEmpty() == 0)
                {
                    noCollision = 0;
                    break;
                }
            }
            figuresMove = (((row2 - row1) / (col2 - col1) == 1) or ((row2 - row1) / (col2 - col1) == -1)) && noCollision;
        }
        if ((row2 > row1) && (col2 < col1))
        {
            for (int i = 1; i < row2 - row1; i++)
            {
                if (board.TYP[row1 + i][col1 - i] -> isEmpty() == 0)
                {
                    noCollision = 0;
                    break;
                }
            }
            figuresMove = (((row2 - row1) / (col2 - col1) == 1) or ((row2 - row1) / (col2 - col1) == -1)) && noCollision;
        }
        if (row1 == row2)
        {
            if (col1 < col2)
            {
                for (int i = col2 - 1; i > col1; i--)
                {
                    if (board.TYP[row1][i] -> isEmpty() == 0)
                    {
                        noCollision = 0;
                        break;
                    }
                }
            }
            if (col1 > col2)
            {
                for (int i = col1 - 1; i > col2; i--)
                {
                    if (board.TYP[row1][i] -> isEmpty() == 0)
                    {
                        noCollision = 0;
                        break;
                    }
                }
            }
            figuresMove = ((row1 == row2) || (col1 == col2)) && noCollision;
        }
        if (col1 == col2)
        {
            if (row1 < row2)
            {
                for (int i = row2 - 1; i > row1; i--)
                {
                    if (board.TYP[i][col1] -> isEmpty() == 0)
                    {
                        noCollision = 0;
                        break;
                    }
                }
            }
            if (row1 > row2)
            {
                for (int i = row2 + 1; i < row1; i++)
                {
                    if (board.TYP[i][col1] -> isEmpty() == 0)
                    {
                        noCollision = 0;
                        break;
                    }
                }
            }
            figuresMove = ((row1 == row2) || (col1 == col2)) && noCollision;
        }
    }
    
    
    return (startPiece && friendPiece && figuresMove);
}


