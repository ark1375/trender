#pragma once

#include <functional>
#include <vector>

#include "model.h"
#include "lighting.h"
#include "camera.h"

// using Camera_REF = std::reference_wrapper<Camera>;
using Camera_REF = std::reference_wrapper<Camera>;
using Model_REF = std::reference_wrapper<Model>;
using Light_REF = std::reference_wrapper<Light>;

class World{

public:

    World() = default;
    World(const World&) = default;
    World& operator=(const World&) = default;

    int getNumberOfModels() const;
    int getNumberOfCameras() const;
    int getNumberOfLights() const;

    void addModel(Model&);
    void addLighting(Light&);
    void addCamera(Camera&);

    void removeModel(int);
    void removeCamera(int);
    void removeLighting(int);

    Model& getModel(int) const;
    Camera& getCamera(int) const;
    Light& getLight(int) const;

private:

    std::vector<Model_REF> models;
    std::vector<Camera_REF> cameras;
    std::vector<Light_REF> lights;

    int number_of_models;
    int number_of_cameras;
    int number_of_lights;
    
};