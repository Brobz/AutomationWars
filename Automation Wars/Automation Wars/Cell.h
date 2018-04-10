//
//  Cell.h
//  Automation Wars
//
//  Created by Guilherme Bittencourt de Borba on 3/13/18.
//  Copyright © 2018 Brobz&JALVITO. All rights reserved.
//

#ifndef Cell_h
#define Cell_h

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

class Cell{
public:
    Cell();
    Cell(Vector2i _position, int _size, Color _color, Vector2i _mapDimensions);
    void update(float _territory, bool highestTerritoryNeighbour, int highTerritoryDir);
    void draw(RenderWindow *window);
    void setColor(Color c);
    int getHp();
    float getTerritory();
    bool isDead();
    Vector2i getPosition();
    void move(Vector2i dir);
    void moveRandom();
    int toOneDimension(Vector2i coord);
private:
    Color color;
    int size;
    vector<Vector2i> neighbourCoords = {Vector2i(1, 0), Vector2i(1, 1), Vector2i(0, 1), Vector2i(-1, 1), Vector2i(-1, 0), Vector2i(-1, -1), Vector2i(0, -1), Vector2i(1, -1)};
    float hp, territory;
    bool dead;
    Vector2i position;
    Vector2i mapDimensions;
    vector<Vertex> vertices;
};

#endif /* Cell_h */
