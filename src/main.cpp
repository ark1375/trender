#include <iostream>
#include "tgaimage.h"
#include "model.h"
#include "render.h"
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
    // Renderer::drawLine(gmtl::Point3f{0,0,0} , gmtl::Point3f{1,1,1} , image, WHITE);
    Renderer::drawWireframe(mdl, image , WHITE);

    // std::cout << mdl.getNumberOfFaces() << std::endl;
    // std::cout << mdl.getNumberOfVertices() << std::endl;
    // for (int i = 0 ; i < 3; i++)
    //     std::cout << i <<"\t"<< mdl.getTriangle(i) << std::endl;

    // for (gmtl::Point3f p : mdl.getvertecies()){
    //     std::cout << p << std::endl;
    //     break;
    // }

    image.flip_vertically();
    image.write_tga_file("output.tga");

    return 0;
}

