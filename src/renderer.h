#include "tgaimage.h"
#include "model.h"
#include "lighting.h"
#include "world.h"
#include "dbuffer.h"

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

    DepthBuffer createZbuffer(int,int,World);
    void rasterize(int,int,TGAImage&, DepthBuffer&);
    
    void draw_model_mesh(Model&, TGAImage&, DepthBuffer&);
    
    template <typename T>
    void draw_triangle(Trispec<T>&, TGAImage&, DepthBuffer&);
//______________________________________________________________________________

    void draw_wireframe_model(Model&, TGAImage&);
    
    template <typename T>
    void draw_wireframe_triangle(Trispec<T>, TGAImage&);
    
    template <typename T>
    void draw_wireframe_line(gmtl::Point<T,3>, gmtl::Point<T,3>, TGAImage&);
    
    
    std::vector<World> worlds{};
    int number_of_worlds = 0;

};