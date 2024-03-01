#include "lighting.h"
#include "Trispec.h"

#include "../lib/gmtl/Xforms.h"
#include "../lib/gmtl/VecOps.h"
#include "../lib/gmtl/TriOps.h"
#include "tgaimage.h"

Direct_Light::Direct_Light(Direct_Light& light) : directon(light.getDirection()) {}

Direct_Light::Direct_Light(gmtl::Vec3f& vec) : directon(vec) {}
Direct_Light::Direct_Light(gmtl::Vec3f&& vec) : directon(vec) {}

void Direct_Light::transform(gmtl::Matrix33f mat){
    directon = mat * directon;
}

gmtl::Vec3f Direct_Light::getDirection() const{
    return directon;
}

float Direct_Light::calcIntensity(const Trispec_f& tri, const Direct_Light& light){

    gmtl::Vec3f tr_norm = gmtl::normal(tri);
    gmtl::Vec3f light_dir = light.getDirection();
    float intens = gmtl::dot(tr_norm, light_dir);
    return intens;
}