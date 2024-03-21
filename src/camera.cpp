#include "camera.h"

#include "../lib/gmtl/Matrix.h"
#include "../lib/gmtl/MatrixOps.h"
#include "../lib/gmtl/Output.h"

#include <iostream>
#include <cmath>

Camera::Camera(gmtl::Point3f cam_pos, gmtl::Vec3f cam_dir, float focal_length, int sens_x, int sens_y) :
    position(cam_pos), direction(cam_dir), focallength(focal_length), width(sens_x), height(sens_y)
{
    gmtl::normalize(Camera::direction);
    calc_mats();
}

Camera::Camera(gmtl::Matrix33f intrinsic, gmtl::Matrix34f extrinsic) : extrinsic(extrinsic), intrinsic(intrinsic) {}

void Camera::calc_mats(){
    
    // intrinsics
    intrinsic.set(
        focallength, 0 , width/2,
        0 , focallength, height/2,
        0,      0,       1
    );

    std::cout << direction << std::endl;

    rotation_angle_XY = acos(
        direction[0] / sqrt( direction[0] * direction[0] + direction[1]*direction[1])
    );
    rotation_angle_YZ = acos(
        direction[1] / sqrt( direction[1] * direction[1] + direction[2]*direction[2])
    );
    rotation_angle_XZ = acos(
        direction[0] / sqrt( direction[2] * direction[2] + direction[0]*direction[0])
    );


    gmtl::Matrix33f rot_xy;
    gmtl::Matrix33f rot_yz;
    gmtl::Matrix33f rot_xz;

    rot_xz.set(
        cos(rotation_angle_XZ) , -sin(rotation_angle_XZ), 0,
        sin(rotation_angle_XZ) ,  cos(rotation_angle_XZ), 0,
        0, 0, 1
    );
    rot_yz.set(
        cos(rotation_angle_YZ), 0, -sin(rotation_angle_YZ),
        0, 1, 0,
        sin(rotation_angle_YZ), 0, cos(rotation_angle_YZ)
    );
    rot_xy.set(
        1 , 0 , 0,
        0, cos(rotation_angle_XY), -sin(rotation_angle_XY),
        0, sin(rotation_angle_XY), cos(rotation_angle_XY)
    );
    
    gmtl::Matrix33f rot_mat = rot_xy * rot_xz * rot_yz;

    Camera::extrinsic.set(
        rot_mat[0][0], rot_mat[0][1], rot_mat[0][2], position[0],
        rot_mat[1][0], rot_mat[1][1], rot_mat[1][2], position[1],
        rot_mat[2][0], rot_mat[2][1], rot_mat[2][2], position[2]
    );
}

gmtl::Matrix34f Camera::getExtrinsic() const{
    return extrinsic;
}

gmtl::Matrix33f Camera::getIntrinsic() const{
    return intrinsic;
}

