#include "render.h"
#include <algorithm>
#include "../lib/gmtl/VecOps.h"
#include "../lib/gmtl/Output.h"

void Renderer::drawLine(const gmtl::Point3f& p1 , const gmtl::Point3f& p2, TGAImage& image, const TGAColor& color){
    
    int m_h = image.get_height();
    int m_w = image.get_width();

    bool steep = false;

    gmtl::Point3f p1_c = p1; //this copys the value
    gmtl::Point3f p2_c = p2; //this copys the value

    if (std::abs(p1_c[0]-p2_c[0]) < std::abs(p1_c[1]-p2_c[1])) {
        p1_c = gmtl::Point3f{p1[1], p1[0], p1[2]};
        p2_c = gmtl::Point3f{p2[1], p2[0], p2[2]};
        steep = true; 
    }

    if (p1_c[0]>p2_c[0]) { // make it left−to−right 
        std::swap(p1_c, p2_c); 
    }

    float tangent = (p1_c[1] - p2_c[1]) / (p1_c[0] - p2_c[0]);
    
    for (int x = (p1_c[0] * m_w) , i = 0 ; x <= (int)(p2_c[0] * m_w) ; x++, i++){

        int y = ((p1_c[1] * m_h) + i * tangent);
        
        if (steep) { 
            image.set(y , x , color); // if transposed, de−transpose 
        } else { 
            image.set(x , y , color); 
        } 
    }
}

void Renderer::drawTriangle_border(const gmtl::Trif tri, TGAImage& image, const TGAColor& color){

    Renderer::drawLine( tri[0] , tri[1] , image , color);
    Renderer::drawLine( tri[1] , tri[2] , image , color);
    Renderer::drawLine( tri[0] , tri[2] , image , color);

}

void Renderer::drawWireframe(const Model& mdl, TGAImage& image, const TGAColor& color){

    for (int i = 0 ; i < mdl.getNumberOfFaces() ; i++)
        Renderer::drawTriangle_border(mdl.getTriangle(i) , image , color);

}