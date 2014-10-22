//
//  circlePack.cpp
//  Particle-Image
//
//  Created by Zachary Blank on 10/21/14.
//  Copyright (c) 2014 Hungry. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <ctime>
#include "circlePack.h"

std::vector<Pixel> area(Circle circle) {
    std::vector<Pixel> area;
    
    int left = circle.x - circle.r;
    int right = circle.x + circle.r;
    int top = circle.y - circle.r;
    int bottom = circle.y + circle.r;
    
    for (int row = top; row <= bottom; ++row) {
        for (int col = left; col <= right; ++col) {
            
            long dist = pow(circle.x - col, 2.0) + pow(circle.y - row, 2.0);
            
            if (dist <= pow(circle.r, 2.0)) {
                Pixel pixel;
                pixel.x = round(row);
                pixel.y = round(col);
                
                area.push_back(pixel);
            }
        }
    }
    
    return area;
}

bool isCircleInContainer(Circle circle, std::vector<std::vector<Pixel>> container) {

    // Vector
    // get area of given circle
    std::vector<Pixel> _area = area(circle);
    
//    std::cout << "Area size: " << _area.size() << std::endl;
    
    //loop through pixels and see if they are either transparent or filled
    for (int i = 0; i < _area.size(); i++) {
                
        if (_area[i].y > container.size() || _area[i].x > container[_area[i].y].size() || container[_area[i].y][_area[i].x].filled || container[_area[i].y][_area[i].x].a == 0) {
            return false;
        }
    }
    
    return true;
}

std::vector<Circle> circles;
std::vector<Circle> circlePack(Grid grid) {
    
    // Get a random starting point
    Pixel startPixel = grid.opaque[rand() % grid.opaque.size()];
    
    Circle startCircle;
    startCircle.x = startPixel.x;
    startCircle.y = startPixel.y;
    startCircle.r = 10;
    
    if (isCircleInContainer(startCircle, grid.matrix)) {
        // return the point
        circles.push_back(startCircle);
    }
    
//    std::cout << "# of Circles:" << circles.size() << std::endl;
    
    if (circles.size() < 10) {
        circlePack(grid);
    }
    
    return circles;
}
