#include "dbuffer.h"

#include <algorithm>
#include <limits>

#include "../lib/gmtl/Vec.h"
#include "../lib/gmtl/TriOps.h"
#include "../lib/gmtl/VecOps.h"

DepthBuffer::DepthBuffer(int h, int w) : bheight(h) , bwidth(w) {
    initialize_bufffer_inf();
}

DepthBuffer::~DepthBuffer(){
    buffer.reset(nullptr);
}

void DepthBuffer::calcDepthBuffer(Model& mdl){

}

template< typename T>
void DepthBuffer::calcDepthBuffer_triangle(Trispec<T>& tri){

    Trispec<T> tri_c = tri;
    tri_c.transform(
        gmtl::Matrix<T,3,3>{ 
            bwidth, 0,       0,
            0,      bheight, 0, 
            0,      0,       std::max(bwidth,bheight) 
    });

    for ( int i = tri_c.getBBXmin()[0] ; i < tri_c.getBBXmin()[0] ; i++ )
        for ( int j = tri_c.getBBXmin()[1] ; j < tri_c.getBBXmin()[1] ; j++ ){
            //Calculate normal to get the plane equation. K is the coeficient;
            gmtl::Vec<T, 3> normal = gmtl::normal(tri_c);
            normal /= std::max(normal[0] , std::max(normal[1] , normal[2]));
            float k = -1 * (gmtl::dot(normal , tri_c[0]));

            //solve the plane equation to calculate for depth
            float depth = ( normal[0] * i + normal[1] * j + k ) / normal[2];

            //check the depth against the depth buffer
            if( buffer[i * bheight + j] > depth)
                buffer[i * bheight + j] = depth;
        }

}

void DepthBuffer::initialize_bufffer_inf(){
    
    //initialize_the_buffer
    buffer = std::unique_ptr<float[]>(new float[bwidth * bheight]);

    //set buffer to infinity
    auto zero = [](float* b_address) { *b_address = std::numeric_limits<float>::min(); };
    std::for_each( buffer[0] , buffer[bwidth * bheight] , zero );

}