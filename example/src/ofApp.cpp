#include "ofApp.h"

void ofApp::setup()
{
    drawGui = true;
    ofBackground(0);
    ofSetFrameRate(60);

    // Setup post-processing chain
    post.init(ofGetWidth(), ofGetHeight());
    effects.push_back(post.createPass<ContrastPass>());
    effects.push_back(post.createPass<HsbShiftPass>());
    effects.push_back(post.createPass<RGBShiftPass>());
    effects.push_back(post.createPass<LimbDarkeningPass>());
    effects.push_back(post.createPass<FxaaPass>());
    effects.push_back(post.createPass<FakeSSSPass>());
    effects.push_back(post.createPass<BloomPass>());
    effects.push_back(post.createPass<DofPass>());
    effects.push_back(post.createPass<KaleidoscopePass>());
    effects.push_back(post.createPass<NoiseWarpPass>());
    effects.push_back(post.createPass<PixelatePass>());
    effects.push_back(post.createPass<EdgePass>());
    effects.push_back(post.createPass<HorizontalTiltShifPass>());
    effects.push_back(post.createPass<VerticalTiltShifPass>());
    effects.push_back(post.createPass<GodRaysPass>());
    effects.push_back(post.createPass<SSAOPass>());
    effects.push_back(post.createPass<ToonPass>());
    effects.push_back(post.createPass<ZoomBlurPass>());
    gui.setup("gui", "settings.xml", 20, 20);
    for (auto &effect : effects)
    {
        effect->setEnabled(false);
        gui.add(effect->parameters);
    }
    gui.minimizeAll();

    // Setup box positions
    for (unsigned i = 0; i < NUM_BOXES; ++i)
    {
        posns.push_back(ofVec3f(ofRandom(-300, 300), ofRandom(-300, 300), ofRandom(-300, 300)));
        cols.push_back(ofColor::fromHsb(255 * i / (float)NUM_BOXES, 255, 255, 255));
    }

    // Setup light
    light.setPosition(1000, 1000, 2000);

    // create our own box mesh as there is a bug with
    // normal scaling and ofDrawBox() at the moment
    boxMesh = ofMesh::box(20, 20, 20);
}

void ofApp::update()
{
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

void ofApp::draw()
{

    // setup gl state
    ofEnableDepthTest();
    light.enable();

    // begin scene to post process
    post.begin(cam);

    // draw boxes
    for (unsigned i = 0; i < posns.size(); ++i)
    {
        ofSetColor(cols[i]);
        ofPushMatrix();
        ofTranslate(posns[i]);
        boxMesh.draw();
        ofPopMatrix();
    }

    // ofDrawAxis(100);

    // end scene and draw
    post.end();

    if (drawGui)
    {
        ofDisableDepthTest();
        gui.draw();
    }
}

void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case 'g':
        drawGui = !drawGui;
        break;
    }
}