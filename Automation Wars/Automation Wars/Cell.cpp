//
//  Cell.cpp
//  Automation Wars
//
//  Created by Guilherme Bittencourt de Borba on 3/13/18.
//  Copyright © 2018 Brobz&JALVITO. All rights reserved.
//

#include "Cell.h"

Cell::Cell(Vector2i _position, int _size, Color _color){
    position = _position;
    size = _size;
    hp = 100;
    color = _color;
    vertices.push_back(Vertex(Vector2f(position.x * size, position.y * size), color));
    vertices.push_back(Vertex(Vector2f((position.x + 1) * size, position.y * size), color));
    vertices.push_back(Vertex(Vector2f((position.x + 1) * size, (position.y + 1) * size), color));
    vertices.push_back(Vertex(Vector2f(position.x * size, (position.y + 1) * size), color));
}

void Cell::setColor(Color c){
    color = c;
    for(int i = 0; i < vertices.size(); i++){
        vertices[i].color = c;
    }
}


void Cell::draw(sf::RenderWindow *window){
    (*window).draw(&vertices[0], 4, Quads);
}
