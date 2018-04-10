//
//  Map.cpp
//  Automation Wars
//
//  Created by Guilherme Bittencourt de Borba on 3/9/18.
//  Copyright © 2018 Brobz&JALVITO. All rights reserved.
//

#include "Map.h"
#include <algorithm>


Map::Map(){
    srand(time(NULL));
    dimensions = Vector2i(800, 600);
    cellSize = 2;
    emitters.push_back(Vector3i(200, 300, 3500));
    emitters.push_back(Vector3i(450, 250, 1500));
    emitters.push_back(Vector3i(650, 500, 2500));
    loadTerritory();
    int c = 5000;
    for(int i = 0; i < c; i++){
        Vector2i pos = Vector2i(rand() % (dimensions.x / cellSize), rand() % (dimensions.y / cellSize));
        while(getCell(pos) != nullptr){
            pos = Vector2i(rand() % (dimensions.x / cellSize), rand() % (dimensions.y / cellSize));
        }
        cells.push_back(Cell(pos, cellSize, Color(100, 100, 100), dimensions));
    }
}

void Map::loadTerritory(){
    territory.clear();
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
        }
    }
}

void Map::update(){
    for(int i = 0; i < cells.size(); i++){
        Vector2i pos = cells[i].getPosition();
        int highestTerritoryDir = 0;
        float highestTerritory = 0;
        bool highestTerritoryNeighbour;
        for(int j = 0; j < neighbourCoords.size(); j++){
            if(toOneDimension(pos + neighbourCoords[j]) >= territory.size() || toOneDimension(pos + neighbourCoords[j]) < 0)
                continue;
            
            if(territory[toOneDimension(pos + neighbourCoords[j])] > highestTerritory){
                highestTerritory = territory[toOneDimension(pos + neighbourCoords[j])];
                highestTerritoryDir = j;
            }
        }
        
        
        if(getCell(pos + neighbourCoords[highestTerritoryDir]) != nullptr)
            highestTerritoryNeighbour = 1;//!(getCell(pos + neighbourCoords[highestTerritoryDir])->isDead());
        else
            highestTerritoryNeighbour = 0;
        
        cells[i].update(territory[toOneDimension(pos)], highestTerritoryNeighbour, highestTerritoryDir);
        
        if(cells[i].isDead()){
            cells.erase(cells.begin() + i);
            i--;
            continue;
        }
        
        
        
        if(territory[toOneDimension(pos)] > 0.2){
            spreadTerritory(cells[i].getPosition());
        }
        
    }
    if(!(counter % 300)){
        emitters.clear();
        for(int i = 0; i < 3; i++){
            emitters.push_back(Vector3i(rand() % 800 + 1, rand() % 600 + 1, rand() % 2501 + 1000));
        }
        loadTerritory();
    }
    counter++;
}

void Map::spreadTerritory(Vector2i point){
    bool RIGHT_CORNER = (point.x == dimensions.x / cellSize - 1);
    bool LEFT_CORNER = (!point.x);
    bool TOP_CORNER = (!point.y);
    bool BOTTOM_CORNER = (point.y == dimensions.y / cellSize - 1);
    
    float spread = territory[toOneDimension(point)] * 0.03 / 8;
    int n = 0;
    
    if(!RIGHT_CORNER){
        if(territory[toOneDimension(Vector2i(point.x + 1, point.y))] < territory[toOneDimension(point)]){
            territory[toOneDimension(Vector2i(point.x + 1, point.y))] += spread;
            n++;
        }
    }
    if(!RIGHT_CORNER && !BOTTOM_CORNER){
        if(territory[toOneDimension(Vector2i(point.x + 1, point.y + 1))] < territory[toOneDimension(point)]){
            territory[toOneDimension(Vector2i(point.x + 1, point.y + 1))] += spread;
            n++;
        }
    }
    if(!BOTTOM_CORNER){
        if(territory[toOneDimension(Vector2i(point.x, point.y + 1))] < territory[toOneDimension(point)]){
            territory[toOneDimension(Vector2i(point.x, point.y + 1))] += spread;
            n++;
        }
    }
    if(!LEFT_CORNER && !BOTTOM_CORNER){
        if(territory[toOneDimension(Vector2i(point.x - 1, point.y + 1))] < territory[toOneDimension(point)]){
            territory[toOneDimension(Vector2i(point.x - 1, point.y + 1))] += spread;
            n++;
        }
    }
    if(!LEFT_CORNER){
        if(territory[toOneDimension(Vector2i(point.x - 1, point.y))] < territory[toOneDimension(point)]){
            territory[toOneDimension(Vector2i(point.x - 1, point.y))] += spread;
            n++;
        }
    }
    if(!LEFT_CORNER && !TOP_CORNER){
        if(territory[toOneDimension(Vector2i(point.x - 1, point.y - 1))] < territory[toOneDimension(point)]){
            territory[toOneDimension(Vector2i(point.x - 1, point.y - 1))] += spread;
            n++;
        }
    }
    if(!TOP_CORNER){
        if(territory[toOneDimension(Vector2i(point.x, point.y - 1))] < territory[toOneDimension(point)]){
            territory[toOneDimension(Vector2i(point.x, point.y - 1))] += spread;
            n++;
        }
    }
    if(!RIGHT_CORNER && !TOP_CORNER){
        if(territory[toOneDimension(Vector2i(point.x + 1, point.y - 1))] < territory[toOneDimension(point)]){
            territory[toOneDimension(Vector2i(point.x + 1, point.y - 1))] += spread;
            n++;
        }
    }
    
    territory[toOneDimension(point)] -= spread * n;
}


int Map::toOneDimension(Vector2i coord){
    return coord.x * dimensions.y / cellSize + coord.y;
}

Cell* Map::getCell(Vector2i pos){
    for(int i = 0; i < cells.size(); i++){
        if(cells[i].getPosition() == pos)
            return &cells[i];
    }

    return nullptr;
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
