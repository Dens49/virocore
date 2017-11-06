/*
 * Copyright (c) 2017-present, ViroMedia, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the  LICENSE file in the
 * root directory of this source tree. An additional grant  of patent rights can be found in
 * the PATENTS file in the same directory.
 */
package com.viro.renderer.jni;

import java.util.HashMap;
import java.util.Map;

/**
 * ARAnchor represents real-world objects whose position and orientation can be tracked. ARAnchors
 * are automatically created by Viro when planes are detected. A corresponding {@link ARNode} is
 * created and added to the {@link Scene} for each detected anchor.
 */
public class ARAnchor {

    /**
     * Specifies the type of ARAnchor.
     */
    public enum Type {
        /**
         * Default type for an {@link ARAnchor}, representing a point and orientation.
         */
        ANCHOR("anchor"),

        /**
         * Plane type for an {@link ARAnchor}, representing a detected horizontal surface.
         */
        PLANE("plane");

        private String mStringValue;
        private Type(String value) {
            this.mStringValue = value;
        }
        /**
         * @hide
         */
        public String getStringValue() {
            return mStringValue;
        }

        private static Map<String, Type> map = new HashMap<String, Type>();
        static {
            for (Type value : Type.values()) {
                map.put(value.getStringValue().toLowerCase(), value);
            }
        }
        /**
         * @hide
         */
        public static Type valueFromString(String str) {
            return map.get(str.toLowerCase());
        }
    };

    // All ARAnchors have these props
    private String mAnchorId;
    private Type mType;
    private Vector mPosition; // world transform of the anchor
    private Vector mRotation; // in degrees TODO convert to radians
    private Vector mScale;

    /**
     * Invoked from JNI
     * @hide
     */
    ARAnchor(String anchorId, String type, float[] position, float[] rotation, float[] scale) {
        mAnchorId = anchorId;
        mType = Type.valueFromString(type);
        mPosition = new Vector(position);
        mRotation = new Vector(rotation);
        mScale = new Vector(scale);
    }

    @Override
    protected void finalize() throws Throwable {
        try {
            dispose();
        } finally {
            super.finalize();
        }
    }

    /**
     * Release native resources associated with this ARAnchor.
     */
    public void dispose() {

    }

    /**
     * Get a unique String ID for this anchor.
     *
     * @return Unique ID for the anchor.
     */
    public String getAnchorId() {
        return mAnchorId;
    }

    public Type getType() {
        return mType;
    }

    public Vector getPosition() {
        return mPosition;
    }

    public Vector getRotation() {
        return mRotation;
    }

    public Vector getScale() {
        return mScale;
    }

}
