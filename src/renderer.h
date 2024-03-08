#include "tgaimage.h"
#include "model.h"
#include "lighting.h"
#include "world.h"

#include <vector>

#include "../lib/gmtl/Point.h"
#include "../lib/gmtl/Vec.h"
#include "../lib/gmtl/Matrix.h"
#include "../lib/gmtl/Tri.h"
#include "../lib/gmtl/VecOps.h"
#include "../lib/gmtl/MatrixOps.h"
#include "../lib/gmtl/TriOps.h"

class Renderer{

public:

    TGAColor DEFAULT_COLOR{255,255,255,255};

    Renderer() = default;
    Renderer(Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    void addWorld(World);
    void removeWorld(int);
    World getWorld(int);

    void draw_wireframe(int, int, TGAImage&);
    void draw_meshs(int, int, TGAImage&);

private:

    std::vector<World> worlds;
    int number_of_worlds = 0;

};