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
    void transform(const gmtl::Matrix<TYPE,3,3>);
    
private:

    void orderVertecies();
    float tangs[3];
    void calc_tangs();
};

using Trispec_f = Trispec<float>;
using Trispec_d = Trispec<double>;
using Trispec_i = Trispec<int>;