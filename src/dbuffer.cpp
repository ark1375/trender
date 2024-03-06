#include "dbuffer.h"

#include <algorithm>
#include <limits>
#include <iostream>

#include "../lib/gmtl/Vec.h"
#include "../lib/gmtl/TriOps.h"
#include "../lib/gmtl/VecOps.h"
#include "../lib/gmtl/Point.h"

template <typename T>
float DepthBuffer::zval(Trispec<T> &tri , int u , int v){

    //Calculate normal to get the plane equation. K is the coeficient;
    gmtl::Vec<T, 3> normal = gmtl::normal(tri);
    // normal /= std::max(normal[0] , std::max(normal[1] , normal[2]));
    float k = -1 * (gmtl::dot(normal , tri[0]));

    //solve the plane equation to calculate for depth
    float depth = ( normal[0] * u + normal[1] * v + k ) / normal[2];

    return -depth;
}

DepthBuffer::DepthBuffer(int h, int w) : bheight(h) , bwidth(w) {
    initialize_bufffer_inf();
}

DepthBuffer::~DepthBuffer(){
    buffer.reset(nullptr);
}

template< typename T>
void DepthBuffer::calcDepthBuffer_triangle(Trispec<T>& tri){

    Trispec<T> tri_c = tri;
    gmtl::Matrix<T,3,3> mtx;
    mtx.set(
        bwidth, 0,       0,
        0,      bheight, 0, 
        0,      0,       1 
    );
    tri_c.transform(mtx);

    for ( int i = tri_c.getBBXmin()[0] ; i < tri_c.getBBXmax()[0] ; i++ )
        for ( int j = tri_c.getBBXmin()[1] ; j < tri_c.getBBXmax()[1] ; j++ ){
            gmtl::Point3f p{i,j,0};
            if(tri_c.contains(p)){                
                float depth = DepthBuffer::zval<T>(tri_c , i , j);
                std::cout << depth << std::endl;
                //check the depth against the depth buffer
                if( buffer[i * bheight + j] < depth)
                    buffer[i * bheight + j] = depth;
            }
        }

}

void DepthBuffer::calcDepthBuffer(Model& mdl){

    for(int i = 0; i < mdl.getNumberOfFaces(); i++){
        Trispec_f tr = mdl.getTriangle(i);
        DepthBuffer::calcDepthBuffer_triangle<float>(tr);
    }

}

void DepthBuffer::initialize_bufffer_inf(){
    
    //initialize_the_buffer
    buffer = std::unique_ptr<float[]>(new float[bwidth * bheight]);

    //set buffer to infinity
    for ( int i = 0 ; i < bheight * bwidth ;  i++)
        buffer[i]=std::numeric_limits<float>::min();

}

int DepthBuffer::get_image_data(int u, int v){
    return buffer[u * bheight + v] * 200;
}