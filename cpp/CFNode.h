#ifndef __Asteroid__CFNode__
#define __Asteroid__CFNode__

#include "cocos2d.h"
#ifdef __OBJC__
#include "Box2D.h"
#else
#include "Box2D/Box2D.h"
#endif
#include "CFNodeInfoBoard.h"
#include <stddef.h>
using namespace cocos2d;

#define TYPE_PLANET  10
#define TYPE_PLANETITEM  1
#define TYPE_HERO 2
#define TYPE_ENEMY 3
#define TYPE_PET 4
#define TYPE_CLOUD 5
#define TYPE_GIFT 6

class CFNode:public CCNode{
protected:
    int type;//节点类型，例如hero，enemy，gift等等
    float speed;
    float height;
    float rot;
    CFNodeInfoBoard* infoboard;
   
public:
    CFNode(void);
    virtual ~CFNode(void);
    int getType();
    //游戏对象基本物理属性
    virtual float getHeight();
    virtual void setHeight(float height);
    virtual float getLineSpeed();
    virtual void setLineSpeed(float speed);
    virtual float getRot();
    virtual void setRot(float rot);
    
    //NPC剧情触发对话显示方法
    virtual bool isShowingInfo();
    virtual void showInfo(const char* info, const char* font, float size, const ccColor3B color, float width,float posy, CCObject* obj, SEL_CallFunc callback);
    
    //NPC碰撞触发事件监听处理
    virtual void onConflict(b2Contact* contact,CFNode* other);
    virtual void onEndConflict(b2Contact* contact,CFNode* other);
    virtual CCSize getContentSize();
};
#endif
