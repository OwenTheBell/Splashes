#include "Splash.h"

const int MAX_RIPPLES = 6;
const int MIN_SIDES = 5;
const int MAX_SIDES = 10;
const float START_RADIUS = 20;

const float GAP_BETWEEN_SPLASHES = 0.15;
const float GROWTH = 1.5;
const float DISTORTION = 2;

Splash::Splash(ofVec2f position) {
    this->position = position;
    _seed = position.x * position.y;

    _activeRipples = 1;
    _splashGap = GAP_BETWEEN_SPLASHES;

    for (int i = 0; i < MAX_RIPPLES; i++) {
        ofSeedRandom(_seed);        
        int sides = ofRandom(MIN_SIDES, MAX_SIDES + 1);
        float rotation = ofRandom(360);

        auto ripple = oPolygon(sides, START_RADIUS, position, rotation);
        ripple.scale = 0;
        _ripples.push_back(ripple);
    }
}

void Splash::Update() {
    if (_splashGap <= 0 && _activeRipples < MAX_RIPPLES) {
        _activeRipples++;
        _splashGap = GAP_BETWEEN_SPLASHES;
    }
    _splashGap -= ofGetLastFrameTime();

    for (int i = 0; i < _ripples.size(); i++) {
        int seed = _seed + _ripples[i].scale;
        ofSeedRandom(seed);
        auto &ripple = _ripples[i];
        if (i < _activeRipples) {
            ripple.scale += GROWTH * ofGetLastFrameTime();
        }

        auto corners = ripple.corners();
        float factor = DISTORTION * ofGetLastFrameTime();
        for (auto &corner : corners) {
            corner.x += ofRandom(-factor, factor);
            corner.y += ofRandom(-factor, factor);
        }
        ripple.corners(corners);
    }
}

void Splash::Draw() {
    for (auto ripple : _ripples) {
        ripple.Draw();
    }
}

bool Splash::completed() {
    ofVec2f screenCorners[] = {
        ofVec2f(0, 0),
        ofVec2f(ofGetWidth(), 0),
        ofVec2f(ofGetWidth(), ofGetHeight()),
        ofVec2f(0, ofGetHeight())
    };

    auto ripple = _ripples[_ripples.size() - 1];

    /// first check if any of the corners of the ripple are inside the screen
    for (int i = 0; i < ripple.sides(); i++) {
        auto corner = ripple.scaledCorners()[i];
        if (
                0 < corner.x && corner.x < ofGetWidth() &&
                0 < corner.y && corner.y < ofGetHeight()
            ) {
            return false;
        }
    }

    /// if no corners are inside, then check to make sure none of the edges
    /// intersect either
    for (int i = 0; i < ripple.sides(); i++) {
        int j = i + 1;
        if (j >= ripple.sides()) {
            j = 0;
        }
        for (int i2 = 0; i2 < 4; i2++) {
            int j2 = i2 + 1;
            if (j2 >= 4) {
                j2 = 0;
            }
            ofPoint point = ofPoint(0, 0);
            if (ofLineSegmentIntersection(
                                            ripple.scaledCorners()[i],
                                            ripple.scaledCorners()[j],
                                            screenCorners[i2],
                                            screenCorners[j2],
                                            point
                                        )) {
                return false;
            }
        }
    }
    return true;
}