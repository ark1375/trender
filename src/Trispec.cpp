#include "Trispec.h"
#include "../lib/gmtl/Tri.h"
#include "../lib/gmtl/Point.h"
#include "../lib/gmtl/TriOps.h"
#include "../lib/gmtl/VecOps.h"


Trispec::Trispec(Trispec& tri){

}
Trispec( const Point<DATA_TYPE, 3>& p1, const Point<DATA_TYPE, 3>& p2, const Point<DATA_TYPE, 3>& p3);
void set( const Point<DATA_TYPE, 3>& p1, const Point<DATA_TYPE, 3>& p2, const Point<DATA_TYPE, 3>& p3 );
void orderVertecies();
    
