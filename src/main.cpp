#include <iostream>
#include "tgaimage.h"
#include "model.h"
#include "render.h"
#include "Trispec.h"
#include "lighting.h"
#include "dbuffer.h"

#include "../lib/gmtl/Tri.h"
#include "../lib/gmtl/Point.h"
#include "../lib/gmtl/Output.h"

const TGAColor WHITE    = TGAColor(255, 255, 255, 255);
const TGAColor RED      = TGAColor(255, 0, 0, 255);
const TGAColor GREEN    = TGAColor(0, 255, 0, 255);
const TGAColor BLUE     = TGAColor(0, 0, 255, 255);

int main(){

    TGAImage image(800, 800, TGAImage::RGB);

    Model mdl("../res/head.obj");
    mdl.readmodel();
    mdl.normalize(false);
    DepthBuffer dpb(800,800);
    dpb.calcDepthBuffer(mdl);
    for (int i = 0; i < 800 ; i++)
        for (int j = 0 ; j < 800 ; j++){
            int dval = dpb.get_image_data(i,j);
            TGAColor cl (dval,dval,dval, 255);
            image.set(i , j , cl);
        }
    // Direct_Light dl(gmtl::Vec3f{0,0,1});
    // dl.normalize();

    // Renderer::drawFaces(mdl, image , WHITE, dl);



    // gmtl::Point3f p1{0.1,0.1,0.1} , p2{0.2,0.3,0.3} , p3{0.05,0.4,0.2};
    // gmtl::Trif tr{p1,p2,p3};
    // Trispec_f tri(tr);
    // std::cout << tri.getBBXmax() << std::endl;
    // std::cout << tri.getBBXmin() << std::endl;


    // Renderer::drawTriangle_filled(tri , image, WHITE);
    // std::cout << tri.mVerts[0] << std::endl;
    // std::cout << tri.mVerts[1] << std::endl;
    // std::cout << tri.mVerts[2] << std::endl;
    // std::cout << tri.getTangs(1) << std::endl;
    // std::cout << tri.getTangs(2) << std::endl;
    // std::cout << tri.getTangs(0) << std::endl;



    // Renderer::drawLine(gmtl::Point3f{0,0,0} , gmtl::Point3f{1,1,1} , image, WHITE);
    // Renderer::drawWireframe(mdl, image , WHITE);

    // std::cout << mdl.getNumberOfFaces() << std::endl;
    // std::cout << mdl.getNumberOfVertices() << std::endl;
    // for (int i = 0 ; i < mdl.getNumberOfFaces(); i++){
    //     Trispec_f tr = mdl.getTriangle(i);
    //     if (tr[0][2] < 0 || tr[1][2] < 0 || tr[0][2] < 0)
    //         std::cout << i <<"\t"<< tr << std::endl;
    // }

    // for (gmtl::Point3f p : mdl.getvertecies()){
    //     std::cout << p << std::endl;
    //     break;
    // }

    image.flip_vertically();
    image.write_tga_file("output.tga");

    return 0;
}

