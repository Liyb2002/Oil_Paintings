#include "cube.h"
#include <iostream>
#include "glm.hpp"

cube::cube()
{
}

cube::cube(int param1, int param2) :
    m_param1(param1),
    m_param2(param2)
{

//    std::cout << param1<< std::endl;
float stepSize = 1./param1;

    //right face
     glm::vec3 n6{-1.f, 0.f, 0.f};
     std ::vector <glm::vec3> p6;
     p6.push_back(n6);



     for(int i=0; i<param1; i++){
         for(int j=0; j<param1; j++){
         float topLeftPosX6 = -0.5+i*stepSize;
         float topLeftPosY6 = -0.5+ j*stepSize;
         glm::vec3 p61{-0.5f,topLeftPosX6,topLeftPosY6};
         glm::vec3 p62{-0.5f,topLeftPosX6, topLeftPosY6+stepSize};
         glm::vec3 p63{-0.5f, topLeftPosX6+stepSize, topLeftPosY6+stepSize};
         glm::vec3 p64{-0.5f,topLeftPosX6,topLeftPosY6};
         glm::vec3 p65{-0.5f, topLeftPosX6+stepSize, topLeftPosY6+stepSize};
         glm::vec3 p66{-0.5f, topLeftPosX6+stepSize,topLeftPosY6};
         p6.push_back(p61);
         p6.push_back(p62);
         p6.push_back(p63);
         p6.push_back(p64);
         p6.push_back(p65);
         p6.push_back(p66);
     }
}
     addVec(p6);

     //bot face
      glm::vec3 n4{0.f, 0.f, -1.f};
      std ::vector <glm::vec3> p4;
      p4.push_back(n4);

      for(int i=0; i<param1; i++){
          for(int j=0; j<param1; j++){
          float topLeftPosX4 = 0.5-i*stepSize;
          float topLeftPosY4 = 0.5- j*stepSize;
      glm::vec3 p41{topLeftPosX4, topLeftPosY4,-0.5f};
      glm::vec3 p42{topLeftPosX4-stepSize,topLeftPosY4-stepSize,-0.5f};
      glm::vec3 p43{topLeftPosX4-stepSize, topLeftPosY4,-0.5f};
      glm::vec3 p44{topLeftPosX4, topLeftPosY4,-0.5f};
      glm::vec3 p45{topLeftPosX4-stepSize,topLeftPosY4-stepSize,-0.5f};
      glm::vec3 p46{topLeftPosX4-stepSize, topLeftPosY4,-0.5f};
      p4.push_back(p41);
      p4.push_back(p42);
      p4.push_back(p43);
      p4.push_back(p44);
      p4.push_back(p45);
      p4.push_back(p46);
}
      }
      addVec(p4);


      //Back face
      glm::vec3 n2{0.f, -1.f, 0.f};
      std ::vector <glm::vec3> p2;
      p2.push_back(n2);

      for(int i=0; i<param1; i++){
          for(int j=0; j<param1; j++){
          float topLeftPosX2 = 0.5-i*stepSize;
          float topLeftPosY2 = 0.5- j*stepSize;
       glm::vec3 p21{topLeftPosX2,-0.5, topLeftPosY2};
       glm::vec3 p22{topLeftPosX2-stepSize,-0.5f,topLeftPosY2-stepSize};
       glm::vec3 p23{topLeftPosX2,-0.5f,topLeftPosY2-stepSize};
       glm::vec3 p24{topLeftPosX2,-0.5f, topLeftPosY2};
       glm::vec3 p25{topLeftPosX2-stepSize,-0.5f, topLeftPosY2};
       glm::vec3 p26{topLeftPosX2-stepSize,-0.5f,topLeftPosY2-stepSize};
       p2.push_back(p21);
       p2.push_back(p22);
       p2.push_back(p23);
       p2.push_back(p24);
       p2.push_back(p25);
       p2.push_back(p26);
       }
      }
       addVec(p2);


       //top face: key!
        glm::vec3 n3{0.f, 0.f, 1.f};
        std ::vector <glm::vec3> p3;
        p3.push_back(n3);

        for(int i=0; i<param1; i++){
            for(int j=0; j<param1; j++){
            float topLeftPosX = -0.5+i*stepSize;
            float topLeftPosy = 0.5-j*stepSize;
        glm::vec3 p31{topLeftPosX, topLeftPosy, 0.5};
        glm::vec3 p32{topLeftPosX,topLeftPosy-stepSize, 0.5};
        glm::vec3 p33{topLeftPosX+stepSize,topLeftPosy-stepSize, 0.5};
        glm::vec3 p34{topLeftPosX+stepSize, topLeftPosy, 0.5};
        glm::vec3 p35{topLeftPosX, topLeftPosy, 0.5};
        glm::vec3 p36{topLeftPosX+stepSize,topLeftPosy-stepSize, 0.5};
   //     std::cout<<stepSize<<std::endl;

        p3.push_back(p31);
        p3.push_back(p32);
        p3.push_back(p33);
        p3.push_back(p34);
        p3.push_back(p35);
        p3.push_back(p36);
        }
        }
        addVec(p3);

        //left face
         glm::vec3 n5{1.f, 0.f, 0.f};
         std ::vector <glm::vec3> p5;
         p5.push_back(n5);


         for(int i=0; i<param1; i++){
             for(int j=0; j<param1; j++){
             float topLeftPosX5 = 0.5-i*stepSize;
             float topLeftPosY5 = 0.5-j*stepSize;
         glm::vec3 p51{0.5f, topLeftPosX5, topLeftPosY5};
         glm::vec3 p52{0.5f,topLeftPosX5-stepSize,topLeftPosY5-stepSize};
         glm::vec3 p53{0.5f, topLeftPosX5,topLeftPosY5-stepSize};
         glm::vec3 p54{0.5f,topLeftPosX5-stepSize,topLeftPosY5-stepSize};
         glm::vec3 p55{0.5f, topLeftPosX5, topLeftPosY5};
         glm::vec3 p56{0.5f,topLeftPosX5-stepSize, topLeftPosY5};
         p5.push_back(p51);
         p5.push_back(p52);
         p5.push_back(p53);
         p5.push_back(p54);
         p5.push_back(p55);
         p5.push_back(p56);
         }
         }
         addVec(p5);


   //Front face
         glm::vec3 n1{0.f, 1.f, 0.f};
         std ::vector <glm::vec3> p1;
         p1.push_back(n1);

         for(int i=0; i<param1; i++){
             for(int j=0; j<param1; j++){
             float topLeftPosX1 = 0.5-i*stepSize;
             float topLeftPosY1 = 0.5-j*stepSize;
    glm::vec3 p11{topLeftPosX1, 0.5f, topLeftPosY1};
    glm::vec3 p12{topLeftPosX1, 0.5f,topLeftPosY1-stepSize};
    glm::vec3 p13{topLeftPosX1-stepSize, 0.5f,topLeftPosY1-stepSize};
    glm::vec3 p14{topLeftPosX1, 0.5f, topLeftPosY1};
    glm::vec3 p15{topLeftPosX1-stepSize, 0.5f,topLeftPosY1-stepSize};
    glm::vec3 p16{topLeftPosX1-stepSize, 0.5f, topLeftPosY1};
    p3.push_back(p11);
    p3.push_back(p12);
    p3.push_back(p13);
    p3.push_back(p14);
    p3.push_back(p15);
    p3.push_back(p16);
    }
         }
    addVec(p1);


//   std::cout << m_vertexData.size()<< std::endl;
    initializeOpenGLShapeProperties();
}

void cube :: addVec(std::vector<glm::vec3>position){
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

cube::~cube()
{
}
