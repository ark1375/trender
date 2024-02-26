#include "model.h"
#include <vector>
#include <array>
#include <string>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <limits>
#include "../lib/gmtl/Xforms.h"
#include "../lib/gmtl/VecOps.h"
#include "../lib/gmtl/Point.h"
#include "../lib/gmtl/TriOps.h"
#include "../lib/gmtl/Output.h"
#include <iostream>
#include <algorithm>

constexpr float MAX_FLOAT = std::numeric_limits<float>::max();
constexpr float MIN_FLOAT = std::numeric_limits<float>::min();

Model::Model(std::string path) : path(path), centeroid(0,0,0),
    minpoint(MAX_FLOAT, MAX_FLOAT, MAX_FLOAT),
    maxpoint(MIN_FLOAT, MIN_FLOAT, MIN_FLOAT) {}

void Model::checkminmax(gmtl::Point3f point){

    Model::maxpoint[0] = Model::maxpoint[0] < point[0] ? point[0] : Model::maxpoint[0];
    Model::maxpoint[1] = Model::maxpoint[1] < point[1] ? point[1] : Model::maxpoint[1];
    Model::maxpoint[2] = Model::maxpoint[2] < point[2] ? point[2] : Model::maxpoint[2];

    Model::minpoint[0] = Model::minpoint[0] > point[0] ? point[0] : Model::minpoint[0];
    Model::minpoint[1] = Model::minpoint[1] > point[1] ? point[1] : Model::minpoint[1];
    Model::minpoint[2] = Model::minpoint[2] > point[2] ? point[2] : Model::minpoint[2];

}

bool Model::readmodel(){
    if (std::filesystem::exists(path)){
        
        std::ifstream filestream(path , std::ifstream::in);
        std::stringstream sv;
        std::stringstream sf;
        std::string line;

        //read vertecies first
        while(std::getline(filestream , line)){

            if (line[0] == 'v' && line[1] == ' '){
                sv << line.substr(2) << "@" <<'\n';
                Model::num_of_vertecies++;
            }
            
            else if (line[0] == 'f'){
                sf << line.substr(2) <<'\n';
                Model::num_of_faces++;
            }

        }

        Model::parsevertecies(std::move(sv));
        Model::parsefaces(std::move(sf));

        return true;

    }
    else
        return false;
}

void Model::parsevertecies(std::stringstream&& sv){
    sv.seekg(0);

    for (int i = 0; i < Model::num_of_vertecies; i++){
        std::stringstream temp;
        std::string temp_line;

        std::getline(sv, temp_line);

        gmtl::Point3f point;

        int indx = 0;
        for (const char ch : temp_line){

            if (!(ch == '@' || ch ==' '))
                temp << ch;

            else{
                std::string vert_data = temp.str();
                point[indx] = std::stof(vert_data);
                indx++;
                temp.str(std::string());
            }
        }
        checkminmax(point);
        centeroid += point;
        Model::model_vertecies.push_back(point);

    }
    centeroid /= num_of_vertecies;
}

void Model::parsefaces(std::stringstream&& sf){
    sf.seekg(0);


    for (int i = 0 ; i < Model::num_of_faces; i++){

        std::stringstream temp;
        std::string temp_line;
        std::getline(sf, temp_line);

        bool is_end_num_reached = false;
        int indx = 0;
        std::array<int,3> points;

        for (const char ch : temp_line){
            
            if (!is_end_num_reached && ch != '/')
                temp << ch;

            else if (!is_end_num_reached && ch == '/'){

                is_end_num_reached = true;
                points[indx] = std::stoi(temp.str()) - 1;
                indx++;
                temp.str(std::string());
            }
            if (ch == ' ')
                is_end_num_reached = false;
        }
        
        Model::model_faces.push_back(points);

    }

}

void Model::normalize(bool midpointzero){

    gmtl::Vec3f trans_vec;

    if (midpointzero)
        trans_vec = centeroid;
    
    else
        trans_vec = Model::minpoint;

    Model::maxpoint -= trans_vec;
    Model::minpoint -= trans_vec;
    Model::centeroid -= trans_vec;

    gmtl::Point3f normalizer_vec = Model::maxpoint - Model::minpoint;
    float normalizer = *std::max_element(&(normalizer_vec.mData[0]) , &(normalizer_vec.mData[3]));

    Model::maxpoint  /= normalizer;
    Model::minpoint  /= normalizer;
    Model::centeroid /= normalizer;

    for(gmtl::Point3f &point : Model::model_vertecies){
        point -= trans_vec;
        point[0] = point[0] / normalizer;
        point[1] = point[1] / normalizer;
        point[2] = point[2] / normalizer;
    }

}

void Model::translate(gmtl::Vec3f tvec){

    for (gmtl::Point3f &point : Model::model_vertecies)
        point += tvec;

}

void Model::transform(gmtl::Matrix33f tmat){

    for (gmtl::Point3f &point : Model::model_vertecies)
            gmtl::xform(point , tmat, point);

}

int Model::getNumberOfFaces() const {
    return num_of_faces;
}

int Model::getNumberOfVertices() const {
    return num_of_vertecies;
}

gmtl::Trif Model::getTriangle (int face_number) const{
    return gmtl::Trif(
        Model::model_vertecies[Model::model_faces[face_number][0]],
        Model::model_vertecies[Model::model_faces[face_number][1]],
        Model::model_vertecies[Model::model_faces[face_number][2]]
    );
}

std::vector<gmtl::Point3f> Model::getvertecies() const{
    return Model::model_vertecies;
}