#ifndef __Asteroid__CFTipsBoard__
#define __Asteroid__CFTipsBoard__

#include <stdio.h>
#include "cocos2d.h"
#include "CFCocosUtil.h"
#include "CFGameStoryBoard.h"

USING_NS_CC;

class CFGameTipsBoard:public CCNode{
private:
    CCSize size;
    CFGameStoryBoard* infoboard;
    CCSprite* background;
    CFGameContext* context;
    bool showing;
    int index;
    float getFitScale(CCSprite* sprite);
public:
    CFGameTipsBoard(void);
    virtual ~CFGameTipsBoard(void);
    static CFGameTipsBoard* create(CFGameContext* context, CFGameStoryBoard* infoboard);
    virtual bool init();
    virtual void update(float dt);
    void setTips(CCArray* tips);
    void setIsNotShowing();
    bool isShowing();
};

#endif
