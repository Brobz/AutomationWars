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
    cellSize = 5;
    emitters.push_back(Vector3i(200, 300, 5000));
    emitters.push_back(Vector3i(350, 300, 10000));
    emitters.push_back(Vector3i(650, 500, 1000));
    for(int i = 0; i < dimensions.x / cellSize; i++){
        for(int j = 0; j < dimensions.y / cellSize; j++){
            territory.push_back((float)rand() / (RAND_MAX + 1));
            double factor = 0;
            //factor = ((double)i / dimensions.x + (double)j / dimensions.y) * 255 / 2.0 * cellSize;
            for(int a = 0; a < emitters.size(); a++){
                factor += emitters[a].z / sqrt(pow(emitters[a].x - i * cellSize, 2) + pow(emitters[a].y - j * cellSize, 2));
            }
            if(factor > 255)
                factor = 255;
            if(factor < 0)
                factor = 0;
            cells.push_back(Cell(Vector2i(i, j), cellSize, Color(factor, factor, factor)));
            
        }
    }
    
}

Cell* Map::getCell(Vector2i pos){
    return &cells[pos.x * dimensions.y / cellSize + pos.y];
}

int Map::getCellSize(){
    return cellSize;
}

void Map::draw(sf::RenderWindow *window){
    for(int i = 0; i < cells.size(); i++){
        cells[i].draw(window);
    }
}
