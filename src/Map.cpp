#include "Map.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "SFML/Graphics.hpp"
#include <Player.h>

using namespace std;
Map::Map(const char* filename) {
    //ctor
    this->setFileMap(filename);
}
int Map::isLoaded() {
    return this->loaded;
}
void Map::setTexture(sf::Texture* texture, int dimX, int dimY) {
    this->texture = *texture;
    this->dimX = dimX;
    this->dimY = dimY;
    this->sprite.setTexture(this->texture);
    this->posX = 0;
    this->posY = 0;
}
void Map::setPosition(int x, int y) {
    this->posX = x;
    this->posY = y;
}
void Map::setSprite(int x, int y) {
    //defini l'image de la map
    //defini les dimensions
    //defini quel nombre associer a tel sprite
    int dimX = this->dimX;
    int dimY = this->dimY;
    this->sprite.setTextureRect(sf::IntRect(x * dimX, y * dimY, dimX, dimY));
}
int AABB(int x1, int y1, int w1,int h1, int x2,int y2,int w2, int h2) {
     if(  x2 >= x1+w1
       || x2+w2 <= x1
       || y2 > y1 + h1
       || y2+h2 <= y1) {
        return 0;
    }
    return 1;
}
void Map::setFileMap(const char* filename) {
    //on charge le fichier map
    FILE* file = fopen(filename, "r");
    if(file == NULL) {
        loaded = 0;
        cout << "Echec ouverture de la carte" << endl;
    } else {
        char tmp = getc(file);
        int w=0, h=0;
        while(tmp != EOF) {
            tmp = fgetc(file);
            if(tmp != '\n') {
                if(tmp != ' ') w++;
            } else {
                h++;
            }
        }
        h++;
        w = ((w+1) / h);
        this->mapWidth  = w;
        this->mapHeight = h;
        this->mapData = (char**) malloc(sizeof(char*) * h);

        for(int i=0; i < h; i++) {
            this->mapData[i] = (char*) malloc(sizeof(char) * w);
        }

        int y=0, x=0;
        fclose(file);
        FILE* file2 = fopen(filename, "r");
        char tmp2 = getc(file2);
        if(file2 != NULL) {
            while(tmp2 != EOF) {
                if(tmp2 != '\n' && tmp2 != ' ') {
                    this->mapData[y][x] = tmp2;
                    x++;
                    //cout << tmp2 << ", ";
                }
                if(x >= w) {
                    x = 0;
                    y++;
                    //cout << endl;
                }
                tmp2 = fgetc(file2);
            }
        }
        for(int i=0; i < h; i++) {
            for(int j=0; j < w; j++) {
                printf("%c, ", this->mapData[i][j]);
            }
            printf("\n");
        }
    }
}
int Map::collision(Player* player) {
    char* types = "13456789abc\0"; //les blocs sur lequels ont peut collisioner
    for(int i=0; i < this->mapHeight; i++) {
        for(int j=0; j < this->mapWidth; j++) {
            for(int k=0; types[k] != '\0'; k++) {
                if(this->mapData[i][j] == types[k]) {
                    if(1 == AABB(this->posX + j * this->dimX, this->posY + i * this->dimY, this->dimX, this->dimY, player->x, player->y, player->tileWidth, player->tileHeight)) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
void Map::draw(sf::RenderWindow* window) {
    int x=0, y=0;
    for(int i=0; i < this->mapHeight; i++) {
        for(int j=0; j < this->mapWidth; j++) {
            char v = this->mapData[i][j];
            //il suffit de changer cette conditions pour d autres map
            switch(v) {
                case '1':
                    x = 0; y = 0;
                    break;
                case '0':
                    x = 1; y = 0;
                    break;
                case '3':
                    x = 2; y = 0;
                    break;
                case '4':
                    x = 0; y = 1;
                    break;
                case '5':
                    x = 1; y = 1;
                    break;
                case '6':
                    x = 2; y = 1;
                    break;
                case '7':
                    x = 0; y = 2;
                    break;
                case '8':
                    x = 1; y = 2;
                    break;
                case '9':
                    x = 2; y = 2;
                    break;
                case 'a':
                    x = 0; y = 3;
                    break;
                case 'b':
                    x = 1; y = 3;
                    break;
                case 'c':
                    x = 2; y = 3;
                    break;
            }
            this->setSprite(x, y);
            this->sprite.setPosition(this->posX + j * this->dimX,this->posY + i * this->dimY);
            window->draw(this->sprite);
        }
    }
}
