#include "ofApp.h"
#include <stdio.h>
#define STRINGIFY(A) #A

//--------------------------------------------------------------
void ofApp::setup(){
    
     //ofSetFullscreen(1);
    ofImage ofiTmpImage;
    radius_pen = 5 ;
    // ofiTmpImage.load("/Users/takahashitakeshishi/Pictures/DepthImageSample.png");
    ofiTmpImage.load("/Users/takahashitakeshishi/Pictures/DepthImageSample.png");
    
    //ofiTmpImage.load("/Users/takahashitakeshishi/Pictures/sintyoku.jpg");
    oftfFont.load("Arial.ttf",12);
    iIsDrag = 0;
    fWidth = ofGetWidth();
    fHeight = ofGetHeight();
    threshold_edge = 5;
    threshold_depth = 100;
    
    ofiBaseImage =  makeBaseImage(ofiTmpImage);
    ofiCover.load("sintyoku.jpg");//to allocate, source have no meaning
    ofiCover.resize(fWidth, fHeight);
    ofSetVerticalSync(false);
    for(int i = 0 ; i < RANDOMTEX_NUM ; i ++){
        ofPixels tmp;
        tmp.allocate(fWidth, fHeight, OF_IMAGE_COLOR_ALPHA);
        for(int x = 0 ; x < fWidth ; x++ ){
            for(int y  = 0 ; y < fHeight ; y++ ){
                ofColor c = ofColor(ofRandom(2,10),255,255,255);
                tmp.setColor(x, y, c);
                
            }
            
        }
        randomTexture[i].setFromPixels(tmp);
        
    }
    topLayer.allocate(fWidth, fHeight);
    transparentShader = setTransparentProcess();
    PMouse = ofVec2f(ofGetMouseX(),ofGetMouseX());
    ofiCover = resetCover(ofiCover);
    ofSoundStreamSetup(2, 0, this, 44100, 1024, 4);
    soundFreq = 100;
    phase = 0;
    bIsEdged = 0;
    bIsDragged = 0;
    mouseVel = 0 ;
}
//--------------------------------------------------------------
void ofApp::update(){
    ofPixels tmp;
    topLayer.readToPixels(tmp);//cause to slow
    ofiCover.setFromPixels(tmp);//cause to slow
    topLayer.begin();
    transparentShader.begin();
    transparentShader.setUniform1f("fMouseX", ofGetMouseX());
    transparentShader.setUniform1f("fMouseY", ofGetMouseY());
    transparentShader.setUniform1f("radius_pen", radius_pen);
    transparentShader.setUniform1f("fPMouseX", PMouse.x);
    transparentShader.setUniform1f("fPMouseY", PMouse.y);
    transparentShader.setUniform1i("iIsDrag", ofGetMousePressed());
    transparentShader.setUniformTexture("randomTexture",randomTexture[int(ofRandom(RANDOMTEX_NUM))], 1);
    ofiCover.draw(ofPoint(0,0), topLayer.getWidth(),topLayer.getHeight() );
    transparentShader.end();
    topLayer.end();
    PMouse = ofVec2f(ofGetMouseX(),ofGetMouseY());
    bIsEdged = getOverEdge(mouseX, mouseY);
}
//--------------------------------------------------------------
void ofApp::draw(){
    ofiBaseImage.draw(ofPoint(0,0), fWidth, fHeight);
    topLayer.draw(ofPoint(0,0), fWidth, fHeight);
    // randomTexture[1].draw(0,0);
    //ofiCover.draw(0,0);
    ofSetColor(0, 255, 0);
    ofColor tmpColor= ofiBaseImage.getColor(ofiBaseImage.getWidth()*(float(mouseX)/ofGetWidth()), ofiBaseImage.getHeight()*(float(mouseY)/ofGetHeight()));
    cout<<ofiBaseImage.getWidth()*float(mouseX)/ofGetWidth()<<endl;
//    cout<<mouseX<<endl;
 //   oftfFont.drawString(ofToString(ofGetFrameRate())+"color="+ofToString(tmpColor), fWidth-300, 15);
  //  layers[ofGetWidth()][ofGetHeight()];
    ofSetColor(255, 255, 255,255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    bIsDragged = 1;
    //cout<<button<<endl;
   mouseVel = sqrt((PMouse.x-mouseX)*(PMouse.x-mouseX)+(PMouse.y-mouseY)*(PMouse.y-mouseY));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    bIsDragged = 0;
    mouseVel = 0;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    fWidth = w;
    fHeight = h;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
bool ofApp::getOverEdge(float _x,float _y){
    bool bOverEdge = false;
    
    if(!bIsEdged){
    ofColor tmpThresh = ofColor(90,90,90);//high place color
        ofColor tmpBaseImageColor = ofiBaseImage.getColor(ofiBaseImage.getWidth()*(float(_x)/ofGetWidth()), ofiBaseImage.getHeight()*(float(_y)/ofGetHeight()));
    if((pColor == tmpThresh&&tmpBaseImageColor!=tmpThresh)||(pColor != tmpThresh&&tmpBaseImageColor==tmpThresh)){
        bOverEdge = true;
    }
    pColor = tmpBaseImageColor;
        return bOverEdge;
    
    }else{
        bOverEdge = true;
        return bOverEdge;
    }
    
}

ofImage ofApp::makeBaseImage(ofImage image){
    /*
     ofImage tmp;
     tmp = image;
     tmp.setImageType(OF_IMAGE_GRAYSCALE);
     //  unsigned char ucTmpPixels[int(tmp.getWidth()*tmp.getHeight()*4)];
     ofPixels tmpPixels;
     //    cout<<OF_IMAGE_COLOR_ALPHA<<endl;
     tmpPixels = tmp.getPixels();
     
     for(int x = 0 ; x < tmp.getWidth() ; x ++){
     for(int y = 0 ; y < tmp.getHeight() ; y ++){
     for(int i = 0 ; i < NUM_THRESH-1 ; i ++){
     //                if(tmpPixels.getColor(x, y).getBrightness()>(255/NUM_THRESH)*i){
     if(tmpPixels.getColor(x, y).getBrightness()<(255/NUM_THRESH)*(i+1)){
     
     tmpPixels.setColor(x, y, ofColor((255/NUM_THRESH)*(i)));
     }
     }
     }
     }
     
     tmp.setFromPixels(tmpPixels);
     return tmp;
     */
    ofPixels  p;
    ofFbo base,second;
    ofxCvGrayscaleImage wblurImage,bblurImage;
    wblurImage.allocate(int(image.getWidth()), int(image.getHeight()));
    bblurImage.allocate(int(image.getWidth()), int(image.getHeight()));
    glLineWidth(0.0f);
    base.allocate(image.getWidth(),image.getHeight(),GL_RGBA);
    second.allocate(image.getWidth(),image.getHeight(),GL_RGBA);
    base.begin();
    ofBackground(100, 100, 100);
    unsigned char tmp[int(image.getWidth()*image.getHeight())];
    unsigned char *pixels = image.getPixels();
    ofSetColor(255, 255, 255);
    for(int y = 0 ; y < image.getHeight()-1 ; y ++){
        for(int x = 0 ; x < image.getWidth()-1; x ++){
            int position = (image.getWidth()*y+x);
            if(abs(pixels[int(image.getWidth()*y+x)]-pixels[int(image.getWidth()*y+(x+1))])>threshold_edge||abs(pixels[int(image.getWidth()*y+x)]-pixels[int(image.getWidth()*(y+1)+x)])>threshold_edge){
                tmp[position] = 255;
                ofSetColor(255,255, 255);
                ofCircle(x,y, RADIUS);
            }else {
                tmp[position] = 0;
            }
            //tmp[position] = pixels[position];
        }
    }
    base.end();
    base.readToPixels(p);
    for(int y = 0 ; y < image.getHeight(); y ++){
        for(int x = 0 ; x < image.getWidth(); x ++){
            int position = (image.getWidth()*y+x);
            tmp[position] = (p[position*4]+p[position*4+1]+p[position*4+2])/3;
        }
    }
    cout<< " pixel size "<<p.size()/4 << endl;
    cout<< " image  size"<< image.getWidth()*image.getHeight()<< endl;
    
    wblurImage.setFromPixels(tmp, image.getWidth(), image.getHeight());
    wblurImage.blur(20);
   
    base.begin();
    ofBackground(90, 90, 90);
    for(int y = 0 ; y < image.getHeight()-1 ; y ++){
        for(int x = 0 ; x < image.getWidth()-1; x ++){
            int position = (image.getWidth()*y+x);
            if(abs(pixels[int(image.getWidth()*y+x)]-pixels[int(image.getWidth()*y+(x+1))])>threshold_edge||abs(pixels[int(image.getWidth()*y+x)]-pixels[int(image.getWidth()*(y+1)+x)])>threshold_edge){
                tmp[position] = 255;
                ofSetColor(20,20, 20);
                ofCircle(x,y, RADIUS);
            }else {
                tmp[position] = 0;
            }
            //tmp[position] = pixels[position];
        }
    }
    base.end();
    base.readToPixels(p);
    for(int y = 0 ; y < image.getHeight(); y ++){
        for(int x = 0 ; x < image.getWidth(); x ++){
            int position = (image.getWidth()*y+x);
            tmp[position] = (p[position*4]+p[position*4+1]+p[position*4+2])/3;
        }
    }
    cout<< " pixel size "<<p.size()/4 << endl;
    cout<< " image  size"<< image.getWidth()*image.getHeight()<< endl;
    
    bblurImage.setFromPixels(tmp, image.getWidth(), image.getHeight());
    bblurImage.blur(20);
    
    
    
    base.begin();
    bblurImage.draw(0,0);
    base.end();
    ofPixels tmpPix = ofFbo2ofImage(base).getPixels();
    second.begin();
    wblurImage.draw(0, 0);
    for(int y = 0 ; y < image.getHeight(); y ++){
        for(int x = 0 ; x < image.getWidth(); x ++){
            int position = (image.getWidth()*y+x);
            if(pixels[position]>threshold_depth){
//                ofSetColor(90, 90, 90);
                ofColor c =tmpPix.getColor(x, y);
                ofSetColor(c);
                ofCircle(x, y, 1);
            }
        }
    }
    ofSetColor(255, 255, 255);
    second.end();
    
    ofFbo output;
    output.allocate(image.getWidth(),image.getHeight());
    output.begin();
    //  base.draw(0,0);
    second.draw(0,0);
    output.end();
    output.readToPixels(p);
//    return ofFbo2ofImage(output);
    return ofFbo2ofImage(output);
    
}

ofImage ofApp::resetCover(ofImage img){
    ofImage tmp;
    tmp = img;
    unsigned char tmpPixels[int(tmp.getWidth()*tmp.getHeight()*4)];
    
    for(int x = 0 ; x < tmp.getWidth(); x++){
        for(int y = 0 ; y < tmp.getHeight(); y++){
            tmpPixels[int(tmp.getWidth()*y+x)*4] = 255;
            tmpPixels[int(tmp.getWidth()*y+x)*4+1] = 255;
            tmpPixels[int(tmp.getWidth()*y+x)*4+2] = 255;
            tmpPixels[int(tmp.getWidth()*y+x)*4+3] = 255;
        }
    }
    tmp.setFromPixels(tmpPixels, tmp.getWidth(), tmp.getHeight(), OF_IMAGE_COLOR_ALPHA);
    return tmp;
}
///---------------shader------------------------------
ofShader ofApp::setTransparentProcess(){
    ofShader tmp;
    string shaderProgram = STRINGIFY(
                                     uniform sampler2DRect tex0;
                                     uniform sampler2DRect randomTexture;
                                     
                                     uniform float fMouseX;
                                     uniform float fMouseY;
                                     uniform float fPMouseX;
                                     uniform float fPMouseY;
                                     uniform float radius_pen;
                                     uniform int iIsDrawingRight;
                                     uniform float fRivalryRADIUS;
                                     uniform float fRivalryValue;
                                     uniform float fNumDivide;
                                     uniform int iIsDrag;
                                     vec3 rgb2hsv(vec3 c){
                                         
                                         vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
                                         vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
                                         vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));
                                         float d = q.x - min(q.w, q.y);
                                         float e = 1.0e-10;
                                         return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
                                     }
                                     vec3 hsv2rgb(vec3 c)
                                     {
                                         vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
                                         vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
                                         return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
                                     }
                                     float fDistPTP(vec2 p1, vec2 p2) {
                                         return pow( ( p2.x - p1.x ) * ( p2.x - p1.x ) + ( p2.y - p1.y ) * ( p2.y - p1.y ), 0.5 );
                                     }
                                     float fCrossVector(vec2 v1, vec2 v2){
                                         return v1.x * v2.y - v1.y * v2.x;
                                     }
                                     float fDistPTL(vec2 point, vec2 start, vec2 end){
                                         vec2 AB;
                                         vec2 AP;
                                         
                                         AB.x = end.x - start.x;
                                         AB.y = end.y - start.y;
                                         AP.x = point.x - start.x;
                                         AP.y = point.y - start.y;
                                         
                                         float D = abs( fCrossVector( AB, AP ) );
                                         
                                         float L = fDistPTP( start,end );	//AB間の距離
                                         
                                         float H = D/L;
                                         
                                         return H;
                                     }
                                     
                                     float fDistPTLS(vec2 start, vec2 end ,vec2 point){
                                         
                                         if ( dot(end-start, point-start) < 0.0 ) return fDistPTP(point,start);
                                         if ( dot(start-end, point-end) < 0.0 ) return fDistPTP(point,end);
                                         return abs(fCrossVector(end-start, point-start)) / fDistPTP(end,start);
                                     }
                                     void main(void){
                                         //float w = 2000.0;
                                         vec2 pos = gl_TexCoord[0].st;
                                         float r = texture2DRect(tex0,pos).r;
                                         float g = texture2DRect(tex0,pos).g;
                                         float b = texture2DRect(tex0,pos).b;
                                         float a = texture2DRect(tex0,pos).a;
                                         float rand = texture2DRect(randomTexture,pos).r;
                                         // vec4 color = vec4((r+R)/2.0,(g+G)/2.0,(b+B)/2.0,a);
                                         
                                         //                                         vec4 color = vec4(R/2.0+r/2.0,G/2.0+g/2.0,B/2.0+b/2.0,a);
                                         //                                             if(fDistPTP(pos,vec2(fMouseX,fMouseY))<10.0){
                                         //                                                 a = a/2.0;
                                         //                                             }
                                         if(fDistPTLS(vec2(fMouseX,fMouseY),vec2(fPMouseX,fPMouseY),pos)<radius_pen&&iIsDrag==1){
                                             a = a/(rand*255.0);
                                         }
                                         
                                         vec4 color = vec4(r,g,b,a);
                                         
                                         gl_FragColor = color;
                                     }
                                     );
    tmp.setupShaderFromSource(GL_FRAGMENT_SHADER,shaderProgram );
    tmp.linkProgram();
    return tmp;
}

ofImage ofApp::ofFbo2ofImage(ofFbo input){
    ofImage output;
    output.allocate(input.getWidth(), input.getHeight(), OF_IMAGE_COLOR);
    ofPixels tmp;
    input.readToPixels(tmp);
    output.setFromPixels(tmp);
    
    return output;
}

void ofApp::audioRequested (float *buf, int bufSize, int nChan) {
    //  float phasePerSample = TWO_PI * (soundFreq-ofRandom(100)+ofRandom(200)) / 44100;
    if(bIsDragged){
        float vals[bufSize];
        mouseVel = (int)mouseVel;
        if(bIsEdged){
            for(int i = 0 ; i < bufSize ; i++){
                vals[i] = 1;
            }
        }else{
            for(int i = 0 ; i < bufSize ; i++){
                vals[i] = ofRandom(0,(mouseVel+10));
                vals[i] = vals[i]/(ofGetWidth()/2);
                if(vals[i]>1){
                    vals[i] = 0;
                }
            }
            
        }
        for (int i = 0; i < bufSize; i++) {
            buf[i * nChan    ] = vals[i];
            buf[i * nChan + 1] = vals[i];
        }
    }
    bIsEdged = false;
    bIsDragged = false;
}
