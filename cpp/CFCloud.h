#ifndef __Asteroid__CFCloud__
#define __Asteroid__CFCloud__

#include "cocos2d.h"
#include "CFPlanet.h"
#include "CFNpc.h"
#include "CFPet.h"
#include "CFEnemy.h"
#include "GB2ShapeCache.h"
#include "CFUtil.h"
#include <stddef.h>
using namespace cocos2d;
class CFCloud:public CFNpc{
private:
    const char* name;
    bool destroy;
    CCSprite* sprite;
    CCArmature* armature;
    virtual void generatePet();
    virtual void dropEnemy();
public:
    CFCloud(void);
    virtual ~CFCloud(void);
    static CFCloud* create(const char* filename, float initHeight, float initRot, float initSpeed, CFGameContext* context);
    virtual bool init();
    virtual void update(float dt);
    virtual void onCircle(int circle);
    virtual void onConflict(b2Contact* contact,CFNode* other);
    virtual void onEndConflict(b2Contact* contact,CFNode* other);
    virtual b2Body* getBody();
    virtual CCSize getContentSize();
};

#endif
