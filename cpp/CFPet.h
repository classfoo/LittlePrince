#ifndef __Asteroid__CFPet__
#define __Asteroid__CFPet__


#include <iostream>
#include "cocos2d.h"
#include "CFPlanet.h"
#include "CFNpc.h"
#include "CFUtil.h"
#include "CFPrince.h"

#include "cocos-ext.h"
using namespace extension;

class CFPet:public CFGLNpc, CFGameLevelListener{
private:
    const char* name;
    const char* product;
    CCArmature* armature;
    long lifeTime;
    CCSize size;
    CCSprite* tips;
    CCNode* icon;
    CCSprite* tipsboard;
    void initSprite(const char* name);
    void showWords();
    void endShowWords();
    void generateCloud();
public:
    CFPet(void);
    virtual ~CFPet(void);
    static CFPet* create(CFGameContext* context);
    virtual bool init();
    virtual void update(float dt);
    virtual void onCircle(int circle);
    virtual void onConflict(b2Contact* contact,CFNode* other);
    virtual void onEndConflict(b2Contact* contact,CFNode* other);
    virtual void onGameTaskStart(CCDictionary* task ,int taskindex);
    virtual void onGameTaskOngoing(CCDictionary* task ,int taskindex);
    virtual void onGameTaskComplete(CCDictionary* task ,int taskindex);

    void playAtIndex(int index);
    virtual b2Body* getBody();
    virtual CCSize getContentSize();
};

#endif
