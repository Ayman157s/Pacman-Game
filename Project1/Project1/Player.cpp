#pragma once
#include "Player.h"
#include<iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include "Map.h"
Player::Player() {
	pacR[0].loadFromFile("Media/pacRight2.png");
	pacR[1].loadFromFile("Media/pacF2.png");
	pacL[0].loadFromFile("Media/pacLift.png");
	pacU[0].loadFromFile("Media/pacUp.png");
	pacD[0].loadFromFile("Media/pacDown.png");
	s.setTexture(pacR[0]);
}
void Player::movePacman(int board[22][28], int pacman[2], int pacmanDirection[2], Player& p) {
	if (board[pacman[0] + pacmanDirection[0]][pacman[1] + pacmanDirection[1]] != 1) {
		pacman[0] += pacmanDirection[0]; //pacman[0] -> i
		pacman[1] += pacmanDirection[1]; //pacman[1] -> j 
	}
}
void Player::moveRight(int board[22][28], int pacman[2], Player& p) { //x = 1 , y = 0

	if (board[pacman[0] + 0][pacman[1] + 1] != 1) {

		s.setTexture(pacR[0]);
		pacmanDirection[0] = 0;
		pacmanDirection[1] = 1;

	}
	else {
		storeMovement[0] = 0;
		storeMovement[1] = 1;

	}

}
void Player::moveLeft(int board[22][28], int pacman[2], Player& p) { //x = 1 , y = 0

	if (board[pacman[0] + 0][pacman[1] - 1] != 1) {

		p.s.setTexture(p.pacL[0]);
		pacmanDirection[0] = 0;
		pacmanDirection[1] = -1;
	}
	else {
		storeMovement[0] = 0;
		storeMovement[1] = -1;

	}

}
void Player::moveUp(int board[22][28], int pacman[2], Player& p) { //x = 1 , y = 0

	if (board[pacman[0] - 1][pacman[1] + 0] != 1) {
		p.s.setTexture(p.pacU[0]);
		pacmanDirection[0] = -1;
		pacmanDirection[1] = 0;
	}
	else {
		storeMovement[0] = -1;
		storeMovement[1] = 0;

	}

}
void Player::moveDown(int board[22][28], int pacman[2], Player& p) { //x = 1 , y = 0

	if (board[pacman[0] + 1][pacman[1] + 0] != 1) {
		p.s.setTexture(p.pacD[0]);
		pacmanDirection[0] = 1;
		pacmanDirection[1] = 0;
	}
	else {
		storeMovement[0] = 1;
		storeMovement[1] = 0;

	}

}
void Player::moveToStore(int board[22][28], int pacman[2], int pacmanDirection[2], int storeMovement[2], Player& p) {

	if ((storeMovement[0] != 0 || storeMovement[1] != 0) && (board[pacman[0] + storeMovement[0]][pacman[1] + storeMovement[1]] != 1)) {
		if (storeMovement[0] == 0 && storeMovement[1] == 1) {// right
			p.s.setTexture(p.pacR[0]);

		}
		else if (storeMovement[0] == 0 && storeMovement[1] == -1) {// left
			p.s.setTexture(p.pacL[0]);

		}
		else if (storeMovement[0] == -1 && storeMovement[1] == 0) {// up
			p.s.setTexture(p.pacU[0]);

		}
		else if (storeMovement[0] == 1 && storeMovement[1] == 0) {// down
			p.s.setTexture(p.pacD[0]);

		}
		pacmanDirection[0] = storeMovement[0];
		pacmanDirection[1] = storeMovement[1];
		storeMovement[0] = 0;
		storeMovement[1] = 0;
	}
}


