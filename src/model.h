#include <vector>
#include <array>
#include "../lib/gmtl/Point.h"
#include <string>
class Model{
private:
    std::vector<gmtl::Point3f> model;

public:
    Model() = default;
    Model(std::string &&path);
    Model(std::string &path);

    
    
};