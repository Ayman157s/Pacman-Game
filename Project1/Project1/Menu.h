#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class Menu {
public:
	Text mainmenue[3];
	Menu(float width, float height, string s1, string s2, string s3);
	void draw(RenderWindow& window);
	void moveUp();
	void moveDown();
	void steSelected(int n);
	int pressed() {
		return selected;
	}
	~Menu();
private:
	int selected;
	Font font;

};

