
#include "Filter.h"

class FilterBlur : public Filter {
public:
    FilterBlur();
    virtual ~FilterBlur() override;
    virtual void apply(Canvas2D *canvas, float param1, float param2) override;

    void Convolve2D(Canvas2D *canvas, std::vector< int > conv);




};

