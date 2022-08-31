#ifndef RAYSCENE_H
#define RAYSCENE_H

#include "Scene.h"
#include "Canvas2D.h"

#include <vector>


/**
 * @class RayScene
 *
 *  Students will implement this class as necessary in the Ray project.
 */
class RayScene : public Scene {
public:
    RayScene(Scene &scene);

    CS123SceneGlobalData global;
    CS123SceneMaterial m_material;
    CS123SceneLightData  m_light;
    int numLights;

    virtual ~RayScene();
    virtual void render(Canvas2D* canvas, CS123SceneCameraData *camera);

    bool sdfCircle(int x, int y);
    float rayMarch(glm::vec3 ro, glm::vec3 rd);
    float sdSphere(glm::vec3 p, float r );
    float sdFloor(glm::vec3 p);


    glm::vec3 calcNormal(glm::vec3 p);
    glm::vec3 colorClean(glm::vec3 col);

    struct Sphere{ float r,x,y,z;};
    float intersect(glm::vec3 ro, glm::vec3 rd, float r, float x, float y, float z);
    glm::vec3 reflection(glm::vec3 p, glm::vec3 n, glm::vec3 rd, Sphere s1, Sphere s2, int count);
    glm::vec3 shadow(glm::vec3 ro, glm::vec3 n, glm::vec3 rd, glm::vec3 diffuse, glm::vec3 p, glm::vec3 lightPosition);
    float attenuation(float li, float d);






};

#endif // RAYSCENE_H
