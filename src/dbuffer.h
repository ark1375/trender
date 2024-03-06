#include "model.h"
#include "Trispec.h"
#include <array>
#include <memory>
class DepthBuffer{
public:

    DepthBuffer(int , int);
    // bool visFunction();
    void calcDepthBuffer(Model&);
    float getDepthData(int, int);
    ~DepthBuffer();

private:

    //Here I should probablu use unique pointers
    int bheight , bwidth;
    std::unique_ptr<float[]> buffer;
    void initialize_bufffer_inf();
    
    template<typename T>
    void calcDepthBuffer_triangle(Trispec<T>&);

};