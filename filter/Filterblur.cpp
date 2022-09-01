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

    strokes(canvas);


}

void FilterBlur::strokes(Canvas2D *canvas) {

    std::cout <<"strokes!";

    RGBA* data = canvas->data();

    RGBA* result = new RGBA[canvas->width() * canvas->height()];

    for (int r = 0; r < canvas->height(); r+=1) {
        for (int c = 0; c < canvas->width(); c+=2) {

            int strokeRand = std::rand()%6 + 4;
            int radiusRand = std::rand()%5 + 3;
            int thetaRand = std::rand()%6;



            //length of stroke in [4,10]
            for(int i=1; i<strokeRand; i++){
                //brush radius in [1,3]
                for(int j=0; j<radiusRand; j++){

                    int thisX = c + j + randXStroke(thetaRand, i);
                    int thisY = r + randYStroke(thetaRand, i);

                if(thisX>0 && thisX <canvas->width() && thisY>0 && thisY<canvas ->height()){

                    result[thisX + thisY*canvas ->width()] = data[c + r*canvas ->width()];
                }

            }
            }

        }
        }

    for (int r = 0; r < canvas ->height(); r++) {
        for (int c = 0; c < canvas ->width(); c++) {
            if(result[c + r*canvas ->width()].r == 0 &&
                    result[c + r*canvas ->width()].g == 0 &&
                    result[c + r*canvas ->width()].b == 0){
                continue;
            }

            data[c + r*canvas ->width()] = result[c + r*canvas ->width()];

        }
        }

    delete [] result;

    canvas -> update();


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


            result[c + r*canvas ->width()] = RGBA(finalR, finalG, finalB, 255);



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

float FilterBlur::randXStroke (int thetaRand, int i){
    //45 , -45 degree
    if(thetaRand == 0 || thetaRand == 1 || thetaRand == 4){
        return i ;
    }

    //26.5  ,  -26.5 degree
    if(thetaRand == 2 || thetaRand == 3){
        return 2*i ;
    }

    if(thetaRand == 5){
        return -i ;
    }

}

float FilterBlur::randYStroke (int thetaRand, int i){
    if(thetaRand == 2 || thetaRand == 3){
        return -i ;
    }

    if(thetaRand == 0 || thetaRand == 5  || thetaRand == 4){
        return 0;
    }

    if(thetaRand == 1 ){
        return i ;
    }


}





