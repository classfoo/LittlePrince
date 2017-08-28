#ifndef __Asteroid__CFInfoBoard__
#define __Asteroid__CFInfoBoard__

#include "cocos2d.h"
#include "CFGameLevel.h"
#include "CFGameContext.h"
#include "CFLabel.h"

USING_NS_CC;

class CFGameStoryBoard:public CCNode{
private:
    CCSize size;
    CCMenuItemImage* background;
    CFLabel* label;
    CCLabelTTF* nextTip;
    CFGameContext* context;
    bool showing;
    void showNextTip();
    void hideInfo();
    void setIsNotShowing();
public:
    CFGameStoryBoard(void);
    virtual ~CFGameStoryBoard(void);
    static CFGameStoryBoard* create(CFGameContext* context);
    virtual bool init();
    virtual void update(float dt);
    void showStory();
    bool isShowing();
};

#endif
