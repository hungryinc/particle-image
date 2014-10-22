//
//  Grid.h
//  ParticleImage
//
//  Created by Zachary Blank on 8/27/14.
//  Copyright (c) 2014 Hungry. All rights reserved.
//

#ifndef __ParticleImage__Grid__
#define __ParticleImage__Grid__

#include <iostream>
#include <vector>
#include "Pixel.h"

#endif /* defined(__ParticleImage__Grid__) */

class Grid
{
public:
    std::vector<std::vector<Pixel>> matrix;
    std::vector<Pixel> opaque;
};