
#include "Filter.h"

class FilterEdge : public Filter {
public:
    FilterEdge();
    virtual ~FilterEdge() override;
    virtual void apply(Canvas2D *canvas, float param1, float param2) override;
    void toGrayScale(Canvas2D *canvas);
    void Convolve2D(Canvas2D *canvas);



};


