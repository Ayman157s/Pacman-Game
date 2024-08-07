#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include<SFML/Audio.hpp>
#include"Map.h"

class Food {
public:
    SoundBuffer buf;
    Sound sn;
    SoundBuffer buff;
    Sound se;
    Font font;
    Food(float x, float y, int k);
    Food();
    void draw(sf::RenderWindow& window);
    Text TotalFood;
    Text foodCount;
    int count = 0;
    string s1, s2, s3;
    sf::FloatRect getBounds() const;
    void setVisibility(bool visible);
    bool eatFood(Player& p, vector<Food>& foodPoints, RenderWindow& window, int maxFood);
    bool isVisible;
private:
    sf::CircleShape shape;
};
