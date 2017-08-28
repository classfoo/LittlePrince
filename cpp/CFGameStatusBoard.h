#ifndef __Asteroid__CFGameStatusBoard__
#define __Asteroid__CFGameStatusBoard__

#include <iostream>
#include <string>
#include "cocos2d.h"
#include "CFConsts.h"
#include "CFGameContext.h"
#include "CFGameStatus.h"

USING_NS_CC;

using namespace std;

class CFGameStatusBoard:public CCNode{
private:
    CCSize size;
    CFGameStatusListener* listener;
    CFGameContext* context;
    void reorderStatuses(int gifttype, float targetY);
public:
    CFGameStatusBoard(void);
    virtual ~CFGameStatusBoard(void);
    static CFGameStatusBoard* create(CFGameStatusListener* listener, CFGameContext* context);
    virtual bool init();
    void update(float dt);
    void addGift(int gifttype);
    void showGift(int gifttype);
    virtual CCSize getContentSize();
};

#endif
