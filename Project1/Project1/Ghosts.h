#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include"Player.h"
#include <queue>
using namespace std;
using namespace sf;
class Ghosts
{
public:
	//     i   j                i   j               i   j              i    j
	int ghostsMap1[4][4] = { {12 , 12 , -1 , 0} , {12 , 15 , 0 , 1} , {8 , 12 ,  1 , 0} , {8 , 15 , 0 , -1} };
	int ghostsMap2[4][4] = { {16 , 12 ,  1 , 0} , {16 , 14 , 1 , 0} , {8 , 12 , -1 , 0} , {8 , 14 , 1 , 0 } };
	int ghostsMap3[4][4] = { {8 , 9 , -1 , 0} , {8 , 18 , 0 , 1} , {17 , 9 ,  1 , 0} , {17 , 18 , 0 , -1} };
	int Lives = 0;
	Texture g1r;
	Texture g2r;
	Texture g3r;
	Texture g4r;

	Texture g1l;
	Texture g2l;
	Texture g3l;
	Texture g4l;

	Texture g1u;
	Texture g2u;
	Texture g3u;
	Texture g4u;

	Texture g1d;
	Texture g2d;
	Texture g3d;
	Texture g4d;
	Sprite pin; // pink
	Sprite ink; // blue
	Sprite bli; // red
	Sprite cly; // orange
public:
	Ghosts();
	~Ghosts();
	void moveGhost(int board[22][28], int ghosts[4][4], int pacman[2]);
	void moveGhostBFS(int board[22][28], int ghosts[4][4], int pacman[2]);
	int Loss(RenderWindow& window, int pacman[2], int ghosts[4][4], int pacDir[2], Player& p, int c);
};

