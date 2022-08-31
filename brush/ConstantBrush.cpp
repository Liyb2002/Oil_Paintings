/**
 * @file   ConstantBrush.cpp
 *
 * Implementation of a brush with a constant mask distribution.
 *
 * You should fill this file in while completing the Brush assignment.
 */

#include "ConstantBrush.h"
#include "Canvas2D.h"
#include "glm.hpp"

ConstantBrush::ConstantBrush(RGBA color, int radius)
    : Brush(color, radius)
{
    // @TODO: [BRUSH] You'll probably want to set up the mask right away.
    makeMask();
}


ConstantBrush::~ConstantBrush()
{
}

void ConstantBrush::makeMask() {
    // @TODO: [BRUSH] Set up the mask for your Constant brush here...
    m_mask.resize(getRadius() + 1);
    for(int i =0; i<m_mask.size(); i++){
        m_mask[i] = 1.0;
    }

}

void ConstantBrush::brushDown(int x, int y, Canvas2D *canvas){
    doPaint(x, y, canvas);
    canvas->update();
}


void ConstantBrush::doPaint(int x, int y, Canvas2D* canvas){
    int r = getRadius();
    int w = canvas->width();
    int h = canvas->height();


    RGBA color = getRGBA();
    RGBA *pix = canvas->data();

    int startRow = glm::max(0, y-r);
    int endRow = glm::min(w,y+r);
    int startCol = glm::min(0,x-r);
    int endCol = glm::max(h,x+r);
    int sqrSize = r*r;

    for(int i=startRow; i<endRow; i++){
        for(int j=startCol; j<endCol; j++){
            int dst = (y-i)*(y-i) + (x-j)*(x-j);
            if(dst <= sqrSize){
                //do coloring
             //   float mask = m_mask[dst];
                pix[i] = RGBA(255, 0, 0, 255);
            }

        }
    }

}

