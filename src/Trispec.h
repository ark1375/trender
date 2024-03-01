#pragma once

#include "../lib/gmtl/Tri.h"
#include "../lib/gmtl/Point.h"

template <typename TYPE>
class Trispec : public gmtl::Tri<TYPE>{

public:

    Trispec(gmtl::Tri<TYPE>&);
    Trispec(Trispec<TYPE>&);
    Trispec(gmtl::Tri<TYPE>&&);
    Trispec( const gmtl::Point<TYPE, 3>&, const gmtl::Point<TYPE, 3>&, const gmtl::Point<TYPE, 3>& );

    void set( const gmtl::Point<TYPE, 3>&, const gmtl::Point<TYPE, 3>&, const gmtl::Point<TYPE, 3>& );
    void orderVertecies();
    float getTangs(int);
    
private:

    float tangs[3];
    void calc_tangs();
};

using Trispec_f = Trispec<float>;
using Trispec_d = Trispec<double>;
using Trispec_i = Trispec<int>;