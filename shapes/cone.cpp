#include "cone.h"
#include "glm.hpp"
#include <iostream>




cone::cone()
{
}

cone::cone(int param1, int param2) :
    m_param1(param1),
    m_param2(param2)
{

    if(param1 <= 2){
        std:: cout <<"param1 must be larger than 2" << std::endl;
        return;

    }
    float PI = 3.14159;
    float frac = 1.0/param1;
    glm::vec3 posTop = {0.f, 0.5f, 0.f};
    glm::vec3 posBot = {0.f, -0.5f, 0.f};
    glm::vec3 normBot = {0.f, -0.5f, 0.f};
/*

 //   glm::vec3 n3{0.f, 0.f, 0.5f};
    glm::vec3 p11{-0.3f, -0.5f, 0.4f};
    glm::vec3 p12{0.3f,-0.5f, 0.4f};

    //       make u = B - A
           glm ::vec3 u = p11 -p12;
    //       v = C - A
           glm ::vec3 v = p11 -posTop;
    //       The normal of the plane is n_j = u x v
           glm :: vec3 normal = glm::cross(u, v);


std:: cout << normal.x << " "<< normal.y << " "<< normal.z << std::endl;
           std ::vector <glm::vec3> thisTriangle;
            thisTriangle.push_back(normal);
            thisTriangle.push_back(posTop);
            thisTriangle.push_back(p11);
            thisTriangle.push_back(p12);

           addVec(thisTriangle);


           glm::vec3 p21{0.3f,-0.5f, 0.4f};
           glm::vec3 p22{0.4f,-0.5f, 0.3f};
           glm :: vec3 normal2 = glm::cross(p21-p22, p21-posTop);
           std ::vector <glm::vec3> thisTriangle2;
            thisTriangle2.push_back(normal);
            thisTriangle2.push_back(posTop);
            thisTriangle2.push_back(p21);
            thisTriangle2.push_back(p22);

           addVec(thisTriangle2);
*/

    std ::vector <glm::vec3> posBotVec;

    for(int i=0; i<param1; i++){

        float posX = glm::cos ( PI * frac * i *2) *0.5;
        float posZ = glm::sin ( PI * frac * i *2) *0.5;
   //     float posX = i*1./param1 + -0.5;

        posBotVec.push_back(glm::vec3{posX, -0.5f, posZ});

   //     std:: cout <<posX << " "<<posZ << std::endl;

    }

    for(int i =posBotVec.size()-1; i>0; i--){
        std ::vector <glm::vec3> thisTriangle;
        std ::vector <glm::vec3> thisBot;

        glm::vec3 pos1 = posBotVec[i];
        glm::vec3 pos2 = posBotVec[i-1];

 //       make u = B - A
        glm ::vec3 u = pos1 -pos2;
 //       v = C - A
        glm ::vec3 v = pos1 -posTop;
 //       The normal of the plane is n_j = u x v
        glm :: vec3 normal = glm::cross(u, v);
 //         std:: cout << normal.x << " "<< normal.y << " "<< normal.z << std::endl;

         thisTriangle.push_back(normal);
         thisTriangle.push_back(posTop);
         thisTriangle.push_back(pos1);
         thisTriangle.push_back(pos2);

         thisBot.push_back(normBot);
         thisBot.push_back(posBot);
         thisBot.push_back(pos1);
         thisBot.push_back(pos2);
         addVec(thisTriangle);
         addVec(thisBot);
    }

    initializeOpenGLShapeProperties();
}

void cone :: addVec(std::vector<glm::vec3>position){
    glm::vec3 normal = position[0];
    for(int i=1; i<position.size(); i++){
       glm::vec3 tmpt = position[i];
       for(int j=0; j<3; j++){
           m_vertexData.push_back(tmpt[j]);
       }
       for(int k=0; k<3; k++){
           m_vertexData.push_back(normal[k]);
       }

    }

}

cone::~cone()
{
}

