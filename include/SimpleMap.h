#ifndef SIMPLEMAP_H
#define SIMPLEMAP_H
#include "SFML/Graphics.hpp"
#include <stdlib.h>
#include <Player.h>

class SimpleMap {
    public:
        SimpleMap(const char* file);
        int mapWidth, mapHeight;
        sf::Texture texture;
        int posX, posY;
        int dimX, dimY;
        sf::Sprite sprite;
        char** mapData = NULL;
        int loaded = 0;
        int isLoaded();
        void setFileMap(const char* filename);
        void setTexture(sf::Texture* texture, int dimX, int dimY);
        void setSprite();
        void debug(bool debug_, sf::RenderWindow* window);
        void draw(sf::RenderWindow* window);
        void setPosition(int x, int y);
        int collision(Player* player);
        void setScale(int x);
};

#endif // SIMPLEMAP_H
