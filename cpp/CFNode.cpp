#include "CFNode.h"

CFNode::CFNode():speed(0),height(0),rot(0),infoboard(NULL),type(-1){

}

CFNode::~CFNode(){
}

int CFNode::getType(){
    return this->type;
}

float CFNode::getHeight(){
    return this->height;
}

void CFNode::setHeight(float height){
    this->height = height;
}

float CFNode::getLineSpeed(){
    return this->speed;
}

void CFNode::setLineSpeed(float speed){
    this->speed = speed;
}

float CFNode::getRot(){
    return this->rot;
}

void CFNode::setRot(float rot){
    this->rot = rot;
}

bool CFNode::isShowingInfo(){
    if(this->infoboard == NULL){
        return false;
    }
    return this->infoboard->isShowing();
}

void CFNode::showInfo(const char *info, const char* font, float size, const ccColor3B color, float width, float posy, CCObject* obj, SEL_CallFunc callback){
    if(this->infoboard == NULL){
        this->infoboard = CFNodeInfoBoard::create(font, size, color, width, obj, callback);
        this->infoboard->setInfo(info);
        this->infoboard->setPosition(ccp(0, posy));
        this->infoboard->setVisible(false);
        this->addChild(this->infoboard);
    }
    this->infoboard->setInfo(info);
}

void CFNode::onConflict(b2Contact *contact, CFNode *other){

}

void CFNode::onEndConflict(b2Contact *contact, CFNode *other){

}

CCSize CFNode::getContentSize(){
    return CCNode::getContentSize();
}
