#include "lighting.h"
#include "../lib/gmtl/Xforms.h"

Direct_Light::Direct_Light(Direct_Light& light) : directon(light.getDirection()) {}

Direct_Light::Direct_Light(gmtl::Vec3f& vec) : directon(vec) {}

void Direct_Light::transform(gmtl::Matrix33f mat){
    directon *= mat;
}

gmtl::Vec3f Direct_Light::getDirection() const{
    return directon;
}