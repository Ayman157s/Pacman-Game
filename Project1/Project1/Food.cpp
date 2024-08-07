#include "Food.h"
//for displaying 
Food::Food() {

    buf.loadFromFile("Media/winn.wav");
    sn.setBuffer(buf);
    buff.loadFromFile("Media/pacman_chomp.wav");
    se.setBuffer(buff);
    font.loadFromFile("Media/Jomhuria-Regular.ttf");
    foodCount.setFont(font);
    TotalFood.setFont(font);
    TotalFood.setFillColor(Color::Yellow);
    TotalFood.setPosition(550, 80);
    TotalFood.setCharacterSize(70);
    foodCount.setPosition(500, 95);
    foodCount.setCharacterSize(50);

}
//for drawing food point
Food::Food(float x, float y, int k) {

    shape.setPosition(x, y);
    if (k == 1) {
        shape.setFillColor(Color::Red);
    }
    else if (k == 2) {
        shape.setFillColor(Color::Green);
    }
    else {
        shape.setFillColor(Color::Blue);
    }
    shape.setRadius(5);
    shape.setOrigin(5, 5);
    isVisible = true;
}

void Food::draw(sf::RenderWindow& window) {
    if (isVisible) {
        window.draw(shape);
    }
}


sf::FloatRect Food::getBounds() const {
    return shape.getGlobalBounds();
}

void Food::setVisibility(bool visible) {
    isVisible = visible;
}
bool Food::eatFood(Player& p, vector<Food>& foodPoints, RenderWindow& window, int maxFood) {
    string s;
    TotalFood.setString(" /" + to_string(maxFood));
    window.draw(TotalFood);
    if (count == maxFood) {
        return true;
    }
    for (auto it = foodPoints.begin(); it != foodPoints.end(); ) {
        if (it->isVisible && it->getBounds().intersects(p.s.getGlobalBounds())) {
            //se.play();
            // Remove the food point from the vector
            it = foodPoints.erase(it);
            count++;
            s = to_string(count);
            foodCount.setString(s);
            return false;
        }
        ++it;
    }

    window.draw(foodCount);
}
