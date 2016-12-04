#include "ofApp.h"

//set constant values
#define NUM_CIRCLES 256
#define MAX_JUMP 50
#define MIN_JUMP -50
#define MAX_CIRCLE_RADIUS 100
#define MIN_CIRCLE_RADIUS 1
#define FRAME_RPS 60
#define BANDS_TO_GET 128

//circle coords
int myCircleX;
int myCircleY;
int myCircleR;

//circle RGB colors
int myColorR;
int myColorG;
int myColorB;

//set grow boolean
bool grow;

//height and width of screen
int screenHeight;
int screenWidth;

//array of circles
float circleX[NUM_CIRCLES];
float circleY[NUM_CIRCLES];
float circleRad[NUM_CIRCLES];


//--------------------------------------------------------------
void ofApp::setup(){
    
    //set framerate
    ofSetFrameRate(FRAME_RPS);
    
    // load in sounds:
    beat.load("01 - The Legend Of Zelda (Original Mix).mp3");
    
    // the fft needs to be smoothed out, so we create an array of floats
    // for that purpose:
    fftSmoothed = new float[8192];
    for (int i = 0; i < 8192; i++){
        fftSmoothed[i] = 0;
    }
    
    myCircleX = ofGetWindowWidth()/2;
    myCircleY = ofGetWindowHeight()/2;
    myCircleR = 150;
    
    myColorB = ofRandom(100, 200);
    myColorG = ofRandom(100, 200);
    myColorR = ofRandom(100, 200);


    //play song
    beat.play();
    
}


//--------------------------------------------------------------
void ofApp::update(){
    
    //set background color
    ofBackground(0,0,0);
    
    // update the sound playing system:
    ofSoundUpdate();
    
    // (5) grab the fft, and put in into a "smoothed" array,
    //		by taking maximums, as peaks and then smoothing downward
    float * val = ofSoundGetSpectrum(BANDS_TO_GET);		// request 128 values for fft
    for (int i = 0;i < BANDS_TO_GET; i++){
        
        // let the smoothed calue sink to zero:
        fftSmoothed[i] *= 0.96f;
        
        // take the max, either the smoothed or the incoming:
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];

    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //cam.begin();
    
    ofEnableAlphaBlending();
    ofDisableAlphaBlending();
    
    // draw the fft resutls:
    //ofSetColor(255,255,255,255);
    
    //float width = (float)(5*128) / BANDS_TO_GET;
    
    for (int i = 0;i < BANDS_TO_GET; i++){
        // (we use negative height here, because we want to flip them
        // because the top corner is 0,0)
        //ofDrawRectangle(50,50,200,200);
        
        //draw rectangles
        ofDrawRectangle(i*getRectWidth(),ofGetWindowHeight(),getRectWidth(),-(fftSmoothed[i]*200));
        ofDrawRectangle(ofGetWindowWidth()-(i*getRectWidth()),0,getRectWidth(),(fftSmoothed[i]*200));
    
        //draw circles
        ofSetColor(getRandomRGB(fftSmoothed[i]),getRandomRGB(fftSmoothed[i]),getRandomRGB(fftSmoothed[i]));
        ofDrawCircle(myCircleX, myCircleY, (fftSmoothed[i] * 75));
 
        ofSetColor(getRandomRGB(fftSmoothed[i]),getRandomRGB(fftSmoothed[i]),getRandomRGB(fftSmoothed[i]));
        ofDrawCircle(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), (fftSmoothed[i] * 25));
        

    }

}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

//--------------------------------------------------------------
int ofApp::getRandomRGB(float f){

    int rgb = f*50+ofRandom(MIN_JUMP,MAX_JUMP);
    
    if(rgb>255){
        rgb=255;
    }
    else if(rgb<0){
        rgb=0;
    }
    
    return rgb;
}

//--------------------------------------------------------------
int ofApp::getRectWidth(){
    
    int width = ofGetWindowWidth()/BANDS_TO_GET;
    
    return width;
}

