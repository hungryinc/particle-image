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

Grid grid;

std::vector<Pixel> circumferencePoints(Circle circle) {
    std::vector<Pixel> circumferencePoints;
    
    int left = circle.x - circle.r;
    int right = circle.x + circle.r;
    int top = circle.y - circle.r;
    int bottom = circle.y + circle.r;
    
//    std::cout << "start: " << circle.x << ", " << circle.y << std::endl;
    
    for (int row = top; row <= bottom; row++) {
        for (int col = left; col <= right; col++) {
            double dist = pow(circle.x - col, 2) + pow(circle.y - row, 2);
            
            if (dist <= pow(circle.r, 2)) {
                
                Pixel pixel;
                pixel.x = round(col);
                pixel.y = round(row);
                
                circumferencePoints.push_back(pixel);
                
//                std::cout << pixel.x << ", " << pixel.y << std::endl;
            }
        }
    }

//    exit(1);
    return circumferencePoints;
}

void fill(std::vector<Pixel>) {
    
}

bool isCircleInContainer(Circle circle) {

    std::vector<Pixel> _circumferencePoints = circumferencePoints(circle);
    
    //loop through pixels and see if they are either transparent or filled
    for (int i = 0; i < _circumferencePoints.size(); i++) {
        if (_circumferencePoints[i].y >= grid.matrix.size()) {
            return false;
        }
        
        if (_circumferencePoints[i].x >= grid.matrix[_circumferencePoints[i].y].size()) {
            return false;
        }
        
        if (grid.matrix[_circumferencePoints[i].y][_circumferencePoints[i].x].filled) {
            return false;
        }
        
        if (grid.matrix[_circumferencePoints[i].y][_circumferencePoints[i].x].a == 0) {
            return false;
        }
    }
    
    // fill all the points
    for (int i = 0; i < _circumferencePoints.size(); i++) {
        grid.matrix[_circumferencePoints[i].y][_circumferencePoints[i].x].filled = true;
    }
    
    return true;
}

std::vector<Circle> circles;

std::vector<Circle> _circlePack() {
    // Get a random starting point
    Pixel startPixel = grid.opaque[rand() % grid.opaque.size()];
    
    Circle startCircle;
    startCircle.x = startPixel.x;
    startCircle.y = startPixel.y;
    startCircle.r = 10;
    
    if (isCircleInContainer(startCircle)) {
        circles.push_back(startCircle);
    }
    
    if (circles.size() < 10) {
        _circlePack();
    }
    
    return circles;
}

std::vector<Circle> circlePack(Grid _grid) {
    // set the global container we're filling
    grid = _grid;
    
    std::vector<Circle> circles = _circlePack();
    
    Circle zero;
    zero.x = 0;
    zero.y = 0;
    zero.r = 10;
    
    circles.push_back(zero);
    
    return circles;
}
