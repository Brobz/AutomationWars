//
//  Cell.cpp
//  Automation Wars
//
//  Created by Guilherme Bittencourt de Borba on 3/13/18.
//  Copyright © 2018 Brobz&JALVITO. All rights reserved.
//

#include "Cell.h"
#include <cmath>

Cell::Cell(Vector2i _position, int _size, Color _color){
    position = _position;
    size = _size;
    hp = 0;
    color = _color;
    dead = true;
    if(rand() % 2)
        dead = false;
    vertices.push_back(Vertex(Vector2f(position.x * size, position.y * size), color));
    vertices.push_back(Vertex(Vector2f((position.x + 1) * size, position.y * size), color));
    vertices.push_back(Vertex(Vector2f((position.x + 1) * size, (position.y + 1) * size), color));
    vertices.push_back(Vertex(Vector2f(position.x * size, (position.y + 1) * size), color));
}

void Cell::update(int neighbours, float territory){
    
    this->territory = territory;
    
    if(neighbours < 2)
        dead = true;
    if(neighbours > 3)
        dead = true;
    if(neighbours == 3 && dead && territory > 0.15)
        dead = false;
    
    if(territory > 0.75)
        dead = false;
    if(territory < 0.2)
        dead = true;
    
    
    if(dead)
        setColor(Color(255, 0, 0, 255 * pow(territory, 0.7)));
    else
        setColor(Color(0, 255, 0, 255 * pow(territory, 0.7)));
}

bool Cell::isDead(){
    return dead;
}

float Cell::getTerritory(){
    return territory;
}

int Cell::getHp(){
    return hp;
}

Vector2i Cell::getPosition(){
    return position;
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
