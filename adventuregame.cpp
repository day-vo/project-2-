#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


struct Player
{
private:
    
public:
    int health;
    int damage;
};

class Maze
{
private:
    const int MAZE_WIDTH = 10;
    const int MAZE_HEIGHT = 10;

    char** board;
    bool playerLost;

public:
    Maze()
    {
        playerLost = false;
        board = new char* [MAZE_HEIGHT];

        for (int i = 0; i < MAZE_HEIGHT; i++)
        {
            board[i] = new char[MAZE_WIDTH];
        }

        // Initialize with empty spaces
        for (int y = 0; y < MAZE_HEIGHT; y++)
        {
            for (int x = 0; x < MAZE_WIDTH; x++)
            {
                board[y][x] = ' ';
            }
        }

        // Place the player at the start
        board[0][0] = 'O';

        // Place some random walls
        srand(time(0));
        int numWalls = (rand() % 20) + 10;

        for (int i = 0; i < numWalls; i++)
        {
            int x = (rand() % MAZE_WIDTH);
            int y = (rand() % MAZE_HEIGHT);

            if (x == 0 && y == 0)
            {
                // Don't place a wall over the player
                continue;
            }

            board[y][x] = '#';
        }
    }

    void Map()
    {
        playerLost = false;
        board = new char* [MAZE_HEIGHT];

        for (int i = 0; i < MAZE_HEIGHT; i++)
        {
            board[i] = new char[MAZE_WIDTH];
        }

        // Initialize with empty spaces
        for (int y = 0; y < MAZE_HEIGHT; y++)
        {
            for (int x = 0; x < MAZE_WIDTH; x++)
            {
                board[y][x] = '?';
            }
        }

        // Place the player at the start
        board[0][0] = 'O';
    }

    void Print()
    {
        // Print the top border
        for (int x = 0; x < MAZE_WIDTH + 2; x++)
        {
            cout << '-';
        }
        cout << endl;

        // Print the maze contents
        for (int y = 0; y < MAZE_HEIGHT; y++)
        {
            cout << '|';
            for (int x = 0; x < MAZE_WIDTH; x++)
            {
                cout << board[y][x];
            }
            cout << '|' << endl;
        }

        // Print the bottom border
        for (int x = 0; x < MAZE_WIDTH + 2; x++)
        {
            cout << '-';
        }
        cout << endl;
    }

    void MovePlayer(char input)
    {
        int playerX = 0;
        int playerY = 0;

        // Find the player's current position
        for (int y = 0; y < MAZE_HEIGHT; y++)
        {
            for (int x = 0; x < MAZE_WIDTH; x++)
            {
                if (board[y][x] == 'O')
                {
                    playerX = x;
                    playerY = y;
                }
            }
        }

        // Move the player in the specified direction
        if (input == 'w')
        {
            if (playerY > 0 && board[playerY - 2][playerX] != '#')
            {
                board[playerY][playerX] = ' ';
                board[playerY - 2][playerX] = 'O';
            }
        }
        else if (input == 'a')
        {
            if (playerX > 0 && board[playerY][playerX - 2] != '#')
            {
                board[playerY][playerX] = ' ';
                board[playerY][playerX - 2
                ] = 'O';
            }
        }
        else if (input == 's')
        {
            if (playerY < MAZE_HEIGHT - 1 && board[playerY + 1][playerX] != '#')
            {
                board[playerY][playerX] = ' ';
                board[playerY + 1][playerX] = 'O';
            }
        }
        else if (input == 'd')
        {
            if (playerX < MAZE_WIDTH - 1 && board[playerY][playerX + 1] != '#')
            {
                board[playerY][playerX] = ' ';
                board[playerY][playerX + 1] = 'O';
            }
        }
    }

    bool IsSolved()
    {
        int playerX = 0;
        int playerY = 0;

        // Find the player's current position
        for (int y = 0; y < MAZE_HEIGHT; y++)
        {
            for (int x = 0; x < MAZE_WIDTH; x++)
            {
                if (board[y][x] == 'O')
                {
                    playerX = x;
                    playerY = y;
                }
            }
        }

        // Check if the player is at the end
        if (playerX == MAZE_WIDTH - 1 && playerY == MAZE_HEIGHT - 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool IsLost()
    {
        return playerLost;
    }

    void Lost()
    {
        playerLost = true;
    }
};


int main()
{
    Maze maze;
    Player hero;
    hero.health = 100;
    Player enemy;
    string fight = "";

    cout << "Welcome to the Adventure Game! Watch out for holes and enemies! Get to the treasure at the end of the maze!" << endl;

    char input = ' ';
        while (!maze.IsSolved() && !maze.IsLost())
        {
                maze.Print();
                cout << "Your health is: " << hero.health << endl;
                cout << " 'w' up, 'a' left, 's' down, 'd' right, press 'q' to quit" << endl;
                cout << "Enter your move (WASD): ";
                cin >> input;

                if (input == 'w' || input == 'a' || input == 's' || input == 'd')
                {
                    maze.MovePlayer(input);
                }
                if (input == 'q') {
                    cout << "Thanks for playing!";
                    exit(1);
                }
                // Add some chance of fighting an enemy
                if ((rand() % 10) == 1 && (rand() % 50) != 1)
                {
                    enemy.health = 25;
                    cout << "You stumble across an enemy! fight or flee?: "; 
                    while(enemy.health >0)
                    {
                        hero.damage = rand() % 15 + 10;
                        enemy.damage = rand() % 25;
                        cin >> fight;
                        if (fight == "fight")
                        {
                            enemy.health = enemy.health - hero.damage;
                            cout << "Enemy's health: " << enemy.health << endl;
                        }
                        if (enemy.health <= 0) {
                            cout << "You defeat your enemy! continue";
                            break;
                        }
                        if (enemy.health > 0)
                        {
                            hero.health = hero.health - enemy.damage;
                        }
                        if (hero.health < 0) {
                            cout << "You died!";
                            exit(1);
                        }
                        cout << "Your health: " << hero.health << endl;
                        cout << "fight again or flee?: ";

                        if (fight == "flee")
                        {
                            cout << "You give up! Thanks for playing!" << endl;
                            exit(1);
                        }
                        if (fight != "fight" && fight != "flee")
                        {
                            cout << "Invalid input! Try again." << endl;
                        }
                    }
                }
                // Add some chance of falling into a hole
                if ((rand() % 50) == 1)
                {
                    maze.Lost();
                    cout << "You fell into a hole and died!" << endl;
                    exit(1);
                }
                if (input != 'w' && input != 'a' && input != 's' && input != 'd' && input !='q')
                {
                    cout << "Invalid input! press w, a, s, d, or q." << endl;
                }
        }

    if (maze.IsSolved())
    {
        cout << "You won!" << endl;
    }
    exit(1);
    return 0;
}
