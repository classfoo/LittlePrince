#include "CFNodeInfoBoard.h"

CFNodeInfoBoard::CFNodeInfoBoard():label(NULL), font(NULL), obj(NULL){

}

CFNodeInfoBoard::~CFNodeInfoBoard(){

}

CFNodeInfoBoard* CFNodeInfoBoard::create(const char* font, float size, const ccColor3B color, float width, CCObject* obj, SEL_CallFunc callback){
    CFNodeInfoBoard* board = new CFNodeInfoBoard();
    board->width = width;
    board->font = font;
    board->fontsize = size;
    board->color = color;
    board->obj = obj;
    board->callback = callback;
    board->init();
    board->autorelease();
    return board;
}

bool CFNodeInfoBoard::init(){
    this->scheduleUpdate();
    return true;
}

void CFNodeInfoBoard::update(float dt){
    if(start == -1){
        return;
    }
    if(this->label == NULL){
        return;
    }
    this->label->setPosition(ccp(this->label->getPosition().x, this->label->getPosition().y+1));
    time_t current;
    time(&current);
    if(current - start >= 5){
        start = -1;
        this->setVisible(false);
        (this->obj->*callback)();
    }
}

void CFNodeInfoBoard::setInfo(const char* msg){
    if(this->label != NULL){
        this->label->removeFromParentAndCleanup(true);
        this->label = NULL;
    }
    this->label = CFLabel::create(msg, this->font, this->fontsize, this->color, this->width, 150);
    this->size = this->label->getContentSize();
    this->label->setPosition(ccp(0, 0));
    this->addChild(this->label);
    this->setVisible(true);
    time(&start);
}

bool CFNodeInfoBoard::isShowing(){
    return this->isVisible();
}

CCSize CFNodeInfoBoard::getContentSize(){
    return this->size;
}