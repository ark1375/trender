#include "Trispec.h"
#include "cassert"
#include "../lib/gmtl/Tri.h"
#include "../lib/gmtl/Point.h"
#include "../lib/gmtl/TriOps.h"
#include "../lib/gmtl/VecOps.h"

template <typename TYPE>
Trispec<TYPE>::Trispec(Trispec& tri){
    Trispec::mVerts[0] = tri.mVerts[0];
    Trispec::mVerts[1] = tri.mVerts[1];
    Trispec::mVerts[2] = tri.mVerts[2];

    orderVertecies();
    calc_tangs();
}


template <typename TYPE>
Trispec<TYPE>::Trispec( gmtl::Tri<TYPE>& tri) : gmtl::Tri<TYPE>(tri){
    
    orderVertecies();
    calc_tangs();

}

template <typename TYPE>
Trispec<TYPE>::Trispec( 
    const gmtl::Point<TYPE, 3>& p1,
    const gmtl::Point<TYPE, 3>& p2,
    const gmtl::Point<TYPE, 3>& p3) : gmtl::Tri<TYPE>(p1,p2,p3){
    
    orderVertecies();
    calc_tangs();

}

template <typename TYPE>
void Trispec<TYPE>::set( const gmtl::Point<TYPE, 3>& p1, const gmtl::Point<TYPE, 3>& p2, const gmtl::Point<TYPE, 3>& p3 ){
    gmtl::Tri<TYPE>::mVerts[0] = p1;
    gmtl::Tri<TYPE>::mVerts[1] = p2;
    gmtl::Tri<TYPE>::mVerts[2] = p3;

    orderVertecies();
    calc_tangs();
}

template <typename TYPE>
void Trispec<TYPE>::orderVertecies(){
    using base = gmtl::Tri<TYPE>;
    if (base::mVerts[0][1] < base::mVerts[1][1])
        std::swap(base::mVerts[0] , base::mVerts[1]);

    if (base::mVerts[0][1] < base::mVerts[2][1])
        std::swap(base::mVerts[0], base::mVerts[2]);

}

template <typename TYPE>
void Trispec<TYPE>::calc_tangs(){

    using base = gmtl::Tri<TYPE>;
    
    tangs[0] = (base::mVerts[0][1] - base::mVerts[1][1] ) / (base::mVerts[0][0] - base::mVerts[1][0] );
    tangs[1] = (base::mVerts[1][1] - base::mVerts[2][1] ) / (base::mVerts[1][0] - base::mVerts[2][0] );
    tangs[2] = (base::mVerts[0][1] - base::mVerts[2][1] ) / (base::mVerts[0][0] - base::mVerts[2][0] );

}

template <typename TYPE>
float Trispec<TYPE>::getTangs(int edge){
    assert(edge >= 0 && edge <= 2);
    if(edge == 0 || edge == 1 || edge == 2)
        return tangs[edge];

    else return 0;
}

template class Trispec<float>;
template class Trispec<int>;
template class Trispec<double>;

