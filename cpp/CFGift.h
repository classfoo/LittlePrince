#ifndef __Asteroid__CFGift__
#define __Asteroid__CFGift__


#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CFPlanet.h"
#include "CFNpc.h"
#include "CFUtil.h"
#include "CFParticle.h"
#include "CFPrince.h"
#include "CFAnimate.h"

#include "cocos-ext.h"
using namespace extension;

class CFGift:public CFNpc{
private:
    const char* name;
    CCNode* sprite;
    int type;
    int energy;
    int action;
    CCSize size;
    bool conflicted;
    float getTopHeight();
    float getBottomHeight();
public:
    CFGift(void);
    virtual ~CFGift(void);
    static CFGift* create(int type, int energy, int action, const char* name, float initHeight, float initRot, float initSpeed,CFGameContext* context);
    virtual bool init();
    virtual void onCircle(int circle);
    CCNode* initCommonSprite();
    CCNode* initBallonSprite(const char* ballon);
    CCNode* initAnimationSprite();
    virtual void update(float dt);
    void updateByAction0(float dt);
    void updateByAction1(float dt);
    void updateByAction2(float dt);
    void updateByAction3(float dt);
    void updateByAction4(float dt);
    void updateByAction5(float dt);

    virtual void onConflict(b2Contact* contact,CFNode* other);
    virtual void onEndConflict(b2Contact* contact,CFNode* other);
    virtual b2Body* getBody();
    virtual CCSize getContentSize();
};


#endif
