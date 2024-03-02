#pragma once

#include "../lib/gmtl/Tri.h"
#include "../lib/gmtl/Point.h"
#include "../lib/gmtl/Matrix.h"

enum TANG_INDX{
    AB, BC, AC
};

template <typename TYPE>
class Trispec : public gmtl::Tri<TYPE>{

public:

    Trispec(const gmtl::Tri<TYPE>&);
    Trispec(const Trispec<TYPE>&);
    Trispec(gmtl::Tri<TYPE>&&);
    Trispec( const gmtl::Point<TYPE, 3>&, const gmtl::Point<TYPE, 3>&, const gmtl::Point<TYPE, 3>& );

    void set( const gmtl::Point<TYPE, 3>&, const gmtl::Point<TYPE, 3>&, const gmtl::Point<TYPE, 3>& );
    float getTangs(int) const;
    gmtl::Vec<TYPE,3> getBBXmax() const;
    gmtl::Vec<TYPE,3> getBBXmin() const;
    gmtl::Vec<TYPE,3> getnormal() const;

    void transform(const gmtl::Matrix<TYPE,3,3>);
    bool contains(const gmtl::Point<TYPE,3>&);
    gmtl::Vec<TYPE,3> nnormal() const;
    
private:

    void orderVertecies();
    void set_bbxs();
    void calc_bycent();

    float tangs[3];
    gmtl::Vec<TYPE,3>  bbx_min;
    gmtl::Vec<TYPE,3> bbx_max;

    gmtl::Vec<TYPE,3>  AB;
    gmtl::Vec<TYPE,3>  AC;

    gmtl::Vec<TYPE,3>  invAB;
    gmtl::Vec<TYPE,3>  invAC;

    gmtl::Vec<TYPE,3> nn;

    void calc_tangs();
};

using Trispec_f = Trispec<float>;
using Trispec_d = Trispec<double>;
using Trispec_i = Trispec<int>;