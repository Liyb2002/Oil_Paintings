
#include "Filter.h"

class FilterScale : public Filter {
public:
    FilterScale();
    virtual ~FilterScale() override;
    virtual void apply(Canvas2D *canvas, float scaleX, float scaleY) override;

    void doXRange(Canvas2D *canvas, float scaleX);
    void doYRange(Canvas2D *canvas, float scaleY);





};

