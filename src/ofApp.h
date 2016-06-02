#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofxUI.h"
#define NUM_THRESH 2 // set <2
#define RADIUS 5
#define RANDOMTEX_NUM 25
class ofApp : public ofBaseApp{
private:
    float soundFreq;
    float phase;
    bool bIsEdged;
    bool bIsDragged;
    float mouseVel;
    ofColor pColor;
public:
    
     ofImage randomTexture[RANDOMTEX_NUM];
   // layers baseImageLayers[NUM_THRESH];
    bool bIsNearWhite;
    float fThresholdLayer;
    float threshold_edge;
    float threshold_depth;
    float fNumLater;
    ofImage ofiBaseImage;
    float radius_pen;
    
    float fWidth;
    float fHeight;
    int iIsDrag;
    ofTrueTypeFont oftfFont;
    ofImage ofiCover;
    ofFbo topLayer;
    ofShader transparentShader;
    ofVec2f PMouse;
    void setup();
    void update();
    void draw();
    ofImage applySobelFilter(ofImage input);
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    ofImage makeBaseImage(ofImage image);
    ofImage resetCover(ofImage img);
    ofShader setTransparentProcess();
    ofImage ofFbo2ofImage(ofFbo input);
    void audioRequested(float *buf, int bufSize, int nChan);
    bool getOverEdge(float x, float y);
};
