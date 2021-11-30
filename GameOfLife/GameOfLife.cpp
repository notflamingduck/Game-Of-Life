#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <sstream>
using namespace std;

class GameOfLife
{
private:
    int width;
    int height;
public:
    GameOfLife(int width, int height);
    vector<vector<int>> random_state();
    vector<vector<int>> dead_state();
    int next_cell_state(int& x, int& y, vector<vector<int>>& current_board);
    vector<vector<int>> next_board_state(vector<vector<int>> current_board);
    void render(vector<vector<int>> const board);
};
GameOfLife::GameOfLife(int width, int height)
{
    this->width = width;
    this->height = height;
}
// function for generating random state
// used only for testing
vector<vector<int>> GameOfLife::random_state()
{
    srand(time(0));
    vector<vector<int>> board;
    for (int i = 0; i < width; i++)
    {
        vector<int> tmp;
        for (int j = 0; j < height; j++)
        {
            tmp.push_back(rand() % 2);
        }

        board.push_back(tmp);
    }
    return board;
}

// function for generating dead state (all cells are 0)
// used only for testing
vector<vector<int>> GameOfLife::dead_state()
{
    vector<vector<int>> board;
    for (int i = 0; i < width; i++)
    {
        vector<int> tmp;
        for (int j = 0; j < height; j++)
        {
            tmp.push_back(0);
        }

        board.push_back(tmp);
    }
    return board;
}
//getting individual cells next state
int GameOfLife::next_cell_state(int& x, int& y, vector<vector<int>>& current_board)
{
    int alive_neighbors = 0;
    
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (y + j < 0 || y + j >= height || x + i < 0 || x + i >= width)
            {
                continue;
            }
            if (!(i == 0 && j == 0))
            {
                if (current_board[x + i][y + j])
                {
                    alive_neighbors++;
                }
            }
        }
    }

    if(current_board[x][y] == 1 && alive_neighbors < 2)
    {
        return 0;
    }
    if (current_board[x][y] == 1 && alive_neighbors > 3)
    {
        return 0;
    }
    if (current_board[x][y] == 0 && alive_neighbors == 3)
    {
        return 1;
    }
    else
    {
        return current_board[x][y];
    }
}
// pushing each cells new state into the 2D vector
vector<vector<int>> GameOfLife::next_board_state(vector<vector<int>> current_board)
{
    vector<vector<int>> new_state;

    for (int x = 0; x < width; x++)
    {
        vector<int> tmp;
        for (int y = 0; y < height; y++)
        {
            tmp.push_back(next_cell_state(x, y, current_board));
        }
        new_state.push_back(tmp);
    }
    return new_state;
}

// printing the matrix
void GameOfLife::render(vector<vector<int>> const board)
{
    int height = board.size();
    int width = board[0].size();

    for (int i = 0; i < height; i++)
    {
        cout << '|';
        for (int j = 0; j < width; j++)
        {
            if (board[i][j] == 1)
            {
                cout << '#';
            }
            else {
                cout << ' ';
            }
        }
        cout << '|';
        cout << endl;
    }
}

int main()
{
    int width = 10;
    int height = 10;
    string path = "C:\\Users\\Thinkpad\\source\\repos\\GameOfLife\\GameOfLife\\toad.txt";
    vector<vector<int>> input;
    // reading pattern from text file
    try {
        ifstream file;
        file.open(path);
        ostringstream ss;
        if (!file)
        {
            throw runtime_error("File failed to open.");
        }
        string line;  
        while (getline(file, line))
        {
            vector<int> row;
            char ch;
            istringstream ss(line);
            while (ss >> ch)
            {
                row.push_back(ch - '0');
            }
            input.push_back(row);
        }
    }
    catch (exception& e)
    {
        cerr << e.what() << endl;
    }

    GameOfLife gol(6, 6);
    vector<vector<int>> new_state;
    new_state  = gol.next_board_state(input);
    // running Game of Life forever
    while (true)
    {
        new_state = gol.next_board_state(new_state);        
        gol.render(new_state);
    }
}
