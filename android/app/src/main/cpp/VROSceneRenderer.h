//
//  VROSceneRenderer.h
//  ViroRenderer
//
//  Created by Raj Advani on 1/5/17.
//  Copyright © 2017 Viro Media. All rights reserved.
//

#ifndef ANDROID_VROSCENERENDERER_H
#define ANDROID_VROSCENERENDERER_H

#include <memory>
#include "VROEye.h"
#include "VROTimingFunction.h"
#include "VRORenderer.h"
#include "VRORenderDelegate.h"
#include "VRODriverOpenGLAndroid.h"

class VROSceneController;

class VROSceneRenderer {

public:

    VROSceneRenderer() :
        _frame(0) {
        _renderer = std::make_shared<VRORenderer>();
    }
    virtual ~VROSceneRenderer() {}

    /*
     GL initialization invoked from rendering thread.
     */
    virtual void initGL() = 0;

    /*
     Main render loop.
     */
    virtual void onDrawFrame() = 0;

    /*
     Event on trigger.
     */
    virtual void onTriggerEvent() = 0;

    /*
     Pause head tracking.
     */
    virtual void onPause() = 0;

    /*
     Resume head tracking, refreshing viewer parameters if necessary.
     */
    virtual void onResume() = 0;

    /*
     Set the render delegate, which responds to renderer initialization and
     receives per-frame callbacks.
     */
    void setRenderDelegate(std::shared_ptr<VRORenderDelegate> delegate) {
        _renderer->setDelegate(delegate);
    }

    /*
     Set the active scene controller, which dictates what scene is rendered.
     */
    void setSceneController(std::shared_ptr<VROSceneController> sceneController) {
        _renderer->setSceneController(sceneController, *_driver.get());
    }
    void setSceneController(std::shared_ptr<VROSceneController> sceneController, bool animated) {
        _renderer->setSceneController(sceneController, animated, *_driver.get());
    }
    void setSceneController(std::shared_ptr<VROSceneController> sceneController, float seconds,
                            VROTimingFunctionType timingFunction) {
        _renderer->setSceneController(sceneController, seconds, timingFunction, *_driver.get());
    }

    std::shared_ptr<VRORenderer> getRenderer() {
        return _renderer;
    }
    std::shared_ptr<VRODriver> getDriver() {
        return _driver;
    }
    std::shared_ptr<VROFrameSynchronizer> getFrameSynchronizer() {
        return _renderer->getFrameSynchronizer();
    }

protected:

    int _frame;
    std::shared_ptr<VRORenderer> _renderer;
    std::shared_ptr<VRODriverOpenGLAndroid> _driver;

};

#endif //ANDROID_VROSCENERENDERER_H