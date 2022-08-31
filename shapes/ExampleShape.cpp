#include "ExampleShape.h"
#include "glm.hpp"
#include <iostream>


ExampleShape::ExampleShape()
{
}

ExampleShape::ExampleShape(int param1, int param2) :
    m_param1(param1),
    m_param2(param2)
{
    /**
     * We build in vertex data for a cube, in this case they are handwritten.
     * You'll want to expand upon or refactor this code heavily to take advantage
     * of polymorphism, vector math/glm library, and utilize good software design
     *
     */

    /*
     *         -0.5f,-0.5f,-0.5f, \
        -1.f, 0.f, 0.f, \
        -0.5f,-0.5f, 0.5f,\
        -1.f, 0.f, 0.f, \
        -0.5f, 0.5f, 0.5f, \
        -1.f, 0.f, 0.f, \
        */
    m_vertexData = CUBE_DATA_POSITIONS;
  /*  glm::vec3 p1(-1.f, 0.f, 0.f);
    glm::vec3 p2(-1.f, 0.f, 0.f);
    glm::vec3 p3(-1.f, 0.f, 0.f);

    glm::vec3 norm(0,0,0);
    norm += glm::normalize(glm::cross(p1 - p2, p3 - p2));
    norm = glm::normalize(norm);
    std::cout << norm.x <<std::endl;
    std::cout << norm.y <<std::endl;
    std::cout << norm.z <<std::endl;
*/


    /**
     * Initialize the OpenGLShapeProperties so that the shape is ready to be drawn.
     * Note that this does not actually draw the shape, that happens in ShapesScene.cpp
     */
    initializeOpenGLShapeProperties();
}

ExampleShape::~ExampleShape()
{
}
