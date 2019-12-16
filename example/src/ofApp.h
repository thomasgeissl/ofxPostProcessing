#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxPostProcessing.h"

class ofApp : public ofBaseApp
{
public:
    static const unsigned NUM_BOXES = 100;

    void setup();
    void update();
    void draw();

    void keyPressed(int key);

    // scene stuff
    ofxPostProcessing post;
    std::vector<RenderPass::Ptr> effects;
    ofEasyCam cam;
    ofLight light;

    // boxes
    vector<ofVec3f> posns;
    vector<ofColor> cols;
    ofVboMesh boxMesh;
    ofxPanel gui;
    bool drawGui;
};
