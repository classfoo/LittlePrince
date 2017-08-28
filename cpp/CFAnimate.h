#ifndef __Asteroid__CFAnimate__
#define __Asteroid__CFAnimate__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class CFAnimate:public CCNode{
private:
    const char* frame0;
    const char* frame1;
    const char* frame2;
    float delay;
public:
    CFAnimate(void);
    virtual ~CFAnimate(void);
    static CFAnimate* create(const char* frame0, const char* frame1, const char* frame2, float delay);
    virtual bool init();
};

#endif
