#pragma once
#include "Trispec.h"
#include "../lib/gmtl/Matrix.h"
#include "../lib/gmtl/Vec.h"
#include "../lib/gmtl/Point.h"

class Light{
    
};

class Direct_Light : public Light{

public:
    Direct_Light(Direct_Light&);
    Direct_Light(gmtl::Vec3f&);
    Direct_Light(gmtl::Vec3f&&);
    
    void transform(gmtl::Matrix33f);
    gmtl::Vec3f getDirection() const;
    void normalize();

    static float calcIntensity(const Trispec_f&, const Direct_Light&);


private:
    gmtl::Vec3f directon;

};

