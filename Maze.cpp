//g++ Maze.cpp -o final && ./final

#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define GRID_WIDTH 50
#define GRID_HEIGHT 50
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define RESET "\e[0m"

struct holeDirections
{
    bool arriba;
    bool derecha;
    bool izquierda;
    bool abajo;
};

const char WALL = '#';
const char VOID = ' ';

char grid[GRID_WIDTH * GRID_HEIGHT];

int salidax;
int saliday;
int entradax;
int entraday;

holeDirections nodos[GRID_WIDTH * GRID_HEIGHT];

void ResetGrid()
{
    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; ++i)
    {
        grid[i] = WALL;
    }
}

int XYToIndex(int x, int y)
{
    return y * GRID_WIDTH + x;
}
int IsInBounds(int x, int y)
{
    if (x < 0 || x >= GRID_WIDTH)
        return false;
    if (y < 0 || y >= GRID_HEIGHT)
        return false;
    return true;
}

void Visit(int x, int y)
{
    grid[XYToIndex(x, y)] = VOID;

    int dirs[4];
    dirs[0] = NORTH;
    dirs[1] = EAST;
    dirs[2] = SOUTH;
    dirs[3] = WEST;
    for (int i = 0; i < 4; ++i)
    {
        int r = rand() & 3;
        int temp = dirs[r];
        dirs[r] = dirs[i];
        dirs[i] = temp;
    }

    for (int i = 0; i < 4; ++i)
    {
        int dx = 0, dy = 0;
        switch (dirs[i])
        {
        case NORTH:
            dy = -1;
            break;
        case SOUTH:
            dy = 1;
            break;
        case EAST:
            dx = 1;
            break;
        case WEST:
            dx = -1;
            break;
        }

        int x2 = x + (dx << 1);
        int y2 = y + (dy << 1);
        if (IsInBounds(x2, y2))
        {
            if (grid[XYToIndex(x2, y2)] == WALL)
            {
                grid[XYToIndex(x2 - dx, y2 - dy)] = VOID;
                Visit(x2, y2);
            }
        }
    }
}
void Fill()
{
    for (int i = 0; i < GRID_WIDTH; i++)
    {
        grid[i] = WALL;
        grid[i + (GRID_HEIGHT - 1) * GRID_WIDTH] = WALL;
    }
    for (int i = 1; i < GRID_HEIGHT; i++)
    {
        grid[i * GRID_WIDTH] = WALL;
        grid[i * GRID_WIDTH - 1] = WALL;
    }
}
void setSalidaEntrada()
{
    entradax = floor(GRID_WIDTH / 2);
    entraday = floor(GRID_HEIGHT/ 2);
    salidax = 1;
    saliday = 1;
}
void PrintGrid()
{
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            if (x == salidax && y == saliday)
            {
                printf(GRN "S");
            }
            else if (x == entradax && y == entraday)
            {   
                printf(RED "E");
            }
            else
            {
                if(grid[XYToIndex(x, y)] == WALL){
                    printf(RESET "#");
                }else{
                    printf(RESET " ");
                }
            }
            
        }
        cout << endl;
    }
}

void buildMaze(){
    srand(time(0));
    ResetGrid();
    Visit(1, 1);
    Fill();
    setSalidaEntrada();
}

void printMaze(){
    PrintGrid();
    printf(GRN "\nSUCCESS!\n\n");
}

int main()
{
    buildMaze();
    printMaze();
    
    return 0;
}
