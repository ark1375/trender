#include "renderer.h"
#include <cassert>

void Renderer::addWorld(World wld){
    worlds.push_back(wld);
    number_of_worlds++;
}

void Renderer::removeWorld(int indx){
    assert(indx >= 0 && indx < number_of_worlds && "World index out of range!\n");
    worlds.erase(worlds.begin() + indx);
}

World Renderer::getWorld(int indx){
    assert(indx >= 0 && indx < number_of_worlds && "World index out of range!\n");
    return worlds[indx];
}

template <typename T>
void Renderer::draw_wireframe_line(gmtl::Point<T,3> point_a, gmtl::Point<T,3> point_b, TGAImage& image){

    bool steep = false;

    gmtl::Point<T,3> p1_c = point_a; //this copys the value
    gmtl::Point<T,3> p2_c = point_b; //this copys the value

    if (std::abs(p1_c[0]-p2_c[0]) < std::abs(p1_c[1]-p2_c[1])) {
        p1_c = gmtl::Point3f{p1_c[1], p1_c[0], p1_c[2]};
        p2_c = gmtl::Point3f{p2_c[1], p2_c[0], p2_c[2]};
        steep = true; 
    }

    if (p1_c[0]>p2_c[0]) { // make it left−to−right 
        std::swap(p1_c, p2_c); 
    }

    float tangent = (p1_c[1] - p2_c[1]) / (p1_c[0] - p2_c[0]);
    
    for (int x = (p1_c[0]) , i = 0 ; x <= (int)(p2_c[0]) ; x++, i++){

        int y = ((p1_c[1]) + i * tangent);
        
        if (steep) { 
            image.set(y , x , DEFAULT_COLOR); // if transposed, de−transpose 
        } else { 
            image.set(x , y , DEFAULT_COLOR); 
        } 
    }
}

template <typename T>
void Renderer::draw_wireframe_triangle(Trispec<T> tri, TGAImage& image){

    draw_wireframe_line<T>( tri[0], tri[1], image );
    draw_wireframe_line<T>( tri[2], tri[1], image );
    draw_wireframe_line<T>( tri[0], tri[2], image );

}

void Renderer::draw_wireframe_model(Model& mdl, TGAImage& image){

    for (int i = 0; i < mdl.getNumberOfFaces(); i++)
        draw_wireframe_triangle<float>(mdl.getTriangle(i), image);

}

void Renderer::draw_wireframe(int wrld_indx, int camera_indx, TGAImage&){

}