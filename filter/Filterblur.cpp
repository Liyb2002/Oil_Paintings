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

    RGBA* edges = new RGBA[canvas->width() * canvas->height()];

 //   paintOil(canvas, conv);

 //   toGrayScale(canvas);
    Sobel(canvas, edges);

    strokes(canvas, edges);

    delete [] edges;


}

void FilterBlur::strokes(Canvas2D *canvas, RGBA* edges) {

    std::cout <<"strokes!";

    RGBA* data = canvas->data();

    RGBA* result = new RGBA[canvas->width() * canvas->height()];

    for (int r = 0; r < canvas->height(); r+=2) {
        for (int c = 0; c < canvas->width(); c+=2) {

            int strokeRand = std::rand()%6 + 2;
            int radiusRand = std::rand()%5 + 3;
            int thetaRand = std::rand()%6;

            if(c ==10){
                std::cout << strokeRand <<std::endl;
            }


            //brush radius in [1,3]
            for(int j=0; j<radiusRand; j++){
                if(edges[c + r*canvas ->width() +j].r > 0){
                 //   result[thisX + thisY*canvas ->width()] = RGBA (0,0,0,0);

                    break;
                }
                //length of stroke in [4,10]
                for(int i=1; i<strokeRand; i++){

                    int thisX = c + j + randXStroke(thetaRand, i);
                    int thisY = r + randYStroke(thetaRand, i);

                if(thisX>0 && thisX <canvas->width() && thisY>0 && thisY<canvas ->height()){

                    if(edges[thisX + thisY*canvas ->width() +j].r > 0){
                     //   result[thisX + thisY*canvas ->width()] = RGBA (0,0,0,0);

                        break;
                    }

                        result[thisX + thisY*canvas ->width()].r = data[c + r*canvas ->width()].r;
                        result[thisX + thisY*canvas ->width()].g = data[c + r*canvas ->width()].g;
                        result[thisX + thisY*canvas ->width()].b = data[c + r*canvas ->width()].b;
                        result[thisX + thisY*canvas ->width()].a = 255 * (1 - (i+j)/(radiusRand+strokeRand));

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
           //     data[c + r*canvas ->width()] = RGBA(255,0,0,0);
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



void FilterBlur::toGrayScale(Canvas2D *canvas) {
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

void FilterBlur::Sobel(Canvas2D *canvas, RGBA* edges) {
    std::cout <<"Sobel!";

    RGBA* data = canvas->data();
    glm::mat3x3 Gx = {-1,0,1, -2,0,2, -1,0,1};
    glm::mat3x3 Gy = {-1,-2,-1, 0,0,0, 1,2,1};

    glm::mat3x3 conv = {0,1,0, 1,1,1, 0,1,0};

    RGBA* result = new RGBA[canvas->width() * canvas->height()];

    float dim = 3;



    for (int r = 0; r < canvas->height(); r++) {
        for (int c = 0; c < canvas->width(); c++) {


            float Gx_red_acc = 0;
            float Gx_green_acc = 0;
            float Gx_blue_acc = 0;
            float Gy_red_acc = 0;
            float Gy_green_acc = 0;
            float Gy_blue_acc = 0;

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

            result[c + r*canvas ->width()] = RGBA(g_red, g_green, g_blue, 255);

        }
    }

    for (int r = 0; r < canvas ->height(); r++) {
        for (int c = 0; c < canvas ->width(); c++) {

            float temptIntensity = (30.*(float)result[c + r*canvas ->width()].r +
                                    59.*(float)result[c + r*canvas ->width()].g +
                                     11.*(float)result[c + r*canvas ->width()].b)/100.;

            if(temptIntensity > 180){
                edges[c + r*canvas ->width()] = RGBA(255,255,255,255);
          //     data[c + r*canvas ->width()] = RGBA(255,255,255,255);
            }else{
                 edges[c + r*canvas ->width()] = RGBA(0,0,0,255);
           //      data[c + r*canvas ->width()] = RGBA(0,0,0,255);
            }

        }
        }

    delete [] result;

  // canvas->update();

}

float FilterBlur::randXStroke (int thetaRand, int i){
    //45 , -45 degree
    if(thetaRand == 0 || thetaRand == 4){
        return i ;
    }

    if(thetaRand == 1){
        return 0;
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





