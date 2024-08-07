#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <sys/timeb.h>
#include <sys/utime.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <string>
#include <random>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>
#include"Menu.h"
#include"Map.h"
#include"Food.h"
#include"Player.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
using namespace std;
using namespace sf;
int num = 1000; // mainmenu
string name;
Event event;
void pname(RenderWindow& window, std::string& name) {
	Event event;
	if (!name.empty()) {
		name.clear();
	}
	Texture background;
	background.loadFromFile("Media/Pacman_Menu.png");
	Sprite bg;
	bg.setTexture(background);
	Font font;
	font.loadFromFile("Media/Jomhuria-Regular.ttf");
	Text t1;
	Text t2;
	Text t3; // Message to display allowed characters
	t1.setFont(font);
	t2.setFont(font);
	t3.setFont(font);
	t1.setString("Enter your name");
	t1.setCharacterSize(160);
	t2.setCharacterSize(160);
	t1.setPosition(50, 0);
	t2.setPosition(50, 130);
	t1.setFillColor(Color::Red);
	t2.setFillColor(Color{ 0, 150, 0 });

	t3.setString("Only enter:\n- Alphabetic (A-Z/a-z)\n- Special characters (eg. !, #, $, %, &, @, ?, ~)");
	t3.setCharacterSize(50);
	t3.setPosition(50, 400);
	t3.setFillColor(Color::Cyan);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::TextEntered) {
				// Allow alphabetical characters and specific special characters
				if (isalpha(event.text.unicode) || strchr(" !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~", event.text.unicode)) {
					name += static_cast<char>(event.text.unicode);
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Backspace) && name.size() > 0) {
				name.resize(name.size() - 1);
			}
			if (Keyboard::isKeyPressed(Keyboard::Return) && name.size() > 0) {
				num = 3;
				return;
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				num = 1000;
				return;
			}
		}
		t2.setString(name);
		window.clear();
		window.draw(bg);
		window.draw(t1);
		window.draw(t2);
		window.draw(t3); // Draw the message about allowed characters
		window.display();
	}
}
map<string, vector<int>> playerScores;
//store scores with player names
void movePacman(Player& p, int board[22][28], int pacman[2]) {
	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
	{
		p.moveRight(board, pacman, p);
	}
	else if (Keyboard::isKeyPressed(sf::Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
	{
		p.moveLeft(board, pacman, p);
	}
	else if (Keyboard::isKeyPressed(sf::Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
	{
		p.moveUp(board, pacman, p);
	}
	else if (Keyboard::isKeyPressed(sf::Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
	{
		p.moveDown(board, pacman, p);
	}
}
void saveScores(string& playerName, int score) {
	// Save the score to the file
	ofstream scoreFile("Media/playersScores.txt", ios::app);
	if (scoreFile.is_open()) {
		scoreFile << playerName << " " << score << endl;
		scoreFile.close();
	}
	else {
		cout << "Unable to open file." << endl;
		return;
	}

	// Update playerScores map with the new score
	playerScores[playerName].resize(3, -1);

	// Sort the scores in descending order
	//sort(playerScores[playerName].rbegin(), playerScores[playerName].rend());
}
int getPlayerTopScore(const string& playerName) {
	int topScore = 0;
	ifstream scoreFile("Media/playersScores.txt");
	if (scoreFile.is_open()) {
		string name;
		int score;
		while (scoreFile >> name >> score) {
			if (name == playerName && score > topScore) {
				topScore = score;
			}
		}
		scoreFile.close();
	}
	return topScore;
}
void displayTopScore(RenderWindow& window, const string& playerName) {
	// Retrieve player's top score
	int topScore = getPlayerTopScore(playerName);


	Font font;
	font.loadFromFile("Media/Jomhuria-Regular.ttf");

	Text topScoreText;
	topScoreText.setFont(font);
	topScoreText.setCharacterSize(90);
	topScoreText.setFillColor(Color::Yellow);
	topScoreText.setString(to_string(topScore));
	topScoreText.setPosition(1200, 60);
	// Draw top score on the window
	window.draw(topScoreText);
}
void displayTopScores(RenderWindow& window, const string& playerName) {
	if (window.isOpen()) {
		// Clear the playerScores map before reading from the file
		playerScores.clear();

		// Open the score file
		ifstream scoreFile("Media/playersScores.txt");
		if (scoreFile.is_open()) {
			string name;
			int score;
			// Read scores from the file and update playerScores map
			while (scoreFile >> name >> score) {
				if (name == playerName) {
					playerScores[name].push_back(score);
				}
			}
			scoreFile.close();

			// Clear the window before drawing scores
			window.clear();

			// Font for text
			Font font;
			font.loadFromFile("Media/Jomhuria-Regular.ttf");

			// Draw scores
			Vector2f position(700.0f, 200.0f); // Initial position
			Text text;
			text.setFont(font);
			text.setCharacterSize(100);
			text.setFillColor(Color::Green);

			for (const auto& player : playerScores) {
				// Draw player name
				text.setString("You have reached the last leve!\nPlayer: " + player.first);
				text.setPosition(position);
				window.draw(text);
				position.y += 200.0f;

				// Draw top three scores
				text.setString("Top Three Scores:");
				text.setPosition(position);
				window.draw(text);
				position.y += 100.0f;

				// Sort the scores in descending order
				vector<int> sortedScores = player.second;
				sort(sortedScores.rbegin(), sortedScores.rend());

				// Display the top three scores
				for (int i = 0; i < min(3, static_cast<int>(sortedScores.size())); ++i) {
					text.setString(to_string(i + 1) + ") " + to_string(sortedScores[i]));
					text.setPosition(position);
					window.draw(text);
					position.y += 100.0f;
				}
			}

			// Display the window contents
			window.display();
		}
		else {
			cout << "Unable to open the score file" << endl;
		}
	}
}
void displayTopScores(RenderWindow& window) {
	if (window.isOpen()) {
		// Clear the playerScores map before reading from the file
		playerScores.clear();

		// Open the score file
		ifstream scoreFile("Media/playersScores.txt");
		if (scoreFile.is_open()) {
			string playerName;
			int score;
			// Read scores from the file and update playerScores map
			while (scoreFile >> playerName >> score) {
				playerScores[playerName].push_back(score);
			}
			scoreFile.close();

			// Clear the window before drawing scores
			window.clear();

			// Font for text
			Font font;
			font.loadFromFile("Media/Jomhuria-Regular.ttf");

			// Draw scores
			Vector2f position(100.0f, 100.0f); // Initial position
			Text text;
			text.setFont(font);
			text.setCharacterSize(40);
			text.setFillColor(Color::Red);

			for (const auto& player : playerScores) {
				// Draw player name
				text.setString("Player: " + player.first);
				text.setPosition(position);
				window.draw(text);
				position.y += 30.0f;

				// Draw top three scores
				text.setString("Top Three Scores:");
				text.setPosition(position);
				window.draw(text);
				position.y += 30.0f;

				// Sort the scores in descending order
				vector<int> sortedScores = player.second;
				sort(sortedScores.rbegin(), sortedScores.rend());

				// Display the top three scores
				for (int i = 0; i < min(3, static_cast<int>(sortedScores.size())); ++i) {
					text.setString(to_string(i + 1) + ") " + to_string(sortedScores[i]));
					text.setPosition(position);
					window.draw(text);
					position.y += 30.0f;

					// Wrap text if it reaches the window width
					if (position.y + 50.0f > window.getSize().y) {
						position.y = 100.0f; // Reset Y position
						position.x += 250.0f; // Move to the next column
					}
				}

				position.y += 30.0f; // Add some space between players
			}

			// Display the window contents
			window.display();
		}
		else {
			cout << "Unable to open the score file" << endl;
		}
	}
}

int main() {
	//definitions
	Map map;
	Ghosts g;
	int k = 0;
	Food f;
	Player p;
	int w = 0;
	int Live = 0;
	bool flag = false;
	int replay = 555;
	//used sprites and textures
	Texture mainmen;
	mainmen.loadFromFile("Media/Pacman_Menu.png");
	Sprite bg;
	bg.setTexture(mainmen);
	Texture t;
	t.loadFromFile("Media/black2.png");
	Sprite bground;
	bground.setTexture(t);
	Texture m;
	m.loadFromFile("Media/Untitled.png");
	Sprite l;
	l.setTexture(m);
	Texture y;
	y.loadFromFile("Media/w.png");
	Sprite wn;
	wn.setTexture(y);

	///Menu Objects
	Menu men(1920, 1080, "Play", "Scores", "Exit");
	Menu lossMen(1920, 1080, "Replay", "main menu", "Exit");
	Menu mapMen(1920, 1080, "Easy", "Medium", "Hard");
	Menu win(1920, 1080, "next level", "main menu", "Exit");

	///window 
	RenderWindow window(VideoMode(1920, 1080), "PAC MAN");

	// sound
	SoundBuffer buf;
	Sound sn;
	buf.loadFromFile("Media/pacman_beginning.wav");
	sn.setBuffer(buf);

	SoundBuffer buff;
	Sound sd;
	buff.loadFromFile("Media/pacman_death.wav");
	sd.setBuffer(buff);

	SoundBuffer buffe;
	Sound sw;
	buffe.loadFromFile("Media/winn.wav");
	sn.setBuffer(buffe);

	//food of  map1
	std::vector <Food> foodPoints;
	//food of  map2
	std::vector <Food> foodPoints1;
	//food of  map3
	std::vector <Food> foodPoints2;

	//time delay
	Clock clockPacman;
	Clock clock;
	Clock clock2;
	Time delayTime = milliseconds(200);
	Time delayPacman = milliseconds(80);
	Time delayGhost2 = milliseconds(80);
	//-----------------------------------------------------------------------------------
	while (true) {
		if (num == 1000) {
			window.draw(bg);
			men.draw(window);
			while (true) {
				while (window.isOpen())
				{
					while (window.pollEvent(event)) {
						if (event.type == Event::Closed) {
							window.close();
							break;
						}
						if (event.type == Event::KeyPressed) {
							if (event.key.code == Keyboard::Up) {
								men.moveUp();
							}
							if (event.key.code == Keyboard::Down) {
								men.moveDown();
							}
							if (event.key.code == Keyboard::Return) {
								if (men.pressed() == 0) {
									num = 0;
								}
								if (men.pressed() == 1) {
									num = 1;
								}
								if (men.pressed() == 2) {
									num = -1;
								}
							}
						}
					}
					window.clear();
					window.draw(bg);
					men.draw(window);
					window.display();
					if (num == -1) {
						window.close();
						break;
					}
					if (num == 0) { // play
						f.count = 0;
						pname(window, name);
						while (window.isOpen()) {
							while (window.pollEvent(event)) {
								if (event.type == Event::Closed) {
									window.close();
									break;
								}
								if (event.type == Event::KeyPressed) {
									if (event.key.code == Keyboard::Up) {
										mapMen.moveUp();
									}
									if (event.key.code == Keyboard::Down) {
										mapMen.moveDown();
									}
									if (event.key.code == Keyboard::Return) {
										if (mapMen.pressed() == 0) { // Easy
											w = 1;
										}
										if (mapMen.pressed() == 1) { // Medium
											w = 2;
										}
										if (mapMen.pressed() == 2) { // Hard
											w = 3;
										}
										int h = 0;
										while (window.isOpen() && (replay == 555)) {
											window.clear();
											window.draw(bground);
											if (w == 1) { // map 1
												if (h == 0) {
													for (int i = 0; i < 22; i++) {
														for (int j = 0; j < 28; j++) {
															if (map.board[i][j] == 0)
																foodPoints.emplace_back(j * 40 + 400 + 20, i * 40 + 190 + 20, 1);
														}
													}
													h = 1;
												}
												for (auto& food : foodPoints) {
													food.draw(window);
												}
												if (clock.getElapsedTime() >= delayTime) {
													g.moveGhost(map.board, g.ghostsMap1, p.pacmanMap1);
													clock.restart();
												}
												map.drawMap1(window, p, g);
												flag = f.eatFood(p, foodPoints, window, 218);
												displayTopScore(window, name);
												while (window.pollEvent(event)) {
													if (event.type == Event::Closed)
														window.close();
													movePacman(p, map.board, p.pacmanMap1);

												}
												if (clockPacman.getElapsedTime() >= delayPacman) {
													p.moveToStore(map.board, p.pacmanMap1, p.pacmanDirection, p.storeMovement, p);
													p.movePacman(map.board, p.pacmanMap1, p.pacmanDirection, p);
													clockPacman.restart();
												}

											}
											else if (w == 2) { // map 2
												if (h == 0) {
													for (int i = 0; i < 22; i++) {
														for (int j = 0; j < 28; j++) {
															if (map.board1[i][j] == 0)
																foodPoints1.emplace_back(j * 40 + 420 + 20, i * 40 + 170 + 20, 2);
														}
													}
													h = 1;
												}
												for (auto& foody : foodPoints1) {
													foody.draw(window);
												}
												if (clock2.getElapsedTime() >= delayGhost2) {
													g.moveGhost(map.board1, g.ghostsMap2, p.pacmanMap2);
													clock2.restart();
												}
												map.drawMap2(window, p, g);
												flag = f.eatFood(p, foodPoints1, window, 298);
												displayTopScore(window, name);
												while (window.pollEvent(event)) {
													if (event.type == Event::Closed)
														window.close();
													movePacman(p, map.board1, p.pacmanMap2);
												}
												if (clockPacman.getElapsedTime() >= delayPacman) {
													p.moveToStore(map.board1, p.pacmanMap2, p.pacmanDirection, p.storeMovement, p);
													p.movePacman(map.board1, p.pacmanMap2, p.pacmanDirection, p);
													clockPacman.restart();
												}
											}
											else if (w == 3) { // map 3
												if (h == 0) {
													for (int i = 0; i < 22; i++) {
														for (int j = 0; j < 28; j++) {
															if (map.board2[i][j] == 0)
																foodPoints2.emplace_back(j * 40 + 400 + 20, i * 40 + 170 + 20, 3);
														}
													}
													h = 1;
												}
												for (auto& foody : foodPoints2) {
													foody.draw(window);
												}
												if (clock.getElapsedTime() >= delayTime) {
													g.moveGhostBFS(map.board2, g.ghostsMap3, p.pacmanMap3);
													clock.restart();
												}
												map.drawMap3(window, p, g);
												flag = f.eatFood(p, foodPoints2, window, 254);
												displayTopScore(window, name);
												while (window.pollEvent(event)) {
													if (event.type == Event::Closed)
														window.close();
													movePacman(p, map.board2, p.pacmanMap3);
												}
												if (clockPacman.getElapsedTime() >= delayPacman) {
													p.moveToStore(map.board2, p.pacmanMap3, p.pacmanDirection, p.storeMovement, p);
													p.movePacman(map.board2, p.pacmanMap3, p.pacmanDirection, p);
													clockPacman.restart();
												}
											}
											if (w == 1) {
												k = g.Loss(window, p.pacmanMap1, g.ghostsMap1, p.pacmanDirection, p, 1);
											}
											else if (w == 2) {
												k = g.Loss(window, p.pacmanMap2, g.ghostsMap2, p.pacmanDirection, p, 2);
											}
											else if (w == 3) {
												k = g.Loss(window, p.pacmanMap3, g.ghostsMap3, p.pacmanDirection, p, 3);
											}
											if (k == 3) { // loss
												replay = 0;
												while (!foodPoints.empty()) {
													foodPoints.pop_back();
												}
												while (!foodPoints1.empty()) {
													foodPoints1.pop_back();
												}
												while (!foodPoints2.empty()) {
													foodPoints2.pop_back();
												}
												num = 0;
												k = 0;
												h = 0;
												g.Lives = 0;
												saveScores(name, f.count);
												sd.play();
												while (window.isOpen()) {
													while (window.pollEvent(event)) {
														if (event.type == Event::Closed) {
															window.close();
															break;
														}
														if (event.type == Event::KeyPressed) {
															if (event.key.code == Keyboard::Up) {
																lossMen.moveUp();
															}
															if (event.key.code == Keyboard::Down) {
																lossMen.moveDown();
															}
															if (event.key.code == Keyboard::Return) {
																if (lossMen.pressed() == 0) {// replay
																	replay = 555;
																	break;
																}
																if (lossMen.pressed() == 1) { // main menu
																	replay = 555;
																	num = 1000;
																	break;
																}
																if (lossMen.pressed() == 2) { // close
																	window.close();
																}

															}

														}

													}
													window.clear();
													window.draw(l);
													lossMen.draw(window);
													window.display();
													if (replay == 555 || num == 1000)
														break;
												}
												f.count = 0;
											}
											window.display();
											if (num == 1000)
												break;
											int next = 0;
											if (flag == true) { // win
												num = 0;
												saveScores(name, f.count);
												flag = false;
												h = 0;
												sn.play();
												while (window.isOpen()) {

													while (window.pollEvent(event)) {
														if (event.type == Event::Closed) {
															window.close();
															break;
														}
														if (event.type == Event::KeyPressed) {
															if (event.key.code == Keyboard::Up) {
																win.moveUp();
															}
															if (event.key.code == Keyboard::Down) {
																win.moveDown();
															}
															if (event.key.code == Keyboard::Return) {
																bool goToPrevMenu = false;
																if (win.pressed() == 0) {// go to next level
																	if (w == 1) {
																		w = 2;
																		p.pacmanMap2[0] = 10;
																		p.pacmanMap2[1] = 2;

																	}
																	else if (w == 2) {
																		w = 3;
																		p.pacmanMap3[0] = 1;
																		p.pacmanMap3[1] = 1;
																	}
																	else if (w == 3) {
																		while (!goToPrevMenu && window.isOpen()) {
																			displayTopScores(window, name);
																			while (window.pollEvent(event)) {
																				if (event.type == Event::Closed) {
																					window.close();
																					break;
																				}
																				if (Keyboard::isKeyPressed(Keyboard::Escape)) {

																					goToPrevMenu = true; // Go back to the previous menu
																					break;
																				}
																			}
																		}
																	}
																	if (goToPrevMenu) {
																		next = 0;
																	}
																	else {
																		next = 1;
																	}
																	break;
																}
																if (win.pressed() == 1) { // go to main menu
																	replay = 555;
																	num = 1000;
																	break;
																}
																if (win.pressed() == 2) { // close
																	window.close();
																	break;


																}

															}

														}

													}
													window.clear();
													window.draw(wn);
													win.draw(window);
													window.display();
													if (next == 1 || num == 1000)
														break;
												}
												f.count = 0;
											}
										}
									}
								}
								if (num == 1000)
									break;
							}
							if (num == 1000)
								break;
							window.clear();
							window.draw(bg);
							mapMen.draw(window);
							window.display();


						}

					}
					if (num == 1) { // scores
						while (window.isOpen()) {
							displayTopScores(window);
							while (window.pollEvent(event)) {
								if (event.type == Event::Closed) {
									window.close();
									break;
								}
								if (Keyboard::isKeyPressed(Keyboard::Escape)) {
									num = 1000;
									break;
								}

							}
							if (num == 1000)
								break;
						}
					}
					if (num == 1000)
						break;
				}
				if (num == 1000)
					break;
			}
		}
	}
}

