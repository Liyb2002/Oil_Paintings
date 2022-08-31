#include "FilterBlur.h"
#include <iostream>
#include "glm.hpp"


FilterBlur ::FilterBlur(){
}

FilterBlur::~FilterBlur()
{
}




void FilterBlur::apply(Canvas2D *canvas, float param1, float param2) {

    int realParam = (int)param1;
    std::vector< int > conv;

    for(int i=0; i<param1*param1; i++){
        conv.push_back(1);
    }


    Convolve2D(canvas, conv);


}



void FilterBlur::Convolve2D(Canvas2D *canvas, std::vector< int > conv) {
    std::cout <<"Convolve!";

    RGBA* data = canvas->data();

    // TODO: Task 9 Create buffer to store new image data
    RGBA* result = new RGBA[canvas->width() * canvas->height()];


    // TODO: Task 10 Obtain kernel dimension
    float dim = glm::sqrt((float)conv.size());



    for (int r = 0; r < canvas->height(); r++) {
        for (int c = 0; c < canvas->width(); c++) {


            // TODO: Task 11 Initialize color to accumulate convolution data
            float red_acc = 0;
            float green_acc = 0;
            float blue_acc = 0;
            int count = 0;


            // TODO: Task 12
            // Iterate over the kernel using the value from task 10
            // Obtain the value at current index of kernel
            // Find correct index in original image data
            // Accumulate the kernel applied to pixel value in color_acc
            for(int i=0; i<dim; i++){
                for(int j=0; j<dim; j++){

                    int thisX = c + i - dim/2;
                    int thisY = r + j - dim/2;
                    int thisVal = conv[j*dim + i];


                    if(thisX>0 && thisX <canvas->width() && thisY>0 && thisY<canvas ->height()){
                        RGBA curVal = data[thisX + thisY* canvas -> width()];
                        count += thisVal;

                        red_acc += (float)curVal.r * (float)thisVal;
                        green_acc+=(float)curVal.g * (float)thisVal;
                        blue_acc+=(float)curVal.b * (float)thisVal;

                    }
                }

            }

/*
            if(r == 1 && c==1){
            std::cout<< "red is" << (float)data[c + r*canvas ->width()].r << std::endl;
            std::cout<< "green is" << (float)data[c + canvas ->width()].g << std::endl;
            std::cout<< "blue is" << (float)data[c + canvas ->width()].b << std::endl;
            }*/

            red_acc = red_acc/ count;
            green_acc = green_acc/count;
            blue_acc = blue_acc/count;

            result[c + r*canvas ->width()] = RGBA(red_acc, green_acc, blue_acc, 0);



        }
    }

    for (int r = 0; r < canvas ->height(); r++) {
        for (int c = 0; c < canvas ->width(); c++) {

            data[c + r*canvas ->width()] = result[c + r*canvas ->width()];

        }
        }

    delete [] result;

    canvas -> update();

}




