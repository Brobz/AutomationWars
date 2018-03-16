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
    int getCellSize();
    int toOneDimension(Vector2i coord);
private:
    Vector2i dimensions;
    int cellSize;
    vector<Vector3i> emitters;
    vector<float> territory;
    vector<Cell> cells;
};



#endif /* Map_h */
