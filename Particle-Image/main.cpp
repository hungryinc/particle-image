//
//  main.cpp
//  ParticleImage
//
//  Created by Zachary Blank on 8/27/14.
//  Copyright (c) 2014 Hungry. All rights reserved.
//
#include "lodepng.h"
#include "circlePack.h"
#include <cereal/types/vector.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/archives/json.hpp>
#include <iostream>
using namespace std;

int fRand (int i) { return std::rand()%i; }

const char* defaultFile = "/Users/zacharyblank/Projects/Hungryinc/Particle-Image/mb.png";

Grid decode(const char* filename)
{
    std::vector<unsigned char> image; //the raw pixels
    std:vector<std::vector<Pixel>> matrix;
    Grid grid;
    unsigned width, height;
    
    //decode
    unsigned error = lodepng::decode(image, width, height, filename);
    
    if (error) {
        std::cout << error << std::endl;
    } else {
        for (unsigned y = 0; y < height; y++) {
            std::vector<Pixel> row;
            
            for (unsigned x = 0; x < width; x++) {
                
                Pixel pixel;
                pixel.x = x;
                pixel.y = y;
                pixel.a = image[y * width * 4 + x * 4 + 3];
                
                row.push_back(pixel);
                
                if (pixel.a) {
                    grid.opaque.push_back(pixel);
                }
            }
            
            matrix.push_back(row);
        }

        grid.matrix = matrix;
    }
    
    return grid;
}

int main(int argc, const char * argv[])
{
    srand ( (unsigned)time(NULL) );
    
    Grid pixelGrid = decode(argc > 1 ? argv[1] : defaultFile);
    
    std::vector<Circle> circles = circlePack(pixelGrid);
    
    cereal::JSONOutputArchive archive( std::cout );
    
    archive( CEREAL_NVP(circles));
    
    return 0;
    
}