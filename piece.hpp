#ifndef piece_hpp
#define piece_hpp

#include "board.hpp"
#include <string>

enum class Color
{
    White,
    Black,
    Empty
};


class Piece
{
public:
    
    Piece(const std::string& displayString, Color color);

  
    virtual ~Piece() = default;

  
    bool isWhite() const;

  
    bool isBlack() const;

  
    bool isEmpty() const;

  
    std::string toString() const;

  
    virtual bool isMovePossible(const Board& board, const Board::Move& move);
    
    const std::string displayString;

private:
    const Color color;
    Color getColor() const;
};

class Rook : public Piece
{
public:
    Rook(Color);
    bool isMovePossible(Board& board, const Board::Move& move);
};

class Bishop : public Piece
{
public:
    Bishop(Color);
    bool isMovePossible(Board& board, const Board::Move& move);
};

class Knight : public Piece
{
public:
    Knight(Color);
    bool isMovePossible(const Board::Move &move);
};

class Pawn : public Piece
{
public:
    Pawn(Color);
};

class Queen : public Piece
{
public:
    Queen(Color);
    bool isMovePossible(Board& board, const Board::Move& move);
};

class King : public Piece
{
public:
    King(Color);
};


#endif /* piece_hpp */
