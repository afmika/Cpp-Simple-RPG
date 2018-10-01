#include "SimpleMap.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "SFML/Graphics.hpp"
#include <Player.h>

using namespace std;
SimpleMap::SimpleMap(const char* filename) {
    //ctor
    this->setFileMap(filename);
}
int SimpleMap::isLoaded() {
    return this->loaded;
}
void SimpleMap::setTexture(sf::Texture* texture, int dimX, int dimY) {
    this->texture = *texture;
    this->dimX = dimX;
    this->dimY = dimY;
    this->sprite.setTexture(this->texture);
    this->posX = 0;
    this->posY = 0;
}
void SimpleMap::setPosition(int x, int y) {
    this->posX = x;
    this->posY = y;
}
void SimpleMap::setSprite() {
    //defini l'image de la map
    //defini les dimensions
    //defini quel nombre associer a tel sprite
    int dimX = this->dimX;
    int dimY = this->dimY;
    this->sprite.setTexture(this->texture);
}
int AABB2(int x1, int y1, int w1,int h1, int x2,int y2,int w2, int h2) {
     if(  x2 >= x1+w1
       || x2+w2 <= x1
       || y2 > y1 + h1
       || y2+h2 <= y1) {
        return 0;
    }
    return 1;
}
void SimpleMap::setFileMap(const char* filename) {
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
        /*for(int i=0; i < h; i++) {
            for(int j=0; j < w; j++) {
                printf("%c, ", this->mapData[i][j]);
            }
            printf("\n");
        }*/
    }
}
int SimpleMap::collision(Player* player) {
    /** on peut offrir une tab de player ici (test network) pour le multijoueur **/
    //Collision sur les murs
    if(player->x < 0 || player->y < 0 || player->x+player->tileWidth > this->texture.getSize().x || player->y+player->tileHeight > this->texture.getSize().y) {
        return 1;
    }
    //collision sur kes blocs collisionables de la carte
    for(int i=0; i < this->mapHeight; i++) {
        for(int j=0; j < this->mapWidth; j++) {
            if(this->mapData[i][j] != '0') {
                 if(1 == AABB2(this->posX + j * this->dimX, this->posY + i * this->dimY, this->dimX,this->dimY, player->x, player->y, player->tileWidth, player->tileHeight)) {
                     return 1;
                 }
            }
        }
    }
    return 0;
}
void SimpleMap::debug(bool debug_, sf::RenderWindow* window) {
    sf::RectangleShape r;
    r.setFillColor(sf::Color::Transparent);
    r.setOutlineThickness(1);
    r.setOutlineColor(sf::Color::Red);
    for(int i=0; i < this->mapHeight; i++) {
        for(int j=0; j < this->mapWidth; j++) {
            if(this->mapData[i][j] != '0') {
                    r.setPosition(sf::Vector2f(j * this->dimX, i * this->dimY));
                    r.setSize(sf::Vector2f(this->dimX, this->dimY));
                    window->draw(r);
            }
        }
    }
}

void SimpleMap::draw(sf::RenderWindow* window) {
    window->draw(this->sprite);
    this->debug(true, window);
}
