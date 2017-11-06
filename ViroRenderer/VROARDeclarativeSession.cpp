//
//  VROARDeclarativeSession.cpp
//  ViroKit
//
//  Created by Raj Advani on 11/3/17.
//  Copyright © 2017 Viro Media. All rights reserved.
//

#include "VROARDeclarativeSession.h"
#include "VROARDeclarativeNode.h"
#include "VROARScene.h"

VROARDeclarativeSession::VROARDeclarativeSession() {
    _constraintMatcher = std::make_shared<VROARConstraintMatcher>();
}

void VROARDeclarativeSession::init() {
    _constraintMatcher->setDelegate(shared_from_this());
}

VROARDeclarativeSession::~VROARDeclarativeSession() {
    
}

void VROARDeclarativeSession::setDelegate(std::shared_ptr<VROARDeclarativeSessionDelegate> delegate) {
    _delegate = delegate;
}

void VROARDeclarativeSession::addARNode(std::shared_ptr<VROARDeclarativeNode> node) {
    // TODO: figure out a way to make ARNode simply not be visible at start.
    // call this once, because when it planes are first added they should not be visible.
    node->setAttached(false);
    _nodes.push_back(node);
    if (_constraintMatcher) {
        _constraintMatcher->addARNode(node);
    }
}

void VROARDeclarativeSession::removeARNode(std::shared_ptr<VROARDeclarativeNode> node) {
    node->setAttached(false);
    if (_constraintMatcher) {
        _constraintMatcher->removeARNode(node);
    }
    _nodes.erase(
                 std::remove_if(_nodes.begin(), _nodes.end(),
                                [node](std::shared_ptr<VROARDeclarativeNode> candidate) {
                                    return candidate == node;
                                }), _nodes.end());
}

void VROARDeclarativeSession::updateARNode(std::shared_ptr<VROARDeclarativeNode> node) {
    if (_constraintMatcher) {
        _constraintMatcher->updateARNode(node);
    }
}

void VROARDeclarativeSession::sceneWillAppear() {
    for (auto it = _nodes.begin(); it < _nodes.end(); it++) {
        _constraintMatcher->addARNode(*it);
    }
}

void VROARDeclarativeSession::sceneWillDisappear() {
    _constraintMatcher->detachAllNodes(_nodes);
}

#pragma mark - VROARSessionDelegate Implementation

void VROARDeclarativeSession::anchorWasDetected(std::shared_ptr<VROARAnchor> anchor) {
    std::shared_ptr<VROARDeclarativeSessionDelegate> delegate = _delegate.lock();
    if (delegate) {
        delegate->anchorWasDetected(anchor);
    }
    _constraintMatcher->anchorWasDetected(anchor);
}

void VROARDeclarativeSession::anchorWillUpdate(std::shared_ptr<VROARAnchor> anchor) {
    std::shared_ptr<VROARDeclarativeSessionDelegate> delegate = _delegate.lock();
    if (delegate) {
        delegate->anchorWillUpdate(anchor);
    }
}

void VROARDeclarativeSession::anchorDidUpdate(std::shared_ptr<VROARAnchor> anchor) {
    std::shared_ptr<VROARDeclarativeSessionDelegate> delegate = _delegate.lock();
    if (delegate) {
        delegate->anchorDidUpdate(anchor);
    }
    _constraintMatcher->anchorDidUpdate(anchor);
}

void VROARDeclarativeSession::anchorWasRemoved(std::shared_ptr<VROARAnchor> anchor) {
    std::shared_ptr<VROARDeclarativeSessionDelegate> delegate = _delegate.lock();
    if (delegate) {
        delegate->anchorWasRemoved(anchor);
    }
    _constraintMatcher->anchorWasRemoved(anchor);
}

#pragma mark - VROARConstraintMatcherDelegate Implementation

void VROARDeclarativeSession::anchorWasAttached(std::shared_ptr<VROARAnchor> anchor) {
    std::shared_ptr<VROARDeclarativeSessionDelegate> delegate = _delegate.lock();
    if (delegate) {
        delegate->anchorDidUpdate(anchor);
    }
}

void VROARDeclarativeSession::anchorWasDetached(std::shared_ptr<VROARAnchor> anchor) {
    std::shared_ptr<VROARDeclarativeSessionDelegate> delegate = _delegate.lock();
    if (delegate) {
        delegate->anchorDidUpdate(anchor);
    }
}
