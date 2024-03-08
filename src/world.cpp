#include "world.h"
#include <cassert>

int World::getNumberOfCameras() const{ return number_of_cameras; }
int World::getNumberOfLights()  const{ return number_of_lights; }
int World::getNumberOfModels()  const{ return number_of_models; }

void World::addModel(Model& mdl){
    World::models.push_back( 
        std::reference_wrapper<Model>(mdl)
    );
    number_of_models++;
}

void World::addCamera(Camera& cam){
    World::cameras.push_back( 
        std::reference_wrapper<Camera>(cam)
    );
    number_of_cameras++;
}

void World::addLighting(Light& light){
    World::lights.push_back( 
        std::reference_wrapper<Light>(light)
    );
    number_of_lights++;

}

void World::removeModel(int indx){
    if(indx >= 0 && indx < number_of_models){
        models.erase( models.begin() + indx );
        number_of_models--;
    }
}

void World::removeLighting(int indx){
    if(indx >= 0 && indx < number_of_lights){
        lights.erase( lights.begin() + indx );
        number_of_lights--;
    }
}

void World::removeCamera(int indx){
    if(indx >= 0 && indx < number_of_cameras){
        cameras.erase( cameras.begin() + indx );
        number_of_cameras--;
    }
}


Model& World::getModel(int indx) const{
    assert( indx >= 0 && indx < number_of_models && "Model index out of range");
    return models[indx];
}

Light& World::getLight(int indx) const{
    assert( indx >= 0 && indx < number_of_lights && "Light index out of range");
    return lights[indx];
}

Camera& World::getCamera(int indx) const{
    assert( indx >= 0 && indx < number_of_cameras && "Camera index out of range");
    return cameras[indx];
}


