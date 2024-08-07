#include "Menu.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
Menu::Menu(float width, float height, string s1, string s2, string s3) {
	font.loadFromFile("Media/Jomhuria-Regular.ttf");
	mainmenue[0].setFont(font);
	mainmenue[0].setFillColor(Color{ 0, 150, 0 });
	mainmenue[0].setString(s1);
	mainmenue[0].setCharacterSize(160);
	mainmenue[0].setPosition(Vector2f(850, height / 4 + 50));

	mainmenue[1].setFont(font);
	mainmenue[1].setFillColor(Color::White);
	mainmenue[1].setString(s2);
	mainmenue[1].setCharacterSize(160);
	mainmenue[1].setPosition(Vector2f(850, height / 4 + 150));

	mainmenue[2].setFont(font);
	mainmenue[2].setFillColor(Color::White);
	mainmenue[2].setString(s3);
	mainmenue[2].setCharacterSize(160);
	mainmenue[2].setPosition(Vector2f(850, height / 4 + 250));
	selected = 0;
}
Menu::~Menu() {}
void Menu::steSelected(int n) {
	selected = n;
}

void Menu::draw(RenderWindow& window) {
	for (int i = 0; i < 3; i++) {
		window.draw(mainmenue[i]);
	}
}
void Menu::moveDown() {
	if (selected + 1 <= 3) {
		mainmenue[selected].setFillColor(Color::White);
		selected++;
		if (selected == 3)
			selected = 0;
		mainmenue[selected].setFillColor(Color{ 0, 150, 0 });
	}
}
void Menu::moveUp() {
	if (selected - 1 >= -1) {
		mainmenue[selected].setFillColor(Color::White);
		selected--;
		if (selected == -1)
			selected = 2;
		mainmenue[selected].setFillColor(Color{ 0, 150, 0 });
	}
}
