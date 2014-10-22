//
//  Circle.h
//  ParticleImage
//
//  Created by Zachary Blank on 8/30/14.
//  Copyright (c) 2014 Hungry. All rights reserved.
//

#ifndef ParticleImage_Circle_h
#define ParticleImage_Circle_h

#endif

#include <vector>

struct Circle
{
    double x;
    
    double y;
    unsigned long r;
    unsigned long radians;
    std::vector<Circle> children;
    
    template<class Archive>
    void serialize( Archive & ar )
    {
        ar( x, y, r );
    }
};
