#include <vector>
#include <array>
#include <string>
#include <sstream>

#include "../lib/gmtl/Point.h"
#include "../lib/gmtl/Tri.h"
#include "../lib/gmtl/Matrix.h"
class Model{
private:
    std::vector<gmtl::Point3f> model_vertecies;
    std::vector<gmtl::Trif> model_faces;
    
    gmtl::Point3f origin;
    gmtl::Point3f maxpoint;
    gmtl::Point3f minpoint;

    std::string path;
    int num_of_vertecies;
    int num_of_faces;

    void parsevertecies(std::stringstream&&);
    void parsefaces(std::stringstream&&);
    void checkminmax(gmtl::Point3f);

public:
    Model(std::string);
    
    Model(Model&) = delete;
    Model(Model&&) = delete;

    bool readmodel();
    void translate(gmtl::Vec3f);
    void transform(gmtl::Matrix33f);
    void normalize(bool);
    
    const std::vector<gmtl::Trif>& getmodel() const;

    void operator=(Model&) = delete;
    void operator=(Model&&) = delete;


    
};