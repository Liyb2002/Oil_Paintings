#include "FilterEdge.h"
#include <iostream>
#include "glm.hpp"


FilterEdge ::FilterEdge(){
}

FilterEdge::~FilterEdge()
{
}

void FilterEdge::apply(Canvas2D *canvas, float param1, float param2) {
    //Step1 to graysacle
      toGrayScale(canvas);
      Convolve2D(canvas);

}


void FilterEdge::toGrayScale(Canvas2D *canvas) {
    std::cout <<"toGrayScale!";
    int width = canvas->width();

        RGBA* current_pixel = nullptr;

        /* Initialize the first pixel of the first row */
        RGBA* current_row = canvas->data();

        RGBA* data = canvas->data();
        size_t currentIndex = 0;

        for (int r = 0; r < canvas->height(); r++) {
            current_pixel = current_row;
            currentIndex = r * width;

            for (int c = 0; c < canvas->width(); c++) {
                // TODO: Task 4
                const RGBA &pixel = data[currentIndex+c];
                int Li = 0.299*pixel.r + 0.587*pixel.g + 0.114*pixel.b;


                // TODO: Task 6
                data[currentIndex+c].r = Li;
                data[currentIndex+c].g = Li;
                data[currentIndex+c].b = Li;


                /* Advance to the next pixel */
                current_pixel++;
                currentIndex++;
            }
            current_row += width;
        }
        canvas->update();


}

void FilterEdge::Convolve2D(Canvas2D *canvas) {
    std::cout <<"Convolve!";

    RGBA* data = canvas->data();
    glm::mat3x3 Gx = {-1,0,1, -2,0,2, -1,0,1};
    glm::mat3x3 Gy = {-1,-2,-1, 0,0,0, 1,2,1};

    glm::mat3x3 conv = {0,1,0, 1,1,1, 0,1,0};

    // TODO: Task 9 Create buffer to store new image data
    RGBA* result = new RGBA[canvas->width() * canvas->height()];


    // TODO: Task 10 Obtain kernel dimension
    float dim = 3;



    for (int r = 0; r < canvas->height(); r++) {
        for (int c = 0; c < canvas->width(); c++) {


            // TODO: Task 11 Initialize color to accumulate convolution data
            float Gx_red_acc = 0;
            float Gx_green_acc = 0;
            float Gx_blue_acc = 0;
            float Gy_red_acc = 0;
            float Gy_green_acc = 0;
            float Gy_blue_acc = 0;


            // TODO: Task 12
            // Iterate over the kernel using the value from task 10
            // Obtain the value at current index of kernel
            // Find correct index in original image data
            // Accumulate the kernel applied to pixel value in color_acc
            for(int i=0; i<dim; i++){
                for(int j=0; j<dim; j++){

                    int thisX = c + i - dim/2;
                    int thisY = r + j - dim/2;
                    int Gx_thisVal = Gx[j][i];
                    int Gy_thisVal = Gy[j][i];


                    if(thisX>0 && thisX <canvas->width() && thisY>0 && thisY<canvas ->height()){
                        RGBA curVal = data[thisX + thisY* canvas -> width()];

                        Gx_red_acc += (float)curVal.r * (float)Gx_thisVal;
                        Gx_green_acc+=(float)curVal.g * (float)Gx_thisVal;
                        Gx_blue_acc+=(float)curVal.b * (float)Gx_thisVal;

                        Gy_red_acc += (float)curVal.r * (float)Gy_thisVal;
                        Gy_green_acc+=(float)curVal.g * (float)Gy_thisVal;
                        Gy_blue_acc+=(float)curVal.b * (float)Gy_thisVal;


                    }
                }

            }

            float g_red = glm::sqrt(glm::dot(Gx_red_acc,Gx_red_acc) + glm::dot(Gy_red_acc,Gy_red_acc));
            float g_green = glm::sqrt(glm::dot(Gx_green_acc,Gx_green_acc) + glm::dot(Gy_green_acc,Gy_green_acc));
            float g_blue = glm::sqrt(glm::dot(Gy_blue_acc,Gy_blue_acc) + glm::dot(Gy_blue_acc,Gy_blue_acc));

/*
            if(r > 100 && r<110){
            std::cout<< "red is" << (float)data[c + r*canvas ->width()].r << std::endl;
            std::cout<< "green is" << (float)data[c + canvas ->width()].g << std::endl;
            std::cout<< "blue is" << (float)data[c + canvas ->width()].b << std::endl;
            }*/


            result[c + r*canvas ->width()] = RGBA(g_red, g_green, g_blue, 0);



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




