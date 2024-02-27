#include "../lib/gmtl/Tri.h"
#include "../lib/gmtl/Point.h"
#include "../lib/gmtl/Vec.h"
#include "../lib/gmtl/VecOps.h"
#include "utility.h"

inline float Util::calcTangant(const gmtl::Point3f& p1, const gmtl::Point3f& p2){
    return (p1[1] - p2[1]) / (p1[0] - p2[0]);
}