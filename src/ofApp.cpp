#include "ofApp.h"

const float SPAWN_GAP = 5;
const float EDGE_BUFFER = 0.1;
const int MAX_SPLASHES = 30;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    _lastQuadrant = 5;

    SpawnSplash();
    _nextSpawn = SPAWN_GAP;
}

//--------------------------------------------------------------
void ofApp::update(){
    _nextSpawn -= ofGetLastFrameTime();
    if (_nextSpawn <= 0 && _splashes.size() < MAX_SPLASHES) {
        SpawnSplash();
        _nextSpawn = SPAWN_GAP;
    }

    for (int i = _splashes.size() - 1; i >= 0; i--) {
        _splashes[i].Update();
        if (_splashes[i].completed()) {
            _splashes.erase(_splashes.begin() + i);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (auto splash : _splashes) {
        splash.Draw();
    }
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

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // auto splash = Splash(ofVec2f(x, y));
    // _splashes.push_back(splash);
    // auto clickPoint = ofPoint(x, y);
    // std::cout << clickPoint << endl;
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

void ofApp::SpawnSplash() {
    int quadrant = ofRandom(1, 4);
    if (quadrant > _lastQuadrant) {
        quadrant++;
    }

    float minWidth, maxWidth, minHeight, maxHeight;
    if (quadrant % 2 == 0) {
        minWidth = ofGetWidth() * EDGE_BUFFER;
        maxWidth = ofGetWidth() * 0.5f;
    }
    else {
        minWidth = ofGetWidth() * 0.5f;
        maxWidth = ofGetWidth() * (1 - EDGE_BUFFER);
    }

    if ((quadrant - 1) % 2 == 0) {
        minHeight = ofGetHeight() * EDGE_BUFFER;
        maxHeight = ofGetHeight() * 0.5f;
    }
    else {
        minHeight = ofGetHeight() * 0.5f;
        maxHeight = ofGetHeight() * (1 - EDGE_BUFFER);
    }

    _lastQuadrant = quadrant;

    float x = ofRandom(minWidth, maxWidth);
    float y = ofRandom(minHeight, maxHeight);
    auto splash = Splash(ofVec2f(x, y));
    _splashes.push_back(splash);
}