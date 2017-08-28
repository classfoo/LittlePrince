#ifndef __Asteroid__CFPlanetItem__
#define __Asteroid__CFPlanetItem__

#include <iostream>
#include "cocos2d.h"
#include "CFPlanet.h"
#include "CFNpc.h"
#include "CFUtil.h"
#include "CFCloud.h"
#include <stddef.h>
using namespace cocos2d;

class CFPlanetItem:public CFGLNpc{
private:
    int index;
    const char* product;
    const char* name;
    CCSize size;
    void generateCloud();
    void showWords();
    void endShowWords();
public:
    CFPlanetItem(void);
    virtual ~CFPlanetItem(void);
    static CFPlanetItem* create(int index, const char* name, const char* night, float initHeight, float initRot, float initSpeed, float z, const char* product, CFGameContext* context);
    virtual bool init();
    virtual void update(float dt);
    virtual void onCircle(int circle);
    virtual void onConflict(b2Contact* contact,CFNode* other);
    virtual void onEndConflict(b2Contact* contact,CFNode* other);
    virtual b2Body* getBody();
    virtual CCSize getContentSize();
};

#endif

