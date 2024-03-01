#pragma once
#include "../lib/gmtl/Matrix.h"
#include "../lib/gmtl/Vec.h"
#include "../lib/gmtl/Point.h"

class Light{
    
};

class Direct_Light : Light{

public:
    Direct_Light(Direct_Light&);
    Direct_Light(gmtl::Vec3f&);
    void transform(gmtl::Matrix33f);
    gmtl::Vec3f getDirection() const;

private:
    gmtl::Vec3f directon;

};