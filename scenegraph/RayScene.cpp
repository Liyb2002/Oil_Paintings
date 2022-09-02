#include "RayScene.h"
#include "Settings.h"
#include "CS123SceneData.h"
#include "Canvas2D.h"



#include <iostream>

//Question:
//1.How to read Scene data? (MainWindow::renderImage() read fail)
//4.How to know how many objects are in the scene?

RayScene::RayScene(Scene &scene) :
    Scene(scene)
{
    // TODO [INTERSECT]
    // Remember that any pointers or OpenGL objects (e.g. texture IDs) will
    // be deleted when the old scene is deleted (assuming you are managing
    // all your memory properly to prevent memory leaks).  As a result, you
    // may need to re-allocate some things here.

    global = { 1, 1, 1, 1};



}





void RayScene::render(Canvas2D* canvas, CS123SceneCameraData *camera) {

}

RayScene::~RayScene()
{
}

