/**
 * @file Canvas2D.cpp
 *
 * CS123 2-dimensional canvas. Contains support code necessary for Brush, Filter, Intersect, and
 * Ray.
 *
 * YOU WILL NEED TO FILL THIS IN!
 *
 */

// For your convenience, a few headers are included for you.
#include <assert.h>
#include <iostream>
#include <math.h>
#include <memory>
#include <unistd.h>
#include "Canvas2D.h"
#include "Settings.h"
#include "RayScene.h"

#include <QCoreApplication>
#include <QPainter>
#include "brush/Brush.h"
#include "brush/ConstantBrush.h"
#include "brush/LinearBrush.h"
#include "brush/QuadraticBrush.h"
#include "brush/SmudgeBrush.h"

#include "filter/Filter.h"
#include "filter/FilterEdge.h"
#include "filter/FilterBlur.h"
#include "filter/FilterScale.h"





Canvas2D::Canvas2D() :
    // @TODO: Initialize any pointers in this class here.
    m_rayScene(nullptr),
    m_brush(nullptr)
{
    set_brush();
}

Canvas2D::~Canvas2D()
{
}

// This is called when the canvas size is changed. You can change the canvas size by calling
// resize(...). You probably won't need to fill this in, but you can if you want to.
void Canvas2D::notifySizeChanged(int w, int h) {
}

void Canvas2D::paintEvent(QPaintEvent *e) {
    // You probably won't need to fill this in, but you can if you want to override any painting
    // events for the 2D canvas. For now, we simply call the superclass.
    SupportCanvas2D::paintEvent(e);

}

void Canvas2D::settingsChanged() {
    // TODO: Process changes to the application settings.
 //   Canvas2D::renderImage(CS123SceneCameraData *camera, int width, int height);
    std::cout << "Canvas2d::settingsChanged() called. Settings have changed" << std::endl;
}

// ********************************************************************************************
// ** BRUSH
// ********************************************************************************************


void Canvas2D::mouseDown(int x, int y) {
    // @TODO: [BRUSH] Mouse interaction for brush. You will probably want to create a separate
    //        class for each of your brushes. Remember that you can use the static Settings
    //        object to get the currently selected brush and its parameters.

    // You're going to need to leave the alpha value on the canvas itself at 255, but you will
    // need to use the actual alpha value to compute the new color of the pixel

    std::cout << "Canvas2d::mouseDown() called" << std::endl;
    m_brush ->brushDown(x, y, this);


//    bool fixAlphaBlending = settings.fixAlphaBlending; // for extra/half credit

}

void Canvas2D::mouseDragged(int x, int y) {
    // TODO: [BRUSH] Mouse interaction for Brush.
    std::cout << "Canvas2d::mouseDragged() called" << std::endl;
    if ((x < 0) || (y < 0)) return;

        m_brush->brushDragged(x, y, this);

}

void Canvas2D::mouseUp(int x, int y) {
    // TODO: [BRUSH] Mouse interaction for Brush.
    std::cout << "Canvas2d::mouseUp() called" << std::endl;
}



// ********************************************************************************************
// ** FILTER
// ********************************************************************************************

void Canvas2D::filterImage() {
    // TODO: [FILTER] Filter the image. Some example code to get the filter type is provided below.

    std::cout << "filter! with blurRadius:" << settings.blurRadius<< std::endl;

    // Leave this code here! This code ensures that the Canvas2D will be completely wiped before
    // drawing the new image.
    std::unique_ptr<Filter> m_filter;

    if(settings.filterType == FILTER_EDGE_DETECT){
         m_filter = std::make_unique<FilterEdge>();
         m_filter ->apply(this, settings.blurRadius, settings.blurRadius);
    }
    if(settings.filterType == FILTER_BLUR){
        m_filter = std::make_unique<FilterBlur>();
        m_filter ->apply(this, settings.blurRadius, settings.blurRadius);
    }
    if(settings.filterType == FILTER_SCALE){
        m_filter = std::make_unique<FilterScale>();
        m_filter ->apply(this, settings.scaleX, settings.scaleY);

    }



    repaint(rect());
    QCoreApplication::processEvents();
}

// ********************************************************************************************
// ** RAY
// ********************************************************************************************

void Canvas2D::setScene(RayScene *scene) {
    m_rayScene.reset(scene);
}

void Canvas2D::renderImage(CS123SceneCameraData *camera, int width, int height) {
    if (m_rayScene) {
        // @TODO: raytrace the scene based on settings
        //        YOU MUST FILL THIS IN FOR INTERSECT/RAY
 //       std::cout << "render called" << std::endl;

        m_rayScene->render(this, camera);
        if(settings.useShadows){
            std::cout << "using Shadow!" << std::endl;
        }
        update();
        // If you want the interface to stay responsive, make sure to call
        // QCoreApplication::processEvents() periodically during the rendering.

    }
}

void Canvas2D::cancelRender() {
    // TODO: cancel the raytracer (optional)
}


void Canvas2D::set_brush(){
    RGBA color = settings.brushColor;
    int  r  = settings.brushRadius;

    if(settings.brushType == BRUSH_CONSTANT){
        m_brush = std::make_unique<ConstantBrush>(color, r);
    }
    if(settings.brushType == BRUSH_LINEAR){
        m_brush = std::make_unique<LinearBrush>(color, r);
    }

}


