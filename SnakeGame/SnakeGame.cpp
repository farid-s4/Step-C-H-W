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
int score, difficulty;
bool isValidFieldDifficulty(int value) {
    return value >= 1 && value <= 3;
}


bool isValidFieldSize(int value)
{
    return value >= 10 && value <= 100;
}

void FieldInput()
{
    do
    {
        std::cout << "Enter the width of the field [10-100]";
        std::cin >> fieldWidth;

        if (!isValidFieldSize(fieldWidth))
        {
            std::cout << "Invalid input! Width must be between 10 and 100\n";
        }

    } while (!isValidFieldSize(fieldWidth));

    do
    {
        std::cout << "Enter the height of the field [10-100]";
        std::cin >> fieldHeight;

        if (!isValidFieldSize(fieldHeight))
        {
            std::cout << "Invalid input! Height must be between 10 and 100\n";
        }

    } while (!isValidFieldSize(fieldHeight));
    do
    {
        std::cout << "Select difficulty level [1-3]";
        std::cin >> difficulty;
        if (!isValidFieldDifficulty(difficulty))
        {
            std::cout << "Invalid input! Difficulty must be between 1 and 3\n";
        }
    }
    while (!isValidFieldDifficulty(difficulty));
}

char** CreateField()
{
    char** field = new char* [fieldHeight];
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
            std::cout << field[i][j];
        }std::cout << "\n";
    }
}

void GenerateFood(char** field, Coordinate& food)
{
    food.x = rand() % (fieldWidth - 2) + 1;
    food.y = rand() % (fieldHeight - 2) + 1;

    field[food.y][food.x] = '*';
}
void GenerateBigFood(char** field, Coordinate& big_food)
{
    big_food.x = rand() % (fieldWidth - 2) + 1;
    big_food.y = rand() % (fieldHeight - 2) + 1;

    field[big_food.y][big_food.x] = '$';
}

void GenerateWool(char** field, Coordinate& wool)
{
    
    wool.x = rand() % (fieldWidth - 2) + 1;
    wool.y = rand() % (fieldHeight - 2) + 1;
    field[wool.y][wool.x] = '#';
    
}

void UpdateField(char** field, const Coordinate* snake, int snakeLength, const Coordinate& food, const Coordinate& big_food)
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
    field[big_food.y][big_food.x] = '$';
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

bool CheckCollisions(const Coordinate* snake, int snakeLength, const Coordinate& wool)
{
    if (snake[0].x < 0 || snake[0].x >= fieldWidth || snake[0].y < 0 || snake[0].y >= fieldHeight)
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
    if (snake[0].x  == wool.x && snake[0].y == wool.y)
    {
        return true;
    }
    return false;
}

void GrowSnake(Coordinate*& snake, int& snakeLength, int factor)
{
    if (factor == 1)
    {
        snakeLength++;
        Coordinate* tempSnake = new Coordinate[snakeLength];
        for (int i = 0; i < snakeLength - 1; ++i)
        {
            tempSnake[i] = snake[i];
        }
        tempSnake[snakeLength - 1] = tempSnake[snakeLength - 2];
        delete[] snake;
        snake = tempSnake;
        score += 10;
    }
    if (factor == 2)
    {
        snakeLength += 2;
        Coordinate* tempSnake = new Coordinate[snakeLength];
        for (int i = 0; i < snakeLength - 2; ++i) {
            tempSnake[i] = snake[i];
        }
        Coordinate tail = tempSnake[snakeLength - 3]; 
        tempSnake[snakeLength - 2] = tail;
        tempSnake[snakeLength - 1] = tail;

        delete[] snake;

        snake = tempSnake;

        score += 20;
    }
    
}
Direction userInput = UP;
Direction GetUserInput()
{
    
    if (_kbhit())
    {
        char input = _getch();
        if (input == 'w')
        {
            userInput = UP;
            return UP;
        }
        if (input == 's')
        {
            userInput = DOWN;
            return DOWN;
        }
        if (input == 'a')
        {
            userInput = LEFT;
            return LEFT;
        }
        if (input == 'd')
        {
            userInput = RIGHT;
            return RIGHT;
        }
    }
    
    return userInput;

}

void GameLoop(char** field, Coordinate*& snake, int& snakeLength, Coordinate& food , Coordinate& wool, Coordinate& big_food)
{

    bool gameOver = false;

    while (!gameOver)
    {

        Direction dir = GetUserInput();
        DrawField(field);
        UpdateField(field, snake, snakeLength, food, big_food);

        MoveSnake(snake, snakeLength, dir);
        if (CheckCollisions(snake, snakeLength, wool))
        {
            gameOver = true;
            std::cout << "Game over!\n";
            std::cout << "Score: " << score << "\n";
            break;
        }
        
        if (snake[0].x == food.x && snake[0].y == food.y)
        {
            GrowSnake(snake, snakeLength, 1);
            GenerateFood(field, food);
        }
        if (snake[0].x == big_food.x && snake[0].y == big_food.y)
        {
            GrowSnake(snake, snakeLength, 2);
            GenerateBigFood(field, big_food);
        }
        std::cout << "Score: " << score << "\n";


        switch (difficulty) {
        case 1:
            Sleep(200);
            break;
        case 2:
            Sleep(100);
            break;
        case 3:
            Sleep(80);
            break;
        }
    }
}



void InitGame()
{
    FieldInput();
    char** field = CreateField();
    int snakeLength = 1;
    Coordinate* snake = new Coordinate[snakeLength];
    snake[0] = { fieldWidth / 2, fieldHeight / 2 };

    Coordinate food;
    Coordinate wool;
    Coordinate big_food;
    GenerateFood(field, food);
    GenerateWool(field, wool);
    GenerateBigFood(field, big_food);
    GameLoop(field, snake, snakeLength, food, wool, big_food);
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