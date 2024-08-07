
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
//#include "Map.h"
using namespace sf;

class Player {

public:
    int pacmanMap1[2] = { 10 , 3 }; // i , j
    int pacmanMap2[2] = { 10 , 2 }; // i , j
    int pacmanMap3[2] = { 1 , 1 };  // i , j
    int pacmanDirection[2] = { 0 , 0 };
    int storeMovement[2] = { 0 , 0 };
    Texture pacR[2];
    Texture pacL[1];
    Texture pacU[1];
    Texture pacD[1];
    int c = 0;
    Sprite s;
    float speed = 0.3f;

public:

    Player();
    void moveToStore(int board[22][28], int pacman[2], int pacmanDirection[2], int storeMovement[2], Player& p);
    void movePacman(int board[22][28], int pacman[2], int pacmanDirection[2], Player& p);
    void moveRight(int board[22][28], int pacman[2], Player& p);
    void moveLeft(int board[22][28], int pacman[2], Player& p);
    void moveUp(int board[22][28], int pacman[2], Player& p);
    void moveDown(int board[22][28], int pacman[2], Player& p);

};
