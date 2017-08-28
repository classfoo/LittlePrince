#ifndef __Asteroid__CFNodeInfoBoard__
#define __Asteroid__CFNodeInfoBoard__

#include "cocos2d.h"
#include "CFLabel.h"
USING_NS_CC;

class CFNodeInfoBoard:public CCNode{
private:
    CCSize size;
    const char* font;
    float width;
    float fontsize;
    CFLabel* label;
    ccColor3B color;
    time_t start;
    CCObject* obj;
    SEL_CallFunc callback;
public:
    CFNodeInfoBoard(void);
    virtual ~CFNodeInfoBoard(void);
    static CFNodeInfoBoard* create(const char* font, float size, const ccColor3B color, float width, CCObject* obj, SEL_CallFunc callback);
    virtual bool init();
    virtual void update(float dt);
    void setInfo(const char* info);
    bool isShowing();
    virtual CCSize getContentSize();
};
#endif
