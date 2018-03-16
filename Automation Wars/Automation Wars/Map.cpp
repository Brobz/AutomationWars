//
//  Map.cpp
//  Automation Wars
//
//  Created by Guilherme Bittencourt de Borba on 3/9/18.
//  Copyright © 2018 Brobz&JALVITO. All rights reserved.
//

#include "Map.h"


Map::Map(){
    dimensions = Vector2i(800, 600);
    cellSize = 2;
    emitters.push_back(Vector3i(200, 300, 2000));
    emitters.push_back(Vector3i(350, 300, 2000));
    emitters.push_back(Vector3i(650, 500, 2000));
    for(int i = 0; i < dimensions.x / cellSize; i++){
        for(int j = 0; j < dimensions.y / cellSize; j++){
            double factor = 0;
            //factor = ((double)i / dimensions.x + (double)j / dimensions.y) * 255 / 2.0 * cellSize;
            for(int a = 0; a < emitters.size(); a++){
                factor += emitters[a].z / sqrt(pow(emitters[a].x - i * cellSize, 2) + pow(emitters[a].y - j * cellSize, 2));
            }
            if(factor > 255)
                factor = 255;
            if(factor < 0)
                factor = 0;
            territory.push_back(factor / 255);
            cells.push_back(Cell(Vector2i(i, j), cellSize, Color(factor, factor, factor)));
            
        }
    }
    
}

void Map::update(){
    vector<Cell> cellsCopy(cells);
    for(int i = 0; i < cellsCopy.size(); i++){
        Vector2i pos = cellsCopy[i].getPosition();
        int n  = 0;
        
        if(pos.x != dimensions.x / cellSize - 1)
            if(!getCell(Vector2i(pos.x + 1, pos.y))->isDead()){
                n += 1;
            }
        if(pos.x != dimensions.x / cellSize - 1 && pos.y)
            if(!getCell(Vector2i(pos.x + 1, pos.y - 1))->isDead()){
                n += 1;
            }
        if(pos.x != dimensions.x / cellSize - 1 && pos.y != dimensions.y / cellSize - 1)
            if(!getCell(Vector2i(pos.x + 1, pos.y + 1))->isDead()){
                n += 1;
            }
        if(pos.y != dimensions.y / cellSize - 1)
            if(!getCell(Vector2i(pos.x, pos.y + 1))->isDead()){
                n += 1;
            }
        if(pos.x && pos.y != dimensions.y / cellSize - 1)
            if(!getCell(Vector2i(pos.x - 1, pos.y + 1))->isDead()){
                n += 1;
            }
        if(pos.x)
            if(!getCell(Vector2i(pos.x - 1, pos.y))->isDead()){
                n += 1;
            }
        if(pos.x && pos.y)
            if(!getCell(Vector2i(pos.x - 1, pos.y - 1))->isDead()){
                n += 1;
            }
        if(pos.y)
            if(!getCell(Vector2i(pos.x, pos.y - 1))->isDead()){
                n += 1;
            }
        
        
        cellsCopy[i].update(n, territory[toOneDimension(pos)]);
    }
    
    cells = cellsCopy;
}


int Map::toOneDimension(Vector2i coord){
    return coord.x * dimensions.y / cellSize + coord.y;
}

Cell* Map::getCell(Vector2i pos){
    return &cells[pos.x * dimensions.y / cellSize + pos.y];
}

Cell* Map::getCell(Vector2i pos, vector<Cell> &_cells){
    return &_cells[pos.x * dimensions.y / cellSize + pos.y];
}

int Map::getCellSize(){
    return cellSize;
}

void Map::draw(sf::RenderWindow *window){
    for(int i = 0; i < cells.size(); i++){
        cells[i].draw(window);
    }
}
