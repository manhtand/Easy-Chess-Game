#ifndef board_hpp
#define board_hpp

#include <string>

enum class Color;
class Piece;

class Board
{
public:
    struct Pos
    {
        char col;
        int row;
    };
    
    struct Move
    {
        Pos before;
        Pos after;
    };
    
    Board();
    
    ~Board();
    
    Board(const Board& board);
    
    bool checkColor(bool playerTurn, Move move);
    
    void initBoard();
    
    void printBoard();
    
    void play(const Board& board);
    
    Piece*** TYP;
    
    int checkKing(const Board &board);
    
    bool checkInput(std::string input);


private:
    const int edge = 8;
    void makeMove(Move move);
    struct Move declareMove(std::string input);
};


#endif /* board_hpp */
