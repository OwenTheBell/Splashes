#include "oPolygon.h"

oPolygon::oPolygon(int sides, float radius, ofVec2f position, float rotation) {
    this->radius = radius;
    this->position = position;
    this->rotation = rotation;
    this->scale = 1;

    float angle = 180 + rotation;
    for (auto i = 0; i < sides; i++) {
        auto point = ofVec2f(0, radius);
        point = point.getRotated(angle);
        point += position;
        angle += 360.0 / sides;
        _corners.push_back(point);
    }

    old_values.radius = radius;
    old_values.position = position;
    old_values.rotation = rotation;

    this->fill = false;
    this->lineColor = ofColor::white;
    this->fillColor = ofColor::black;
}

int oPolygon::sides() {
    return _corners.size();
}

vector<ofVec2f> oPolygon::corners(){
    if (!CompareToOldState() || _corners.size() == 0) {
        auto radius_diff = radius - old_values.radius;

        float angle = 180 + old_values.rotation;
        for (auto &corner : _corners) {
            auto point = corner - old_values.position;
            point = point.getRotated(-angle); 
            point.y += radius_diff;
            point = point.getRotated(angle + rotation);
            point += position;
            corner = point;
            angle += 360.0 / sides();
        }
        
        UpdateOldState();
    }
    return _corners;
}

void oPolygon::corners(vector<ofVec2f> &corners) {
    if (sides() != corners.size()) {
        return;
    }
    _corners = corners;
}

vector<ofVec2f> oPolygon::scaledCorners() {
    vector<ofVec2f> scaledCorners;

    float angle = 180 + rotation;
    for (auto corner : _corners) {
        auto point = corner - position;
        point = point.getRotated(-angle); 
        point.y *= scale;
        point = point.getRotated(angle + rotation);
        point += position;
        scaledCorners.push_back(point);
        angle += 360.0 / sides();
    }

    return scaledCorners;
}

void oPolygon::Update() {

}

void oPolygon::Draw() {
    ofSetColor(lineColor);
    for (int i = 0; i < scaledCorners().size(); i++) {
        int j = i + 1;
        if (j >= scaledCorners().size()) {
            j = 0;
        }
        ofDrawLine(scaledCorners()[i], scaledCorners()[j]);
    }
}

bool oPolygon::CompareToOldState() {
    if( old_values.radius != radius) {
        return false;
    }
    if (old_values.rotation != rotation) {
        return false;
    }
    if (old_values.position != position) {
        return false;
    }
    return true;
}

void oPolygon::UpdateOldState() {
    old_values.radius = radius;
    old_values.rotation = rotation;
    old_values.position = position;
}