#ifndef __Asteroid__CFPrince__
#define __Asteroid__CFPrince__

#include <iostream>

#include "cocos2d.h"
#ifdef __OBJC__
#include "Box2D.h"
#else
#include "Box2D/Box2D.h"
#endif

#ifdef __OBJC__
#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#endif

#include "CFNode.h"
#include "CFUtil.h"
#include "cocos-ext.h"
#include "GB2ShapeCache.h"
#include "CFGameContext.h"

using namespace extension;

class CFPrince: public CFNode,CFGameLevelListener{
private:
    CFGameContext* context;
    b2Body* body;
    b2Body* node;
    b2Vec2 lastpos;
    CCArmature* armature;
    CCParticleSystemQuad *highspeedParticle;
    CCNode* award;
    bool isready;
    float r;
    float maxrotspeed;
    float rotspeed;
    int animationIndex;
    float zoom;
    int status;
    long starttime;
    long awardseconds;
    float targetHeight;
    void updateSpeed();
    void updateNode();
    void updateBody();
    void updateArmature();
    void updateEnergy(int frame);
    void updateStatus();
    void updateTargetHeight();
    void resetAward();
    bool spadeVisible;
    bool swordVisible;
    void setSpadeVisible(bool visible);
    void setSwordVisible(bool visible);
public:
    CFPrince(void);
    virtual ~CFPrince(void);
    static CFPrince* create(CFGameContext* context);
    virtual bool init();
    void update(float dt);
    float getSpeed();
    void setSpeed(float speed);
    void speedLeft();
    void speedRight();
    void jump(float force);
    bool isFlying();
    bool isRunning();
    void playByIndex(int index);
    
    virtual bool isReady();
    virtual float getWeight();
    virtual float getHeight();
    virtual void setHeight(float height);
    virtual float getZoom();
    virtual float getTop();
    virtual void onBeganTouch(time_t beginTouchTime, CCPoint beginTouchLocation);
    virtual void onEndTouch(time_t beginTouchTime, CCPoint beginTouchLocation, time_t endTouchTime, CCPoint endTouchLocation);
    virtual void onConflict(b2Contact* contact,CFNode* other);
    virtual void onEndConflict(b2Contact* contact,CFNode* other);
    virtual void onGameTaskStory(CCDictionary* task, int taskindex);
    virtual void onGameTaskAward(int awardtype, const char* awardname, int seconds);
    virtual void onGameTaskStart(CCDictionary* task ,int taskindex);
    virtual void onGameTaskComplete(CCDictionary* task ,int taskindex);

    virtual int getStatus();
    virtual b2Body* getBody();
    virtual b2Body* getNode();
    virtual CCSize getContentSize();
};
#endif
