#include "Tetromino.h"

Tetromino::Tetromino(int type) 
{
    this->Type = type;
    x = playGridWidth / 2 - 2;
    y = 0;
    rotation = 0;

    for (int i = 0; i < 4; i++) 
    { 
        shape[i] = tetrominoes[this->Type][i]; 
    }
}

void Tetromino::Draw(BITMAP* BUFFER, BITMAP* TILESET, bool preview)
{
    int xPos = x;
    if(preview)
        xPos = 4 / 2 - 2; 

    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            if (shape[rotation] & (0x8000 >> (i * 4 + j))) 
            {
                DrawBlock(BUFFER, TILESET, xPos + j, y + i);                
            }
        }
    }
}

void Tetromino::DrawBlock(BITMAP* BUFFER, BITMAP* TILESET, int x, int y) 
{
    blit(TILESET, BUFFER, tileStartXpos + ((this->Type) * 8), tileStartYpos, x * blockSize, y * blockSize, tileWidth, tileHeight);
}

bool Tetromino::CanMove(int** playGrid, int newX, int newY) 
{
    for (int i = 0; i < 16; i++) 
    {
        if (shape[rotation] & (0x8000 >> i)) 
        {
            int localX = i % 4;
            int localY = i / 4;
            int finalX = newX + localX;
            int finalY = newY + localY;

            if (finalX < 0 || finalX >= playGridWidth || finalY < 0 || finalY >= playGridHeight)
                return false;

            if (playGrid[finalY][finalX] != 0)
                return false;
        }
    }
    return true; 
}

bool Tetromino::CanRotate(int** playGrid, int nextRotation) 
{
    for (int i = 0; i < 16; i++) 
    {
        if (shape[nextRotation] & (0x8000 >> i)) 
        {
            int localX = i % 4;
            int localY = i / 4;
            int finalX = x + localX;
            int finalY = y + localY;

            if (finalX < 0 || finalX >= playGridWidth || finalY < 0 || finalY >= playGridHeight)
                return false;

            if (playGrid[finalY][finalX] != 0)
                return false;
        }
    }
    return true;
}

void Tetromino::LockPiece(int** playGrid)
{
    for (int i = 0; i < 16; i++)
    {
        if (shape[rotation] & (0x8000 >> i)) 
        {
            int localX = i % 4;
            int localY = i / 4;
            int finalX = this->x + localX;
            int finalY = this->y + localY;

            if (finalX >= 0 && finalX < playGridWidth && finalY >= 0 && finalY < playGridHeight)
                playGrid[finalY][finalX] = this->Type + 1;
        }
    }
}