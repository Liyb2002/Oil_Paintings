#include "RayScene.h"
#include "Settings.h"
#include "CS123SceneData.h"
#include "Canvas2D.h"



#include <iostream>

//Question:
//1.How to read Scene data? (MainWindow::renderImage() read fail)
//4.How to know how many objects are in the scene?

RayScene::RayScene(Scene &scene) :
    Scene(scene)
{
    // TODO [INTERSECT]
    // Remember that any pointers or OpenGL objects (e.g. texture IDs) will
    // be deleted when the old scene is deleted (assuming you are managing
    // all your memory properly to prevent memory leaks).  As a result, you
    // may need to re-allocate some things here.

    global = { 1, 1, 1, 1};



}





void RayScene::render(Canvas2D* canvas, CS123SceneCameraData *camera) {
    CS123SceneLightData thisLight;
    glm::vec3 lightPosition = glm::vec3(thisLight.pos.x, thisLight.pos.y, thisLight.pos.z);
  //  std::cout << "thisLight x is" << thisLight.pos.x <<std::endl;


    // ray origin that represents camera position
    RGBA *pix = canvas->data();
    glm::vec3 ro = glm::vec3(0, 2, 3);

   int size = canvas->width() * canvas->height();

    for (int i = 0; i < size; i++) {
        float x = (i%canvas->width() - canvas->width()/2)/255.;
        float y = (canvas->height()/2 - i/canvas->width() )/255.;

        // ray direction
        glm::vec3 rd = glm::normalize(glm::vec3(x,y, -1));
        Sphere s1 = {1.f, -1.7, 0.f, -1.2f};
        Sphere s2 = {1.f, 0.5f, 0.5f, -2.f};


        float d1 = intersect(ro, rd, s1.r, s1.x, s1.y, s1.z);
         float d2 = intersect(ro, rd, s2.r, s2.x, s2.y, s2.z);
    //    float d3 = rayMarch(ro,rd);
        float d = glm::min(d1,d2);
    //    d = glm::min(d,d3);
 //       std :: cout << "d is " << d << std::endl;

        if(d < 100.0){
            glm::vec3 p = ro + rd * d;
            glm::vec3 normal = calcNormal(p);

            glm::vec3 lightDirection = glm::normalize(lightPosition - p);
            float li = 1.f;

       //     li = attenuation(li, d);


            // ambient
            float k_a = 0.2;
            glm::vec3 i_a = glm::vec3(0.3, 0.3, 0.9);
            glm::vec3 ambient = k_a * i_a;

            // diffuse
            float k_d = 0.9;
            float dotLN = glm::dot(lightDirection, normal);
            glm::vec3 i_d = glm::vec3(0.5,0.9,0.3);
            glm::vec3 diffuse = k_d * dotLN * i_d * 1.f;

            //Reflection

           glm::vec3 re = reflection(p,normal,rd,s1,s2,1) * glm::vec3(0.2);

           //Shadow
       //    diffuse = shadow(ro, normal, rd, diffuse, p, lightPosition);


          //  pix[i] = RGBA(0.5 * 255, 0.9 * 255, 0.3 * 255, 0);
         //   glm::vec3 col = glm::vec3(dif)* glm::vec3(0.5,0.9,0.3);
            glm:: vec3 col = ambient + diffuse + re;
            col = colorClean(col);
  //          std :: cout << "color is " << col.x << col.y << col.z << std::endl;
            pix[i] = RGBA(col.x * 255, col.y * 255, col.z * 255, 0);

        }

    }
    canvas->update();

}

glm::vec3 RayScene::calcNormal(glm::vec3 p) {
  float e = 0.005; // epsilon
  float r = 1.; // radius of sphere
  return glm::normalize(glm::vec3(
    sdSphere(glm::vec3(p.x + e, p.y, p.z), r) - sdSphere(glm::vec3(p.x - e, p.y, p.z), r),
    sdSphere(glm::vec3(p.x, p.y + e, p.z), r) - sdSphere(glm::vec3(p.x, p.y - e, p.z), r),
    sdSphere(glm::vec3(p.x, p.y, p.z  + e), r) - sdSphere(glm::vec3(p.x, p.y, p.z - e), r)
  ));
}


bool RayScene::sdfCircle(int x, int y) {

  int d = x * x  + y * y;

  if(d > 1000){
      return false;
  }

  return true;
}

float RayScene::rayMarch(glm::vec3 ro, glm::vec3 rd) {
  float depth = 0.0;

  for (int i = 0; i < 255; i++) {
    glm::vec3 p = ro + depth * rd;
    float d = sdFloor(p);
    depth += d;
    if (d < 0.001 || depth > 100.) break;
  }

  return depth;
}

float RayScene:: sdSphere(glm::vec3 p, float r )
{
//  glm::vec3 offset = glm::vec3(0, 0, -2);
  return glm::sqrt(p.x*p.x + p.y*p.y + (p.z+2)*(p.z+2)) - r;
}

float RayScene:: sdFloor(glm::vec3 p) {
  return p.y + .5;
}

float RayScene::intersect(glm::vec3 ro, glm::vec3 rd, float r, float x, float y, float z) {
    float a = glm::dot(rd, rd);
    glm::vec3 s0_r0 = glm::vec3(ro.x - x, ro.y - y, ro.z - z);
    float b = 2.0 * glm::dot(rd, s0_r0);
    float c = glm::dot(s0_r0, s0_r0) - (r * r);
    if (b*b - 4.0*a*c < 0.0) {
        return 101.0;
    }
    return (-b - sqrt((b*b) - 4.0*a*c))/(2.0*a);
}

glm::vec3 RayScene ::reflection(glm::vec3 ro, glm::vec3 n, glm::vec3 rd, Sphere s1, Sphere s2, int count){

    if(!settings.useReflection || count == 6){
        return glm::vec3(0,0,0);
    }


    glm::vec3 r = rd - 2*glm::dot(rd,n)*n;

    float d1 = intersect(r, rd, s1.r, s1.x, s1.y, s1.z);
    float d2 = rayMarch(r,rd);
    float d = glm::min(d1,d2);

    glm::vec3 col;

    for(int i=0; i<6; i++){

    }

    if(d < 100.0){
        glm::vec3 p = ro + rd * d;
        glm::vec3 normal = calcNormal(p);
        glm::vec3 lightPosition = glm::vec3(3, 2, 4);
        glm::vec3 lightDirection = glm::normalize(lightPosition - p);



        // Calculate diffuse reflection by taking the dot product of
        // the normal and the light direction.
        float dif = glm::dot(normal, lightDirection);
        col += glm::vec3(dif) * glm::vec3(0.5,0.9,0.3) * glm::vec3(1.f/count,1.f/count, 1.f/count);
        col += reflection(p, normal, rd,  s1,  s2,  count+1);
}else{
        return glm::vec3(0,0,0);
    }

    return col;


}

glm::vec3 RayScene::shadow(glm::vec3 ro, glm::vec3 n, glm::vec3 rd, glm::vec3 diffuse, glm::vec3 p, glm::vec3 lightPosition){
    if(!settings.useShadows){
        return diffuse;
    }

    glm::vec3 newRayOrigin = p + n * glm::vec3(0.01);
    float shadowRayLength = rayMarch(ro,rd);
    float lightToP = glm::sqrt(lightPosition.x*lightPosition.x* - p.x*p.x+
                               lightPosition.y*lightPosition.y* - p.y*p.y+
                               lightPosition.z*lightPosition.z* - p.z*p.z);
    if(shadowRayLength < lightToP){
       return glm::vec3(0,0,0);
    }

    return diffuse;

}

float RayScene::attenuation(float li, float d){
    float divisor = 0.2 + d*0.3 + d*d*0.3;
    float att = 1.f / divisor;
    return glm::min(att, 1.f);

}

glm::vec3 RayScene::colorClean(glm::vec3 col){
    if(col.x < 0.){
        col.x = 0.f;
    }
    if(col.y < 0.){
        col.y = 0.f;
    }
    if(col.z < 0.){
        col.z = 0.f;
    }

    if(col.x > 1.){
        col.x = 1.f;
    }
    if(col.y > 1.){
        col.y = 1.f;
    }
    if(col.z > 1.){
        col.z = 1.f;
    }

    return glm::vec3(col.x,col.y,col.z);

}

RayScene::~RayScene()
{
}

