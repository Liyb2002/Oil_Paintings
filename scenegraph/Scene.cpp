#include "Scene.h"
#include "Camera.h"
#include "CS123ISceneParser.h"

#include "glm/gtx/transform.hpp"
#include <iostream>


Scene::Scene()
{
}

Scene::Scene(Scene &scene)
{
    // We need to set the global constants to one when we duplicate a scene,
    // otherwise the global constants will be double counted (squared)
  //  CS123SceneGlobalData global = { 1, 1, 1, 1};
    setGlobal(scene.m_global);

    // TODO [INTERSECT]
    // Make sure to copy over the lights and the scenegraph from the old scene,
    // as well as any other member variables your new scene will need.

}

Scene::~Scene()
{
    // Do not delete m_camera, it is owned by SupportCanvas3D
}

void Scene::parse(Scene *sceneToFill, CS123ISceneParser *parser) {
    // TODO: load scene into sceneToFill using setGlobal(), addLight(), addPrimitive(), and
    //   finishParsing()
    CS123SceneGlobalData gd;
    parser->getGlobalData(gd);
    sceneToFill -> setGlobal(gd);

    CS123SceneLightData light;
        int numLights = parser->getNumLights();
        for (int i = 0; i < numLights; i++) {
            parser->getLightData(i, light);
            sceneToFill->addLight(light);
        }

        std::cout << "parse called" << std::endl;

}

void Scene::addPrimitive(const CS123ScenePrimitive &scenePrimitive, const glm::mat4x4 &matrix) {
}

void Scene::addLight(const CS123SceneLightData &sceneLight) {
}

void Scene::setGlobal(const CS123SceneGlobalData &global) {
    m_global = global;
}

