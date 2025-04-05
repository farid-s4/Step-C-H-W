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
    virtual bool Movement(int x, int y) = 0;
    virtual ~Figure()
    {
        _x = 0;
        _y = 0;
    }
};

class Pawn : public Figure
{
    public:
    Pawn(int x, int y) : Figure(x, y) {}
    bool Movement(int x, int y) override
    {
        if (x==_x)
        {
            _y -= 1;
            return true;
        }
        return false;
    }
};
class Bishop : public Figure
{
    public:
    Bishop(int x, int y) : Figure(x, y) {}
    bool Movement(int x, int y) override
    {
        if (x == y)
        {
            _x = x;
            _y = y;
            return true;
        }
        return false;
    }
};
class Rook : public Figure
{
    public:
    Rook(int x, int y) : Figure(x, y) {}
    bool Movement(int x, int y) override
    {
        if (x == _x || y == _y || x == y)
        {
            _x = x;
            _y = y;
            return true;
        }
        return false;
    }
};
class Queen : public Figure
{
    public:
    Queen(int x, int y) : Figure(x, y) {}
    bool Movement(int x, int y) override
    {
        if (x == _x || y == _y || x == y)
        {
            _x = x;
            _y = y;
            return true;
        }
        return false;
    }
};
class King : public Figure
{
    public:
    King(int x, int y) : Figure(x, y) {}
    bool Movement(int x, int y) override
    {
        if ((x == _x + 1 || x == _x - 1 || x == _x) && (y == _y + 1 || y == _y - 1 || y == _y))
        {
            _x = x;
            _y = y;
            return true;
        }
        return false;
    }
};
class Knight : public Figure
{
    public:
    Knight(int x, int y) : Figure(x, y) {}
    bool Movement(int x, int y) override
    {
        if (x == _x -2 && y == _y - 1 || x == _x + 2 && y == _y + 1 || x == _x -1 && y == _y - 2 || x == _x + 1 && y == _y + 2 )
        {
            _x = x;
            _y = y;
            return true;
        }
        return false;
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
while (true)
{
    char board[8][8];
    UpdateBoard(board);
    int x = 0, y = 0;
    int figChoice = 0;

    std::cout << "\nEnter coordinates for the figure (x y): ";
    std::cin >> x >> y;

    std::cout << "Choose figure:\n";
    std::cout << "1 - Knight\n2 - Bishop\n3 - Rook\n4 - King\n5 - Queen\n6 - Pawn\n";
    std::cin >> figChoice;

    int newX = 0, newY = 0;
    std::cout << "Enter new position to move (x y): ";
    std::cin >> newX >> newY;
    std::cout << "\nPlacing figure...\n";
    switch (figChoice) {
        case 1: {
            Knight knight(x, y);
            board[x][y] = 'P'; 
            PrintBoard(board);
            if (knight.Movement(newX, newY)) {
                UpdateBoard(board);
                board[newX][newY] = 'P';
                std::cout << "The figure knight moved.\n";
                PrintBoard(board);
            } else {
                std::cout << "Write correct coordinate\n";
            }
            break;
        }

        case 2: {
            Bishop bishop(x, y);
            board[x][y] = 'B';
            PrintBoard(board);
            if (bishop.Movement(newX, newY)) {
                UpdateBoard(board);
                board[newX][newY] = 'B';
                std::cout << "The figure bishop moved.\n";
                PrintBoard(board);
            } else {
                std::cout << "Write correct coordinate\n";
            }
            break;
        }

        case 3: {
            Rook rook(x, y);
            board[x][y] = 'R';
            PrintBoard(board);
            if (rook.Movement(newX, newY)) {
                UpdateBoard(board);
                board[newX][newY] = 'R';
                std::cout << "The figure rook moved.\n";
                PrintBoard(board);
            } else {
                std::cout << "Write correct coordinate\n";
            }
            break;
        }

        case 4: {
            King king(x, y);
            board[x][y] = 'K';
            PrintBoard(board);
            if (king.Movement(newX, newY)) {
                UpdateBoard(board);
                board[newX][newY] = 'K';
                std::cout << "The figure king moved.\n";
                PrintBoard(board);
            } else {
                std::cout << "Write correct coordinate\n";
            }
            break;
        }

        case 5: {
            Queen queen(x, y);
            board[x][y] = 'Q';
            PrintBoard(board);
            if (queen.Movement(newX, newY)) {
                UpdateBoard(board);
                board[newX][newY] = 'Q';
                std::cout << "The figure queen moved.\n";
                PrintBoard(board);
            } else {
                std::cout << "Write correct coordinate\n";
            }
            break;
        }

        case 6: {
            Pawn pawn(x, y);
            board[x][y] = 'P';
            PrintBoard(board);
            if (pawn.Movement(newX, newY)) {
                UpdateBoard(board);
                board[newX][newY] = 'P';
                std::cout << "The figure pawn moved.\n";
                PrintBoard(board);
            } else {
                std::cout << "Write correct coordinate\n";
            }
            break;
        }

        default:
            std::cout << "Invalid choice!\n";
            break;
        }

}
}