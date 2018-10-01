#ifndef PLAYER_H
#define PLAYER_H
#include "SFML/Graphics.hpp"

class Player {
    public:
        int x, y, lastX, lastY, mana, level;
        int step;
        const char* name;
        sf::Texture texture;
        sf::Sprite sprite;
        int tileWidth;
        int tileHeight;
        int spriteX=0, spriteY=0;
        Player(const char* name, int x, int y);
        void setName(const char* name);
        void setPosition(int x, int y);
        void setTexture(sf::Texture* texture);
        void setSprite(int spriteX, int spriteY);
        void animateUp();
        void animateDown();
        void animateRight();
        void animateLeft();
        void goUp();
        void animate(int direction);
        void goDown();
        void goLeft();
        void goRight();
        void setToLastPosition();
        void draw(sf::RenderWindow* window);
        void debug(bool debug_, sf::RenderWindow* window);
        sf::Vector2f getOrigin();
};

#endif // PLAYER_H
