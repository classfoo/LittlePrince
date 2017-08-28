#include "CFNumberScroll.h"

CFNumberScroll* CFNumberScroll::create(int fontsize){
    CFNumberScroll* scroll = new CFNumberScroll();
    scroll->fontsize = fontsize;
    scroll->init();
    scroll->autorelease();
    return scroll;
}

bool CFNumberScroll::init()
{
    if ( !CCNode::init() )
    {
        return false;
    }
    visibleNode=CCNode::create();
    //    创建0-9的数字
    for(int i=0;i<10;i++){
        char str[2];
        str[0] = '0' + i;
        str[1] = '\0';
        CCLabelTTF* single = CCLabelTTF::create(str, "", this->fontsize);
        single->setTag(i);
        single->setAnchorPoint(ccp(0, 0));
        single->setPosition(ccp(0, this->fontsize * i));
        //     将数字加入visibleNode节点中
        visibleNode->addChild(single);
    }
    this->addChild(visibleNode);
    return true;
}

void CFNumberScroll::visit() {
    //    启动遮罩效果
    glEnable(GL_SCISSOR_TEST);
    CCPoint pos = CCPointZero;
    //    获取visibleNode节点屏幕绝对位置
    pos = visibleNode->getParent()->convertToWorldSpace(pos);
    CCRect rect = CCRectMake(pos.x, pos.y, this->fontsize, this->fontsize);
    //    设置遮罩效果
    glScissor(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    CCNode::visit();
    //    关闭遮罩效果
    glDisable(GL_SCISSOR_TEST);
}

void CFNumberScroll::setNumber(int var)
{
    //    停止本节点的所有动作
    this->stopAllActions();
    //    移动到到节点坐标
    CCPoint moveToPosition = ccp(visibleNode->getPosition().x,-var*this->fontsize);
    //    创建动作移动到该节点
    CCMoveTo* moveAction = CCMoveTo::create(var *1, moveToPosition);
    //    运行该动作
    visibleNode->runAction(moveAction);  
}