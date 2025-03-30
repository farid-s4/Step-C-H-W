#include <iostream>
#include <windows.h> // user input wsad
#include<ctime> // time(NULL)
#include<cstdlib> // srand() rand()
#include <conio.h>


enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Coordinate
{
    int x;
    int y;
};

int fieldWidth, fieldHeight;


bool isValidFieldSize(int value)
{
    return value>= 10 && value <= 100;
}

void FieldInput()
{
    do
    {
        std::cout<< "Enter the width of the field [10-100]";
        std::cin>>fieldWidth;

        if (!isValidFieldSize(fieldWidth))
        {
            std::cout<< "Invalid input! Width must be between 10 and 100\n";
        }
        
    }
    while (!isValidFieldSize(fieldWidth));

    do
    {
        std::cout<< "Enter the height of the field [10-100]";
        std::cin>>fieldHeight;

        if (!isValidFieldSize(fieldHeight))
        {
            std::cout<< "Invalid input! Height must be between 10 and 100\n";
        }
        
    }
    while (!isValidFieldSize(fieldHeight));
}

char** CreateField()
{
    char** field = new char*[fieldHeight];
    for (int i = 0; i < fieldHeight; ++i)
    {
        field[i] = new char[fieldWidth];
        for (int j = 0; j < fieldWidth; ++j)
        {
            if (i == 0 || i == fieldHeight - 1 || j == 0 || j == fieldWidth - 1)
            {
                field[i][j] = '#';
            }
            else
            {
                field[i][j] = ' ';
            }
        }
    }
    return field;
}

void DeleteField(char** field)
{
    for (int i = 0; i < fieldHeight; ++i)
    {
        delete[] field[i];
    }

    delete[] field;
}

void DrawField(char** field)
{
    system("cls");

    for (int i = 0; i < fieldHeight; ++i)
    {
        for (int j = 0; j < fieldWidth; ++j)
        {
            std::cout<< field[i][j];
        }std::cout<<"\n";
    }
}

void GenerateFood(char** field, Coordinate& food)
{
    food.x = rand() % (fieldWidth - 2) + 1;
    food.y = rand() % (fieldHeight - 2) + 1;

    field[food.y][food.x] = '*';
}

void UpdateField(char** field, const Coordinate* snake, int snakeLength, const Coordinate& food)
{
    for (int i = 0; i < fieldHeight; ++i)
    {
        for (int j = 0; j < fieldWidth; ++j)
        {
            if (field[i][j] != '*' && field[i][j] != '#')
            {
                field[i][j] = ' ';
            }
        }
    }
    
    for (int i = 0; i < snakeLength; ++i)
    {
        field[snake[i].y][snake[i].x] = 'O';
    }

    field[food.y][food.x] = '*';
}

void MoveSnake(Coordinate* snake, int& snakeLength, Direction dir)
{
    Coordinate newHead = snake[0];
    switch (dir)
    {
        case UP:    newHead.y--; break;
        case DOWN:  newHead.y++; break;
        case LEFT:  newHead.x--; break;
        case RIGHT: newHead.x++; break;
    }

    for (int i = snakeLength - 1; i > 0; --i)
    {
        snake[i] = snake[i - 1];
    }

    snake[0] = newHead;
}

bool CheckCollisions(const Coordinate* snake, int snakeLength)
{
    if(snake[0].x < 0 || snake[0].x >= fieldWidth || snake[0].y < 0 || snake[0].y >= fieldHeight)
    {
        return true;
    }

    for (int i = 1; i < snakeLength; ++i)
    {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
        {
            return true;
        }
    }

    return false;
}

void GrowSnake(Coordinate*& snake, int& snakeLength)
{
    Coordinate* tempSnake = new Coordinate[snakeLength + 1];
    for (int i = 0; i < snakeLength; ++i)
    {
        tempSnake[i] = snake[i];
    }
    delete[] snake;
    snake = tempSnake;
    snakeLength++;
}

Direction GetUserInput()
{
    
    if (_kbhit())
    {
        char input = _getch();
        if (input == 'w') return UP;
        if (input == 's') return DOWN;
        if (input == 'a') return LEFT;
        if (input == 'd') return RIGHT;
    }

    //return RIGHT;
}

void GameLoop(char** field, Coordinate*& snake, int& snakeLength, Coordinate& food)
{
    Direction dir = RIGHT;
    bool gameOver = false;

    while (!gameOver)
    {
        DrawField(field);
        UpdateField(field, snake, snakeLength, food);
        
        MoveSnake(snake, snakeLength, dir);

        if (CheckCollisions(snake, snakeLength))
        {
            gameOver = true;
            std::cout<<"Game over!\n";
            break;
        }

        if (snake[0].x == food.x && snake[0].y == food.y)
        {
            GrowSnake(snake, snakeLength);
            GenerateFood(field, food);
        }

        dir = GetUserInput();
        Sleep(100);
    }
}



void InitGame()
{
    FieldInput();
    char** field = CreateField();
    int snakeLength = 1;
    Coordinate* snake = new Coordinate[snakeLength];
    snake[0] = {fieldWidth/2, fieldHeight/2};

    Coordinate food;
    GenerateFood(field, food);
    GameLoop(field, snake, snakeLength, food);
    delete[] snake;
    DeleteField(field);
    
}




int main()
{
    InitGame();
    // fieldHeight = 10;
    // fieldWidth = 10;
    //FieldInput();
    // char** field = CreateField();
    // DrawField(field);
    return 0;
}