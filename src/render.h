#pragma once

#include <vector>

#include "tgaimage.h"
#include "model.h"
#include "lighting.h"

#include "../lib/gmtl/Point.h"
#include "../lib/gmtl/Vec.h"
#include "../lib/gmtl/Matrix.h"
#include "../lib/gmtl/Tri.h"
#include "../lib/gmtl/VecOps.h"
#include "../lib/gmtl/MatrixOps.h"
#include "../lib/gmtl/TriOps.h"

class Renderer{
public:
    static void drawLine(const gmtl::Point3f& , const gmtl::Point3f&, TGAImage&, const TGAColor&);
    static void drawTriangle_border( const Trispec_f, TGAImage&, const TGAColor& );
    static void drawWireframe(const Model&, TGAImage&, const TGAColor&);

    static void drawTriangle_filled(const Trispec_f, TGAImage&, const TGAColor&);
    static void drawFaces(const Model&, TGAImage& , const TGAColor&, Light&);

    static void drawTriangle_filled_gradient(const Trispec_f, TGAImage&, const TGAColor&, const TGAColor&);
    static void drawFaces_gradiant(const Model&, TGAImage&, const TGAColor&, const TGAColor&);
};