#include <iostream>
#include "model.h"
#include "../lib/gmtl/Output.h"

int main(){
    Model mdl("../res/head.obj");
    mdl.readmodel();
    // std::cout << mdl.getNumberOfFaces() << std::endl;
    // std::cout << mdl.getNumberOfVertices() << std::endl;
    // for (int i = 0 ; i < mdl.getNumberOfFaces() ; i++)
    //     std::cout << i <<"\t"<< mdl.getTriangle(i) << std::endl;

    for (gmtl::Point3f p : mdl.getvertecies()){
        std::cout << p << std::endl;
    }
}

