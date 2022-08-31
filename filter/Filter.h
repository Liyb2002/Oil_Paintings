#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include "RGBA.h"
#include "Canvas2D.h"



#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define PI 3.1415926f

class Canvas2D;


class Filter {
public:

    Filter();
    virtual ~Filter();
    virtual void apply(Canvas2D* canvas, float param1, float param2) = 0;


};

#endif // FILTER_H
