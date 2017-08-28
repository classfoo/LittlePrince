#ifndef __Asteroid__CFGameStatus__
#define __Asteroid__CFGameStatus__

#include <iostream>

#include "cocos2d.h"
#include "CFConsts.h"
#include "CFGameContext.h"

class CFGameStatusListener{
public:
    virtual void onGameTaskAward(int gifttype, const char* awardname, int seconds);
};

class CFGameStatus:public CCNode{
private:
    int status;
    time_t starttime;
    int gifttype;
    int giftseconds;
    int giftawardcount;
    int giftcount;
    float giftscale;
    const char* giftname;
    const char* awardname;
    float awardscale;
    int awardseconds;
    CFGameContext* context;
    CFGameStatusListener* listener;
    CCLabelBMFont* label;
    CCNode* award;
    CCSprite* gift;
    void showAward();
    void hideAward();
    void runAwardAction();
    float getFitScale(CCSprite* sprite);
public:
    CFGameStatus(void);
    virtual ~CFGameStatus(void);
    static CFGameStatus* create(int gifttype, CFGameStatusListener* listener, CFGameContext* context);
    virtual bool init();
    void update(float dt);
    void showGift();
    void addGift();
    virtual CCSize getContentSize();
};

#endif
