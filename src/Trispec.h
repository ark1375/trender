#include "../lib/gmtl/Tri.h"
#include "../lib/gmtl/Point.h"

template< typename DATA_TYPE >
class Trispec : gmtl::Tri{

public:

    Trispec(Trispec&);
    Trispec( const Point<DATA_TYPE, 3>& p1, const Point<DATA_TYPE, 3>& p2, const Point<DATA_TYPE, 3>& p3);
    void set( const Point<DATA_TYPE, 3>& p1, const Point<DATA_TYPE, 3>& p2, const Point<DATA_TYPE, 3>& p3 );
    void orderVertecies();
    
private:

    float tangs[3];
    void calc_tangs();

};