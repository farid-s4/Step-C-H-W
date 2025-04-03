#include <iostream>

class Figure
{
protected:
    int _x;
    int _y;
public:
    
    Figure() : _x(0), _y(0){}
    Figure (int x, int y) :  _x(x), _y(y) {}
    Figure(const Figure &other)
    {

        _x = other._x;
        _y = other._y;
    }
    Figure &operator=(const Figure &other){ _x = other._x; _y = other._y; return *this; }
    int getX() const { return _x; }
    int getY() const { return _y; }
    void setX(int x){ _x = x; }
    void setY(int y){ _y = y; }
    virtual void Movement(int x, int y){}
};

class Pawn : public Figure
{
    public:
    Pawn(int x, int y) : Figure(x, y) {}
    void Movement(int x, int y) 
    {
        if (x==_x)
        {
            _y -= 1;
        }
    }
};
class Bishop : public Figure
{
    public:
    Bishop(int x, int y) : Figure(x, y) {}
    void Movement(int x, int y) override
    {
        if (x == y)
        {
            _x = x;
            _y = y;
        }
    }
};
class Rook : public Figure
{
    public:
    Rook(int x, int y) : Figure(x, y) {}
    void Movement(int x, int y) override
    {
        if (x == _x || y == _y || x == y)
        {
            _x = x;
            _y = y;
        }
    }
};
class Queen : public Figure
{
    public:
    Queen(int x, int y) : Figure(x, y) {}
    void Movement(int x, int y) override
    {
        if (x == _x || y == _y || x == y)
        {
            _x = x;
            _y = y;
        }
    }
};
class king : public Figure
{
    public:
    king(int x, int y) : Figure(x, y) {}
    void Movement(int x, int y) override
    {
        if ((x == _x + 1 || x == _x - 1 || x == _x) && (y == _y + 1 || y == _y - 1 || y == _y))
        {
            _x = x;
            _y = y;
        }
    }
};
class knight : public Figure
{
    public:
    knight(int x, int y) : Figure(x, y) {}
    void Movement(int x, int y) override
    {
        
    }
};

void UpdateBoard(char mass[8][8])
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0)
                mass[i][j] = '#';
            else
                mass[i][j] = '*'; 
        }
    }
}
void PrintBoard(char mass[8][8])
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << mass[i][j] << ' ';
        }
        std::cout << '\n';
    }
}
int main() {
    
    Queen queen( 4, 4);
    const int size = 8;
    char board[size][size];
    UpdateBoard(board);
    board[queen.getY()][queen.getX()] = '|';
    PrintBoard(board);

    queen.Movement(4, 1); 
    std::cout << '\n';
    UpdateBoard(board);
    board[queen.getY()][queen.getX()] = '|';
    PrintBoard(board);
    
    UpdateBoard(board);
    queen.Movement(7, 7);
    board[queen.getY()][queen.getX()] = '|';
    std::cout << '\n';
    PrintBoard(board);
    return 0;
}