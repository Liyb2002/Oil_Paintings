
#include "Filter.h"

class FilterBlur : public Filter {
public:
    FilterBlur();
    virtual ~FilterBlur() override;
    virtual void apply(Canvas2D *canvas, float param1, float param2) override;

    void paintOil(Canvas2D *canvas, std::vector< int > conv);
    void strokes(Canvas2D *canvas);

    float randXStroke (int thetaRand, int i);
    float randYStroke (int thetaRand, int i);

    void toGrayScale(Canvas2D *canvas);
    void Sobel(Canvas2D *canvas);





};

