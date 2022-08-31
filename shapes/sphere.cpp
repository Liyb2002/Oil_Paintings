#include "sphere.h"
#include "glm.hpp"
#include "glm/gtx/transform.hpp"
#include "shapeutil.h"
#include "ExampleShape.h"


Sphere::Sphere(int p1, int p2):
    OpenGLShape(){

    m_vertexData = CUBE_DATA_POSITIONS;
}

