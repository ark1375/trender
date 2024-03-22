#include "camera.h"

#include "../lib/gmtl/Matrix.h"
#include "../lib/gmtl/MatrixOps.h"
#include "../lib/gmtl/Output.h"
#include "../lib/gmtl/PlaneOps.h"
#include "../lib/gmtl/Xforms.h"

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

    rotation_angle_YX = acos(
        direction[0] / sqrt(direction[0] * direction[0] + direction[1] * direction[1])
    );
    rotation_angle_ZY = acos(
        direction[1] / sqrt(direction[2] * direction[2] + direction[1] * direction[1])
    );
    rotation_angle_ZX = acos(
        direction[0] / sqrt(direction[0] * direction[0] + direction[2] * direction[2])
    );


    gmtl::Matrix33f rot_yx;
    gmtl::Matrix33f rot_zy;
    gmtl::Matrix33f rot_zx;

    rot_yx.set(
        cos(rotation_angle_YX) , -sin(rotation_angle_YX), 0,
        sin(rotation_angle_YX) ,  cos(rotation_angle_YX), 0,
        0, 0, 1
    );
    rot_zx.set(
        cos(rotation_angle_ZX), 0, -sin(rotation_angle_ZX),
        0, 1, 0,
        sin(rotation_angle_ZX), 0, cos(rotation_angle_ZX)
    );
    rot_zy.set(
        1 , 0 , 0,
        0, cos(rotation_angle_ZY), -sin(rotation_angle_ZY),
        0, sin(rotation_angle_ZY), cos(rotation_angle_ZY)
    );

    gmtl::Matrix33f rot_mat = rot_yx * rot_zx * rot_zy;
    // gmtl::mult(rot_mat, (float)-1.0);

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

template< typename T>
void Camera::transformPoint(gmtl::Point<T,3>& point){
    
    gmtl::Point<T,4> temp{point[0],point[1],point[2], 1};
    temp = extrinsic * temp;
    gmtl::Point<T,3> trans_ext { temp[0], temp[1], temp[2] };
    // std::cout << temp << std::endl;
    trans_ext = intrinsic * trans_ext;
    point = trans_ext;
}

template void Camera::transformPoint<float>(gmtl::Point<float,3>&);
