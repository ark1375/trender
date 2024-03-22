#pragma once

// #include "world.h"
#include "model.h"
#include "../lib/gmtl/Point.h"
#include "../lib/gmtl/Matrix.h"
#include "../lib/gmtl/Vec.h"
#include "../lib/gmtl/VecOps.h"

class Camera{
public:
    Camera() = default;
    Camera(const Camera&)  = default;
    Camera(gmtl::Point3f, gmtl::Vec3f, float, int , int);
    Camera(gmtl::Matrix33f, gmtl::Matrix34f);

    gmtl::Matrix<float , 3 , 4> getExtrinsic() const;
    gmtl::Matrix<float , 3 , 3> getIntrinsic() const;

    // // World transform_world(World&);
    template< typename T>
    void transformPoint(gmtl::Point<T,3>&);

private:

    gmtl::Point3f position;
    gmtl::Vec3f direction;

    gmtl::Matrix34f extrinsic;
    gmtl::Matrix33f intrinsic;
    
    float rotation_angle_YX;
    float rotation_angle_ZY;
    float rotation_angle_ZX;
    
    float focallength;
    int width;
    int height;

    void calc_mats();
    
};