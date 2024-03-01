#include "render.h"
#include "utility.h"
#include "Trispec.h"
#include "lighting.h"

#include <algorithm>
#include <math.h>

#include "../lib/gmtl/VecOps.h"
#include "../lib/gmtl/Output.h"
#include "../lib/gmtl/Matrix.h"
#include "../lib/gmtl/TriOps.h"

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

        int y = ((p1_c[1]) + i * tangent);
        
        if (steep) { 
            image.set(y , x , color); // if transposed, de−transpose 
        } else { 
            image.set(x , y , color); 
        } 
    }
}

void Renderer::drawTriangle_border(const Trispec_f tri, TGAImage& image, const TGAColor& color){

    Renderer::drawLine( tri[0] , tri[1] , image , color);
    Renderer::drawLine( tri[1] , tri[2] , image , color);
    Renderer::drawLine( tri[0] , tri[2] , image , color);

}

void Renderer::drawWireframe(const Model& mdl, TGAImage& image, const TGAColor& color){

    for (int i = 0 ; i < mdl.getNumberOfFaces() ; i++)
        Renderer::drawTriangle_border(mdl.getTriangle(i) , image , color);
}

void Renderer::drawTriangle_filled(const  Trispec_f tri, TGAImage& image, const TGAColor& color){


    Trispec_f tri_c(tri);

    float m_h = image.get_height();
    float m_w = image.get_width();

    gmtl::Matrix33f tmat;
    tmat.set(
        m_h , 0.0 , 0.0,
        0.0 , m_w , 0.0,
        0.0 , 0.0 , 1.0
    );

    tri_c.transform(tmat);

    //i represents steps in y; we begin in topmost corner
    for (int i = (tri_c[0][1]) ; i >= (tri_c[2][1]) ; i--){
      
        int left_most; 
        int right_most;

        if (tri_c.getTangs(0) == 0 || tri_c.getTangs(1) == 0 || tri_c.getTangs(2) == 0) continue;
        if (std::isnan(tri_c.getTangs(0)) || std::isnan(tri_c.getTangs(1)) || std::isnan(tri_c.getTangs(2))) continue;

        //top half -> should draw CB,CA
        if ( i >= (tri_c[1][1])){
            left_most =  ((i - tri_c[0][1]) / tri_c.getTangs(TANG_INDX::AB)) + tri_c[0][0];
            right_most = ((i - tri_c[0][1]) / tri_c.getTangs(TANG_INDX::AC)) + tri_c[0][0];
        }

        //botom half
        else {
            left_most =  ((i - tri_c[2][1]) / tri_c.getTangs(TANG_INDX::BC)) + tri_c[2][0];
            right_most = ((i - tri_c[2][1]) / tri_c.getTangs(TANG_INDX::AC)) + tri_c[2][0];
        }
        
        if( left_most >= right_most ) std::swap(left_most, right_most);

        for (int j = (left_most) ; j <= (right_most) ; j++){
            // std::cout << j << "\t" << right_most << std::endl;
            image.set(j, i, color);
        }
    }

    
}

void Renderer::drawFaces(const Model& mdl, TGAImage& image , const TGAColor& color, Light& light){
    for( int i = 0; i < mdl.getNumberOfFaces(); i++){

        Trispec_f tr = mdl.getTriangle(i);
        float intens = Direct_Light::calcIntensity(tr, reinterpret_cast<Direct_Light&>(light));
        if (intens >= -1){
            TGAColor cl = color;
            cl.r *= abs(intens);
            cl.g *= abs(intens);
            cl.b *= abs(intens);
            Renderer::drawTriangle_filled( tr , image , cl);
        }
    }
}