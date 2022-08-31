#include "FilterBlur.h"
#include <iostream>
#include "glm.hpp"


FilterBlur ::FilterBlur(){
}

FilterBlur::~FilterBlur()
{
}




void FilterBlur::apply(Canvas2D *canvas, float param1, float param2) {

    std::vector< int > conv;

    for(int i=0; i<param1*param1; i++){
        conv.push_back(1);
    }


    paintOil(canvas, conv);


}



void FilterBlur::paintOil(Canvas2D *canvas, std::vector< int > conv) {
    std::cout <<"paintOil!";

    RGBA* data = canvas->data();

    RGBA* result = new RGBA[canvas->width() * canvas->height()];


    float dim = glm::sqrt((float)conv.size());
    int intensityLvl = 20;


    for (int r = 0; r < canvas->height(); r++) {
        for (int c = 0; c < canvas->width(); c++) {
            std::vector<int> intensityCount(intensityLvl, 0);
            std::vector<int> averageR(intensityLvl, 0);
            std::vector<int> averageG(intensityLvl, 0);
            std::vector<int> averageB(intensityLvl, 0);



            for(int i=0; i<dim; i++){
                for(int j=0; j<dim; j++){

                    int thisX = c + i - dim/2;
                    int thisY = r + j - dim/2;
                    int thisVal = conv[j*dim + i];


                    if(thisX>0 && thisX <canvas->width() && thisY>0 && thisY<canvas ->height()){
                        RGBA curVal = data[thisX + thisY* canvas -> width()];

        int curIntensity =
                (int)((float)curVal.r+(float)curVal.g+(float)curVal.b) * intensityLvl/ (3*255.);
                intensityCount[curIntensity] +=1;
                averageR[curIntensity]+= curVal.r;
                averageG[curIntensity]+= curVal.g;
                averageB[curIntensity]+= curVal.b;
                    }
                }

            }

            int curMax = 0;
            int maxIndex = 0;
            for(int i=0; i<intensityLvl; i++){
                if (intensityCount[i] > curMax)
                    {
                        curMax = intensityCount[i];
                        maxIndex = i;
                    }

            }

            int finalR = averageR[maxIndex]/curMax;
            int finalG = averageG[maxIndex]/curMax;
            int finalB = averageB[maxIndex]/curMax;


            result[c + r*canvas ->width()] = RGBA(finalR, finalG, finalB, 0);



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




