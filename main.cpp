#include "SFML/Graphics.hpp"
#include "Player.h"
#include "SimpleMap.h"
#include <iostream>
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "RPG afmika",
                            sf::Style::Titlebar | sf::Style::Close /*on affiche que le titre et la fermeture X*/
                        );
    //JOUEUR
    Player player("Mika", window.getSize().x/2, window.getSize().y/2); // TSY MAINTSY ITO!
    sf::Texture texture;
    texture.loadFromFile("Characters/player3.png");
    player.setTexture(&texture);

    //CARTE
    /**Map carte("MapData/map.rpg_afmika");
    sf::Texture map_texture;
    map_texture.loadFromFile("Tiles/autotile1.png");
    carte.setTexture(&map_texture, 32, 32);//32 x 32
    carte.setPosition(0, 0); //Position initiale
    **/

    /**
    A LIRE SI JAMAIS LE PROJET A MIS PLUS DE TEMPS QUE PREVU oh... FUTUR MIKA!

    La classe SimpleMap que t'as créé gère une carte définie au préalable
    mais il faut générer le fichier txt correspondant qui
    fournira les parties collisionables de la carte.

    ASTUCE: Mettre plusieurs couches de carte
        - Une variable pour chaque type de couche (principale, batiments, items)

    UTILISER LE MAPPEUR DANS LE DOSSIER OUTILS_UTILES_POUR_LE_JEU/*.html
    - Remplacer les donnees du fichiers html (dimX, dimY, canvasWidth, canvasHeight)
    - img.src = "Ma_carte.png"
    **/

    SimpleMap carte("MapData/grandeMap.rpg_afmika");
    sf::Texture map_texture;
    map_texture.loadFromFile("Tiles/grandeMap.png");
    carte.setTexture(&map_texture, 16, 16);
    carte.setPosition(0, 0);

    sf::View camera(sf::Vector2f(0,0), sf::Vector2f(window.getSize().x/2, window.getSize().y/2));
    camera.zoom(1.25);
    while(window.isOpen()) {
        sf::Event e;
        while(window.pollEvent(e)) {
            if(e.type == sf::Event::Closed) {
                window.close();
            } else if(e.type == sf::Event::KeyPressed) {
                int code = (int) e.key.code;
                if(carte.collision(&player) == 1) {
                    player.setToLastPosition();
                } else {
                    switch(code) {
                    case 73: //haut
                        player.goUp();
                        break;
                    case 74://bas
                        player.goDown();
                        break;
                    case 71://gauche
                        player.goLeft();
                        break;
                    case 72://droite
                        player.goRight();
                        break;
                    }
                }
            }
        }
        camera.setCenter(player.getOrigin());
        carte.draw(&window);
        player.draw(&window);
        window.display();
        window.setView(camera);
        window.clear(sf::Color::Black);
        sf::sleep(sf::milliseconds(100));
    }
    return 0;
}
