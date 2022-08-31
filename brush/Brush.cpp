/**
 * @file   Brush.cpp
 *
 * Implementation of common functionality of bitmap brushes.
 *
 * You should fill this file in while completing the Brush assignment.
 */

#include "Brush.h"
#include "Canvas2D.h"
#include "glm.hpp"
#include <iostream>


static unsigned char lerp(unsigned char a, unsigned char b, float percent) {
    float fa = static_cast<float>(a) / 255.0f;
    float fb = static_cast<float>(b) / 255.0f;
    return static_cast<unsigned char>((fa + (fb - fa) * percent) * 255.0f + 0.5f);
}



Brush::Brush(RGBA color, int radius) :
    // Pro-tip: Initialize all variables in the initialization list
    m_color(color),
    m_radius(radius)
{
//    std::cout<<"create brush";
    // Pro-tip: By the time you get to the constructor body, all of the
    // member variables have already been initialized.
}


Brush::~Brush()
{
    // Pro-tip: The destructor (here) is where you free all the resources
    // you allocated during the lifetime of the class
    // Pro-tip: If you use std::unique_ptr or std::vector, you probabably
    // won't need to put anything in here.
}

int Brush::getAlpha() const {
    return m_color.a;
}

RGBA Brush::getRGBA() const {
    return m_color;
}

int Brush::getBlue() const {
    return m_color.b;
}

int Brush::getGreen() const {
    return m_color.g;
}

int Brush::getRadius() const {
    return m_radius;
}

int Brush::getRed() const {
    return m_color.r;
}

void Brush::setAlpha(int alpha) {
    m_color.a = alpha;
}

void Brush::setRGBA(const RGBA &rgba) {
    m_color = rgba;
}

void Brush::setBlue(int blue) {
    m_color.b = blue;
}

void Brush::setGreen(int green) {
    m_color.g = green;
}

void Brush::setRed(int red) {
    m_color.r = red;
}

void Brush::setRadius(int radius) {
    m_radius = radius;
    makeMask();
}




void Brush::brushDragged(int mouseX, int mouseY, Canvas2D* canvas) {
    // @TODO: [BRUSH] You can do any painting on the canvas here. Or, you can
    //        override this method in a subclass and do the painting there.
    //
    // Example: You'll want to delete or comment out this code, which
    // sets all the pixels on the canvas to red.
    //

    RGBA *pix = canvas->data();
 /*  int size = canvas->width() * canvas->height();
      std::cout <<"brush dragging";

    for (int i = 0; i < size; i++) {
        pix[i] = RGBA(255, 0, 255, 0);
    }
    canvas->update();
*/
    int r = getRadius();
    int w = canvas->width();
    int h = canvas->height();

 std::cout <<"brush dragging";
    RGBA color = getRGBA();

    int startRow = glm::max(0, mouseY-r);
    int endRow = glm::min(w,mouseY+r);
    int startCol = glm::max(0,mouseX-r);
    int endCol = glm::min(h,mouseX+r);
    int sqrSize = r*r;



    for(int i=startRow; i<endRow; i++){
        for(int j=startCol; j<endCol; j++){

            int dst = (mouseY-i)*(mouseY-i) + (mouseX-j)*(mouseX-j);
            if(dst <= sqrSize){
                int maskPlace = glm::round(glm::sqrt(static_cast<float>(dst)));
                //do coloring
                float mask = m_mask[maskPlace];
             //   color.setAlpha(255 * 0.1);
                float srcA = color.a / 255.f;

                setAlpha(20);
                setBlue(240);
                setRed(50);
                setGreen(150);

               // pix[i*w+j] = pix[i*w+j] * (1.f - mask * srcA) + color * mask * srcA;
               pix[i*w+j] = color;
            }

        }
    }

    canvas->update();

}
