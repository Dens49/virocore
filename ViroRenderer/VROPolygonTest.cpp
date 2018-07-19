//
//  VROPolygonTest.cpp
//  ViroKit
//
//  Created by Raj Advani on 7/19/18.
//  Copyright © 2018 Viro Media. All rights reserved.
//

#include "VROPolygonTest.h"
#include "VROTestUtil.h"
#include "VROCompress.h"
#include "VROPolygon.h"
#include "VROToneMappingRenderPass.h"

VROPolygonTest::VROPolygonTest() :
VRORendererTest(VRORendererTestType::Polygon) {
    
}

VROPolygonTest::~VROPolygonTest() {
    
}

void VROPolygonTest::build(std::shared_ptr<VRORenderer> renderer,
                           std::shared_ptr<VROFrameSynchronizer> frameSynchronizer,
                           std::shared_ptr<VRODriver> driver) {
    _sceneController = std::make_shared<VROSceneController>();
    std::shared_ptr<VROScene> scene = _sceneController->getScene();
    std::shared_ptr<VROPortal> rootNode = scene->getRootNode();
    rootNode->setBackgroundCube({ 0.8, 0.8, 0.8, 1.0 });

    std::vector<VROVector3f> path;
    path.push_back({ -1,      -1, 0 });
    path.push_back({ -1,       1, 0 });
    path.push_back({  1,       1, 0 });
    path.push_back({  1,     0.5, 0 });
    path.push_back({  0.5,   0.5, 0 });
    path.push_back({  0.5,  0.25, 0 });
    path.push_back({  1,    0.25, 0 });
    path.push_back({  1,      -1, 0 });
    
    std::vector<VROVector3f> holeA;
    holeA.push_back({ -0.75, -0.75, 0 });
    holeA.push_back({ -0.75, -0.50, 0 });
    holeA.push_back({ -0.50, -0.50, 0 });
    holeA.push_back({ -0.50, -0.75, 0 });
    
    std::vector<VROVector3f> holeB;
    holeB.push_back({ 0.75, -0.75, 0 });
    holeB.push_back({ 0.75, -0.50, 0 });
    holeB.push_back({ 0.50, -0.50, 0 });
    holeB.push_back({ 0.50, -0.75, 0 });

    std::shared_ptr<VROPolygon> polygon = VROPolygon::createPolygon(path, { holeA, holeB }, 0.5, 0.5, 1.0, 1.0);
    polygon->setName("Polygon 1");
    
    std::shared_ptr<VROTexture> bobaTexture = VROTestUtil::loadDiffuseTexture("boba.png");
    bobaTexture->setWrapS(VROWrapMode::Repeat);
    bobaTexture->setWrapT(VROWrapMode::Repeat);
    bobaTexture->setMinificationFilter(VROFilterMode::Linear);
    bobaTexture->setMagnificationFilter(VROFilterMode::Linear);
    bobaTexture->setMipFilter(VROFilterMode::Linear);
    
    std::shared_ptr<VROMaterial> material = polygon->getMaterials()[0];
    material->setLightingModel(VROLightingModel::Constant);
    material->getDiffuse().setTexture(bobaTexture);
    
    std::shared_ptr<VRONode> polyNode = std::make_shared<VRONode>();
    polyNode->setGeometry(polygon);
    polyNode->setPosition({0, 0, -5});
    rootNode->addChildNode(polyNode);
}


