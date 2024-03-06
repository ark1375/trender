#include "model.h"
#include "Trispec.h"
#include <array>
#include <memory>
class DepthBuffer{
public:

    DepthBuffer(int , int);
    // bool visFunction();
    void calcDepthBuffer(Model&);

    template<typename T>
    static float zval(Trispec<T>&, int, int);

    // float getDepthData(int, int);
    int get_image_data(int, int);
    ~DepthBuffer();

private:

    //Here I should probablu use unique pointers
    int bheight , bwidth;
    std::unique_ptr<float[]> buffer;
    void initialize_bufffer_inf();

    template<typename T>
    void calcDepthBuffer_triangle(Trispec<T>&);

};