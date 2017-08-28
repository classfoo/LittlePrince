#ifndef __Asteroid__CFNumberScroll__
#define __Asteroid__CFNumberScroll__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class CFNumberScroll:public CCNode
{
private:
    //    可见的节点数字
    CCNode *visibleNode;
    int fontsize;
public:
    //    创建
    static CFNumberScroll* create(int fontsize);
    //    函数初始化
    virtual bool init();
    //    重载CCNode函数实现opengl遮罩
    virtual void visit();
    //    设置滚动到哪个数字
    void setNumber(int var);
};
#endif


