#pragma once

#include "world.h"
#include "model.h"
#include "../lib/gmtl/Point.h"
#include "../lib/gmtl/Matrix.h"
#include "../lib/gmtl/Vec.h"
#include "../lib/gmtl/VecOps.h"

class Camera{
public:

    Camera(Camera&);
    Camera(gmtl::Point3f&, gmtl::Vec3f&, float, int , int);
    Camera(gmtl::Point3f&&, gmtl::Vec3f&&, float, int , int);

    gmtl::Matrix<float , 3 , 4> getExtrinsic();
    gmtl::Matrix<float , 3 , 3> getIntrinsic();

    // World transform_world(World&);
    Model transform_model(Model&);
    

private:
    gmtl::Point3f position;
    gmtl::Vec3f direction;

    gmtl::Matrix34f extrinsic;
    gmtl::Matrix33f intrinsic;
    
    float rotation_angle_X;
    float rotation_angle_Y;
    float rotation_angle_Z;
    
    float focallength;
    int width;
    int height;
};