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
    Cell(Vector2i _position, int _size, Color _color);
    void draw(RenderWindow *window);
    void setColor(Color c);
private:
    Color color;
    int size, hp;
    Vector2i position;
    vector<Vertex> vertices;
};

#endif /* Cell_h */
