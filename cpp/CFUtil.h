#ifndef __Asteroid__CFUtil__
#define __Asteroid__CFUtil__

#include <iostream>

#ifdef __OBJC__
#include "Box2D.h"
#else
#include "Box2D/Box2D.h"
#endif
#include "cocos2d.h"
#include "GB2ShapeCache.h"
#include "CFNode.h"
#include "CFNumberScroll.h"
#include "CFGameContext.h"

#define PTM_RATIO 32

using namespace cocos2d;

class CFUtil{
public:
    static b2Body* createBody(const char* shape, CFNode* node, b2World* world);
    static void updateBody(b2Body* body, CCNode* node, CFGameContext* context);
};

#endif
