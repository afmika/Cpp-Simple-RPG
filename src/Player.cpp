#include "Player.h"
#include <math.h>
#include <iostream>
using namespace std;
Player::Player(const char* name, int x, int y) {
    //ctor
    this->setName(name);
    this->setPosition(x, y);
    this->step = 5;
    this->mana = 30;
    this->level = 1;
    this->spriteX = 0;
    this->spriteY = 0;
}
void Player::setName(const char* name) {
    this->name = name;
}

/** GESTIONS DES TEXTURES **/
void Player::setTexture(sf::Texture* texture) {
    this->texture = *texture;
}
void Player::setSprite(int spriteX, int spriteY) {
    this->spriteX = spriteX;
    this->spriteY = spriteY;
    // la texture est de 32 * 48 px*px pour 4 * 4 sprites
    this->tileWidth = 32;
    this->tileHeight = 48;
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(this->spriteX * this->tileWidth, this->spriteY * this->tileHeight, this->tileWidth, this->tileHeight));
}
/**GESTION DES ANIMATIONS**/
void Player::animate(int direction) {
    // 0d 1left 2right 3up
    this->spriteY = direction;
    if(this->spriteX >= 3) {
        this->spriteX = 0;
    } else {
        this->spriteX++;
    }
    //pour eviter les collisions
    //on remet le joueur au moment sans collision
    //ca evite le blocage des directions car sinon la collision sera toujours vraie
    this->lastX = this->x;
    this->lastY = this->y;
    cout << this->x << " et " << this->y << endl;
}
void Player::setToLastPosition() {
    this->setPosition(this->lastX, this->lastY);
}
/** GESTIONS DES DIRECTIONS **/
void Player::goUp() {
    this->animate(3);
    this->y-=this->step;
}
void Player::goDown() {
    this->animate(0);
    this->y+=this->step;
}
void Player::goLeft() {
    this->animate(1);
    this->x-=this->step;
}
void Player::goRight() {
    this->animate(2);
    this->x+=this->step;
}
/** GESTIONS DES POSITIONS ET DU DESSIN**/
sf::Vector2f Player::getOrigin() {
    sf::Vector2f o(this->x+this->tileWidth/2, this->y+this->tileHeight/2);
    return o;
}

void Player::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Player::debug(bool debug_, sf::RenderWindow* window) {
   if(debug_) {
        sf::RectangleShape r;
        r.setFillColor(sf::Color::Transparent);
        r.setOutlineThickness(1);
        r.setOutlineColor(sf::Color::Blue);
        r.setPosition(this->x, this->y);
        r.setSize(sf::Vector2f(this->tileWidth, this->tileHeight));
        window->draw(r);
    }
}

void Player::draw(sf::RenderWindow* window) {
    this->sprite.setPosition(this->x, this->y);
    this->setSprite(this->spriteX, this->spriteY);
    window->draw(this->sprite);
    this->debug(true, window);
}
