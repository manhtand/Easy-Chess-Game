#include "piece.hpp"

Queen::Queen(Color color) : Piece("Quen", color)
{}

bool Queen::isMovePossible(Board &board, const Board::Move &move)
{
    bool noCollision = 1;
    bool figuresMove = 1;
    
    int row1 = move.before.row;
    int col1 = move.before.col;
    int row2 = move.after.row;
    int col2 = move.after.col;
    
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
    return figuresMove;
}
