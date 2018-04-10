//
//  Cell.cpp
//  Automation Wars
//
//  Created by Guilherme Bittencourt de Borba on 3/13/18.
//  Copyright © 2018 Brobz&JALVITO. All rights reserved.
//

#include "Cell.h"
#include <cmath>

Cell::Cell(Vector2i _position, int _size, Color _color, Vector2i _mapDimensions){
    position = _position;
    mapDimensions = _mapDimensions;
    size = _size;
    hp = 100;
    color = _color;
    dead = false;
    vertices.push_back(Vertex(Vector2f(position.x * size, position.y * size), color));
    vertices.push_back(Vertex(Vector2f((position.x + 1) * size, position.y * size), color));
    vertices.push_back(Vertex(Vector2f((position.x + 1) * size, (position.y + 1) * size), color));
    vertices.push_back(Vertex(Vector2f(position.x * size, (position.y + 1) * size), color));
}

void Cell::update(float _territory, bool highestTerritoryNeighbour, int highTerritoryDir){
    
    territory = _territory;
    
    
    if(!highestTerritoryNeighbour)
        move(neighbourCoords[highTerritoryDir]);
    
    if(territory < 0.15){
        hp -= (1 - territory);
    }
    
    if(territory > 0.2)
        hp += territory * 3;
    
    if(hp > 100)
        hp = 100;
    if(hp < 0)
        hp = 0;
    
    if(hp > 0)
        dead = false;
    else
        dead = true;
    
    
    
    setColor(Color(255 * (100 - hp) / 100, 255 * hp / 100, 0, 255 * sqrt(territory)));
    /*/
    float f = 255 * territory;
    setColor(Color(f, f, f));
    /*/
}

void Cell::moveRandom(){
    
}


void Cell::move(Vector2i dir){
    if(!position.x && dir.x < 0)
        return;
    if(position.x == mapDimensions.x / size - 1 && dir.x > 0)
        return;
    if(!position.y && dir.y < 0)
        return;
    if(position.y == mapDimensions.y / size - 1 && dir.y > 0)
        return;
    
    position += dir;
    for(int i = 0; i < vertices.size(); i++){
        vertices[i] = Vertex(vertices[i].position + Vector2f(dir.x * size, dir.y * size), vertices[i].color);
    }
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

int Cell::toOneDimension(Vector2i coord){
    return coord.x * mapDimensions.y / size + coord.y;
}
