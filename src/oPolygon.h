#ifndef _O_POLYGON
#define _O_POLYGON

#include "ofMain.h"

class oPolygon {
    public:
        ofVec2f position;
        float radius;
        float rotation;
        float scale;

        float lineWidth;
        ofColor lineColor;
        bool fill;
        ofColor fillColor;

        oPolygon(int sides, float radius, ofVec2f position, float rotation);

        int sides();
        vector<ofVec2f> corners();
        void corners(vector<ofVec2f> &corners);
        vector<ofVec2f> scaledCorners();

        void Update();
        void Draw();

    private:
        vector<ofVec2f> _corners;

        struct old_state {
            float radius;
            float rotation;
            ofVec2f position; 
        } old_values;

        bool CompareToOldState();
        void UpdateOldState();
};

#endif