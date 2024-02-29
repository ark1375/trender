#include "../lib/gmtl/Tri.h"
#include "../lib/gmtl/Point.h"


class Trispec : public gmtl::Trif{

public:

    Trispec(gmtl::Trif&);
    Trispec(Trispec&);
    Trispec( const gmtl::Point<float, 3>&, const gmtl::Point<float, 3>&, const gmtl::Point<float, 3>& );

    void set( const gmtl::Point<float, 3>&, const gmtl::Point<float, 3>&, const gmtl::Point<float, 3>& );
    void orderVertecies();
    float getTangs(int);
    
private:

    float tangs[3];
    void calc_tangs();
};