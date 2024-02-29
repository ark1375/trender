#include "Trispec.h"
#include "cassert"
#include "../lib/gmtl/Tri.h"
#include "../lib/gmtl/Point.h"
#include "../lib/gmtl/TriOps.h"
#include "../lib/gmtl/VecOps.h"


Trispec::Trispec(Trispec& tri){
    Trispec::mVerts[0] = tri.mVerts[0];
    Trispec::mVerts[1] = tri.mVerts[1];
    Trispec::mVerts[2] = tri.mVerts[2];

    orderVertecies();
    calc_tangs();
}


Trispec::Trispec( gmtl::Trif& tri) : gmtl::Trif(tri){
    
    orderVertecies();
    calc_tangs();

}

Trispec::Trispec( 
    const gmtl::Point<float, 3>& p1,
    const gmtl::Point<float, 3>& p2,
    const gmtl::Point<float, 3>& p3) : gmtl::Trif(p1,p2,p3){
    
    orderVertecies();
    calc_tangs();

}


void Trispec::set( const gmtl::Point<float, 3>& p1, const gmtl::Point<float, 3>& p2, const gmtl::Point<float, 3>& p3 ){
    mVerts[0] = p1;
    mVerts[1] = p2;
    mVerts[2] = p3;

    orderVertecies();
    calc_tangs();
}





void Trispec::orderVertecies(){

    if (mVerts[0][1] < mVerts[1][1])
        std::swap(mVerts[0] , mVerts[1]);

    if (mVerts[0][1] < mVerts[2][1])
        std::swap(mVerts[0], mVerts[2]);

}

void Trispec::calc_tangs(){

    tangs[0] = (mVerts[0][1] - mVerts[1][1] ) / (mVerts[0][0] - mVerts[1][0] );
    tangs[1] = (mVerts[1][1] - mVerts[2][1] ) / (mVerts[1][0] - mVerts[2][0] );
    tangs[2] = (mVerts[0][1] - mVerts[2][1] ) / (mVerts[0][0] - mVerts[2][0] );

}

float Trispec::getTangs(int edge){
    assert(edge >= 0 && edge <= 2);
    if(edge == 0 || edge == 1 || edge == 2)
        return tangs[edge];

    else return 0;
}
