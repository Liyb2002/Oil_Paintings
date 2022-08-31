#ifndef CYLINDER_H
#define CYLINDER_H

#include "OpenGLShape.h"
#include "glm.hpp"

class cylinder : public OpenGLShape
{
public:
    cylinder();
    cylinder(int param1, int param2);
    ~cylinder();
  //  void pushVectors(glm::vec3 normal, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, glm::vec3 p5, glm::vec3 p6);
   void addVec(std::vector <glm::vec3>position);
private:
    int m_param1;
    int m_param2;
};

#endif // CYLINDER_H
