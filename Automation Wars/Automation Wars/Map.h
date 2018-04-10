//
//  Map.h
//  Automation Wars
//
//  Created by Guilherme Bittencourt de Borba on 3/9/18.
//  Copyright © 2018 Brobz&JALVITO. All rights reserved.
//

#ifndef Map_h
#define Map_h

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Cell.h"

using namespace sf;
using namespace std;

class Map{
public:
    Map();
    Map(Vector2i, int);
    void update();
    void draw(RenderWindow *window);
    Cell* getCell(Vector2i pos);
    Cell* getCell(Vector2i pos, vector<Cell> &_cells);
    void spreadTerritory(Vector2i point);
    int getCellSize();
    int toOneDimension(Vector2i coord);
    void loadTerritory();
private:
    Vector2i dimensions;
    vector<Vector2i> neighbourCoords = {Vector2i(1, 0), Vector2i(1, 1), Vector2i(0, 1), Vector2i(-1, 1), Vector2i(-1, 0), Vector2i(-1, -1), Vector2i(0, -1), Vector2i(1, -1)};
    int cellSize;
    vector<Vector3i> emitters;
    vector<float> territory;
    vector<Cell> cells;
    int counter;
};



#endif /* Map_h */
