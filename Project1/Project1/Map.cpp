#include "Map.h"
#include <thread>
#include <chrono>
#define ll long long 
#define db double
#define ld long double
#define loop(x) for(int i=0 ; i < x ; i++)
Map::Map() {
	font.loadFromFile("Media/Jomhuria-Regular.ttf");
	score.setFont(font);
	score.setString("Score");
	score.setFillColor(Color::Blue);
	score.setCharacterSize(120);
	score.setPosition(Vector2f(500, -30));
	highScore.setFont(font);
	highScore.setString("High Score");
	highScore.setFillColor(Color::Blue);
	highScore.setCharacterSize(120);
	highScore.setPosition(Vector2f(1100, -30));
	lives.setFont(font);
	lives.setString("Lives");
	lives.setFillColor(Color::Green);
	lives.setCharacterSize(120);
	lives.setPosition(Vector2f(800, -30));
	live.loadFromFile("Media/pacRight.png");
	L1.setTexture(live);
	L1.setPosition(760, 100);
	L2.setTexture(live);
	L2.setPosition(840, 100);
	L3.setTexture(live);
	L3.setPosition(920, 100);
	rectangle.loadFromFile("Media/Rec1.png");
	rec.setTexture(rectangle);
	rec.setPosition(440, 25);
	rectangle2.loadFromFile("Media/Rec2.png");
	rec2.setTexture(rectangle2);
	rec2.setPosition(420, 15);
	rectangle3.loadFromFile("Media/Rec3.png");
	rec3.setTexture(rectangle3);
	rec3.setPosition(400, 15);
	block.loadFromFile("Media/bb.png");
	bl.setTexture(block);

	block2.loadFromFile("Media/wall.png");
	bl2.setTexture(block2);

	block3.loadFromFile("Media/ww.png");
	bl3.setTexture(block3);

}

void Map::drawMap1(RenderWindow& window, Player& p, Ghosts& g) {
	window.draw(rec);
	window.draw(score);
	if (g.Lives == 2) {
		lives.setFillColor(Color::Red);
	}
	window.draw(lives);
	window.draw(L1);
	if (g.Lives == 1 || g.Lives == 0) {
		window.draw(L2);
	}
	if (g.Lives == 0) {
		window.draw(L3);
	}

	window.draw(highScore);

	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 28; j++) {
			if (i == p.pacmanMap1[0] && j == p.pacmanMap1[1]) {
				p.s.setPosition(j * 40 + 400, i * 40 + 190);
				window.draw(p.s);
			}
			else if (i == g.ghostsMap1[0][0] && j == g.ghostsMap1[0][1]) {
				g.pin.setPosition(j * 40 + 400, i * 40 + 190);
				window.draw(g.pin);
			}
			else if (i == g.ghostsMap1[1][0] && j == g.ghostsMap1[1][1]) {
				g.ink.setPosition(j * 40 + 400, i * 40 + 190);
				window.draw(g.ink);
			}
			else if (i == g.ghostsMap1[2][0] && j == g.ghostsMap1[2][1]) {
				g.bli.setPosition(j * 40 + 400, i * 40 + 190);
				window.draw(g.bli);
			}
			else if (i == g.ghostsMap1[3][0] && j == g.ghostsMap1[3][1]) {
				g.cly.setPosition(j * 40 + 400, i * 40 + 190);
				window.draw(g.cly);
			}
			else if (board[i][j] == 1) {
				bl.setPosition(j * 40 + 400, i * 40 + 190);
				window.draw(bl);
			}
		}
	}

}
void Map::drawMap2(RenderWindow& window, Player& p, Ghosts& g) {
	window.draw(rec2);
	window.draw(score);
	if (g.Lives == 2) {
		lives.setFillColor(Color::Red);
	}
	window.draw(lives);
	window.draw(L1);
	if (g.Lives == 1 || g.Lives == 0) {
		window.draw(L2);
	}
	if (g.Lives == 0) {
		window.draw(L3);
	}
	window.draw(highScore);
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 28; j++) {
			if (i == p.pacmanMap2[0] && j == p.pacmanMap2[1]) {
				p.s.setPosition(j * 40 + 420, i * 40 + 170);
				window.draw(p.s);
			}
			else if (i == g.ghostsMap2[0][0] && j == g.ghostsMap2[0][1]) {
				g.pin.setPosition(j * 40 + 420, i * 40 + 170);
				window.draw(g.pin);
			}
			else if (i == g.ghostsMap2[1][0] && j == g.ghostsMap2[1][1]) {
				g.ink.setPosition(j * 40 + 420, i * 40 + 170);
				window.draw(g.ink);
			}
			else if (i == g.ghostsMap2[2][0] && j == g.ghostsMap2[2][1]) {
				g.bli.setPosition(j * 40 + 420, i * 40 + 170);
				window.draw(g.bli);
			}
			else if (i == g.ghostsMap2[3][0] && j == g.ghostsMap2[3][1]) {
				g.cly.setPosition(j * 40 + 420, i * 40 + 170);
				window.draw(g.cly);
			}
			else if (board1[i][j] == 1)
			{
				bl3.setPosition(j * 40 + 420, i * 40 + 170);
				window.draw(bl3);
			}
		}
	}

}
void Map::drawMap3(RenderWindow& window, Player& p, Ghosts& g) {
	window.draw(rec3);
	window.draw(score);
	if (g.Lives == 2) {
		lives.setFillColor(Color::Red);
	}
	window.draw(lives);
	window.draw(L1);
	if (g.Lives == 1 || g.Lives == 0) {
		window.draw(L2);
	}
	if (g.Lives == 0) {
		window.draw(L3);
	}
	window.draw(highScore);
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 28; j++) {
			if (i == p.pacmanMap3[0] && j == p.pacmanMap3[1]) {
				p.s.setPosition(j * 40 + 400, i * 40 + 170);
				window.draw(p.s);
			}
			else if (i == g.ghostsMap3[0][0] && j == g.ghostsMap3[0][1]) {
				g.pin.setPosition(j * 40 + 400, i * 40 + 170);
				window.draw(g.pin);
			}
			else if (i == g.ghostsMap3[1][0] && j == g.ghostsMap3[1][1]) {
				g.ink.setPosition(j * 40 + 400, i * 40 + 170);
				window.draw(g.ink);
			}
			else if (i == g.ghostsMap3[2][0] && j == g.ghostsMap3[2][1]) {
				g.bli.setPosition(j * 40 + 400, i * 40 + 170);
				window.draw(g.bli);
			}
			else if (i == g.ghostsMap3[3][0] && j == g.ghostsMap3[3][1]) {
				g.cly.setPosition(j * 40 + 400, i * 40 + 170);
				window.draw(g.cly);
			}
			else if (board2[i][j] == 1)
			{
				bl2.setPosition(j * 40 + 400, i * 40 + 170);
				window.draw(bl2);
			}
		}
	}
}

Map::~Map() {}


