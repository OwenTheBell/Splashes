#ifndef _SPLASH
#define _SPLASH

#include "ofMain.h"
#include "oPolygon.h"

class Splash {
    public:
        ofVec2f position;

        bool completed();

        Splash(ofVec2f position);

        void Update();
        void Draw();


    private:
        vector<oPolygon> _ripples;
        float _splashGap;
        float _seed;

        int _activeRipples;
};

#endif 