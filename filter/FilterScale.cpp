#include "FilterScale.h"
#include <iostream>
#include "glm.hpp"


FilterScale ::FilterScale(){
}

FilterScale::~FilterScale()
{
}




void FilterScale::apply(Canvas2D *canvas, float scaleX, float scaleY) {



    doXRange(canvas, scaleX);
    doYRange(canvas, scaleY);



}

void FilterScale::doXRange(Canvas2D *canvas, float scaleX){

    RGBA *data = canvas->data();
    RGBA* result = new RGBA[canvas->width() * canvas->height()];

    for (int r = 0; r < canvas->height(); r++) {
            for (int c = 0; c < canvas->width(); c++) {
                if((int)(c/scaleX) > canvas ->width()){
                    result[c + r*canvas ->width()] = RGBA(0,0,0,0);
                }else{
                    result[c + r*canvas ->width()] = data[(int)(c/scaleX) + r*canvas ->width()];
                }
            }
            }


    for (int r = 0; r < canvas ->height(); r++) {
            for (int c = 0; c < canvas ->width(); c++) {

                data[c + r*canvas ->width()] = result[c + r*canvas ->width()];

            }
            }
    delete [] result;
   canvas->update();
}



void FilterScale::doYRange(Canvas2D *canvas, float scaleY){

    RGBA *data = canvas->data();
    RGBA* result = new RGBA[canvas->width() * canvas->height()];

    for (int r = 0; r < canvas->height(); r++) {
            for (int c = 0; c < canvas->width(); c++) {
                int row = (int)r/ scaleY;

                if(row > canvas ->height()){
                    result[c + r*canvas ->width()] = RGBA(0,0,0,0);
                }else{
                    result[c + r*canvas ->width()] = data[c+ row*canvas ->width()];
                }

            }
            }


    for (int r = 0; r < canvas ->height(); r++) {
            for (int c = 0; c < canvas ->width(); c++) {

                data[c + r*canvas ->width()] = result[c + r*canvas ->width()];

            }
            }
    delete [] result;
   canvas->update();
}


