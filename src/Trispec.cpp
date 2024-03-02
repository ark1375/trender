#include "Trispec.h"

#include "cassert"

#include "../lib/gmtl/Tri.h"
#include "../lib/gmtl/Point.h"
#include "../lib/gmtl/TriOps.h"
#include "../lib/gmtl/VecOps.h"
#include "../lib/gmtl/Matrix.h"
#include "../lib/gmtl/Xforms.h"
#include "../lib/gmtl/Output.h"

template <typename TYPE>
Trispec<TYPE>::Trispec(const Trispec& tri){
    Trispec::mVerts[0] = tri.mVerts[0];
    Trispec::mVerts[1] = tri.mVerts[1];
    Trispec::mVerts[2] = tri.mVerts[2];

    orderVertecies();
    calc_tangs();
    set_bbxs();
    calc_bycent();

}


template <typename TYPE>
Trispec<TYPE>::Trispec( const gmtl::Tri<TYPE>& tri) : gmtl::Tri<TYPE>(tri){
    
    orderVertecies();
    calc_tangs();
    set_bbxs();
    calc_bycent();

}

template <typename TYPE>
Trispec<TYPE>::Trispec( gmtl::Tri<TYPE>&& tri) : gmtl::Tri<TYPE>(tri){
    
    orderVertecies();
    calc_tangs();
    set_bbxs();
    calc_bycent();

}

template <typename TYPE>
Trispec<TYPE>::Trispec( 
    const gmtl::Point<TYPE, 3>& p1,
    const gmtl::Point<TYPE, 3>& p2,
    const gmtl::Point<TYPE, 3>& p3) : gmtl::Tri<TYPE>(p1,p2,p3){
    
    orderVertecies();
    calc_tangs();
    set_bbxs();
    calc_bycent();

}

template <typename TYPE>
void Trispec<TYPE>::set( const gmtl::Point<TYPE, 3>& p1, const gmtl::Point<TYPE, 3>& p2, const gmtl::Point<TYPE, 3>& p3 ){
    gmtl::Tri<TYPE>::mVerts[0] = p1;
    gmtl::Tri<TYPE>::mVerts[1] = p2;
    gmtl::Tri<TYPE>::mVerts[2] = p3;

    orderVertecies();
    calc_tangs();
    set_bbxs();
    calc_bycent();

}

template <typename TYPE>
void Trispec<TYPE>::orderVertecies(){
    using base = gmtl::Tri<TYPE>;
    if (base::mVerts[0][1] < base::mVerts[1][1])
        std::swap(base::mVerts[0] , base::mVerts[1]);

    if (base::mVerts[0][1] < base::mVerts[2][1])
        std::swap(base::mVerts[0], base::mVerts[2]);

    if (base::mVerts[1][1] < base::mVerts[2][1])
        std::swap(base::mVerts[1], base::mVerts[2]);

}

template <typename TYPE>
void Trispec<TYPE>::calc_tangs(){

    using base = gmtl::Tri<TYPE>;
    
    //AB
    tangs[0] = (base::mVerts[0][1] - base::mVerts[1][1] ) / (base::mVerts[0][0] - base::mVerts[1][0] );
    //BC
    tangs[1] = (base::mVerts[1][1] - base::mVerts[2][1] ) / (base::mVerts[1][0] - base::mVerts[2][0] );
    //AC
    tangs[2] = (base::mVerts[0][1] - base::mVerts[2][1] ) / (base::mVerts[0][0] - base::mVerts[2][0] );

}

template <typename TYPE>
float Trispec<TYPE>::getTangs(int edge) const{
    assert(edge >= 0 && edge <= 2);
    if(edge == 0 || edge == 1 || edge == 2)
        return tangs[edge];

    else return 0;
}

template <typename TYPE>
void Trispec<TYPE>::transform(const gmtl::Matrix<TYPE,3,3> mat){
    using base = gmtl::Tri<TYPE>;

    base::mVerts[0] *= mat;
    base::mVerts[1] *= mat;
    base::mVerts[2] *= mat;

    orderVertecies();
    calc_tangs();
    set_bbxs();
    calc_bycent();

}

template <typename TYPE>
bool Trispec<TYPE>::contains(const gmtl::Point<TYPE,3>& p){
    using base = gmtl::Tri<TYPE>;
    gmtl::Vec<TYPE,3> PA = base::mVerts[0] - p;

    TYPE u = (-PA[0] * Trispec<TYPE>::invAC[1]) + (PA[1] * Trispec<TYPE>::invAC[0]);
    TYPE v = (-PA[1] * Trispec<TYPE>::invAB[0]) + (PA[0] * Trispec<TYPE>::invAB[1]);

    if (u >= -0.01 && v >= -0.01 && 1-u-v >=-0.01) return true; else return false;
}

template <typename TYPE>
void Trispec<TYPE>::set_bbxs(){

    using base = gmtl::Tri<TYPE>;
    using main = Trispec<TYPE>;

    for (int i = 0 ; i <= 2 ; i++){

        main::bbx_max[i] = base::mVerts[0][i];

        if (main::bbx_max[i] < base::mVerts[1][i])
            main::bbx_max[i] = base::mVerts[1][i];
        
        if (main::bbx_max[i] < base::mVerts[2][i])
            main::bbx_max[i] = base::mVerts[2][i];
    }

    for (int i = 0 ; i <= 2 ; i++){

        main::bbx_min[i] = base::mVerts[0][i];

        if (main::bbx_min[i] > base::mVerts[1][i])
            main::bbx_min[i] = base::mVerts[1][i];
        
        if (main::bbx_min[i] > base::mVerts[2][i])
            main::bbx_min[i] = base::mVerts[2][i];
    }

}

template <typename TYPE>
gmtl::Vec<TYPE,3> Trispec<TYPE>::getBBXmax() const{
    return Trispec<TYPE>::bbx_max;
}   

template <typename TYPE>
gmtl::Vec<TYPE,3> Trispec<TYPE>::getBBXmin() const{
    return Trispec<TYPE>::bbx_min;
}

template <typename TYPE>
void Trispec<TYPE>::calc_bycent(){
    using base = gmtl::Tri<TYPE>;

    Trispec<TYPE>::AB = base::mVerts[1] - base::mVerts[0];
    Trispec<TYPE>::AC = base::mVerts[2] - base::mVerts[0];

    TYPE determinat = AB[0] * AC[1] - AC[0] * AC[1];

    Trispec<TYPE>::invAB = Trispec<TYPE>::AB / determinat;
    Trispec<TYPE>::invAC = Trispec<TYPE>::AC / determinat;

}

template class Trispec<float>;
template class Trispec<int>;
template class Trispec<double>;

