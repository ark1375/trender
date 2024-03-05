#include <array>
#include "../lib/gmtl/Ve"
using PixelPoint = std::array<int , 2>;

class DepthBuffer{
public:

    bool visFunction();

private:
    std::pair<PixelPoint, float> buffer;
    
};