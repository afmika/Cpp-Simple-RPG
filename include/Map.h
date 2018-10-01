#ifndef MAP_H
#define MAP_H
#include "SFML/Graphics.hpp"
#include <stdlib.h>
#include <Player.h>

/**
    CETTE MAP EST VRAIMENT CHIANTE A GERER
    IL EST PREFERABLE DE CREER UNE MAP SUR PHOTOSHOP
    PUIS DE CREER UN FICHIER TXT QUI ETUDIE *SEULEMENT*
    LA COLLSION ENTRE LE FICHIER PNG.
**/
class Map {
    public:
        Map(const char* file);
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
        void setSprite(int x, int y);
        void draw(sf::RenderWindow* window);
        void setPosition(int x, int y);
        int collision(Player* player);
    protected:

    private:
};

#endif // MAP_H
