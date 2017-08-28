#include "CFGameStatusBoard.h"
CFGameStatusBoard::CFGameStatusBoard():listener(NULL){
}

CFGameStatusBoard::~CFGameStatusBoard(){
}

CFGameStatusBoard* CFGameStatusBoard::create(CFGameStatusListener* listener, CFGameContext* context){
    CFGameStatusBoard* board = new CFGameStatusBoard();
    board->listener = listener;
    board->context = context;
    board->init();
    board->autorelease();
    return board;
}

bool CFGameStatusBoard::init(){
    if(!CCNode::init()){
        return false;
    }
    CFGameLevel* level = this->context->getCurrentLevel();
    int count = level->getGiftTypeCount();
    int width = 0;
    int height = 0;
    int posY = 0;
    for(int i = 0;i < count;i++){
        CFGameStatus* status = CFGameStatus::create(i, listener, context);
        CCSize statusSize = status->getContentSize();
        if(statusSize.width>width){
            width = statusSize.width;
        }
        if(statusSize.height>height){
            height = statusSize.height;
        }
        status->setPosition(ccp(0, posY));
        posY+=height;
        this->addChild(status);
    }
    this->size = CCSize(width, height);
    this->scheduleUpdate();
    return true;
}

void CFGameStatusBoard::update(float dt){
}

void CFGameStatusBoard::addGift(int gifttype){
    CFGameLevel* level = this->context->getCurrentLevel();
    int status = level->getCurrentTaskStatus();
    if(status != gifttype + 3){
        return;
    }
    CFGameStatus* target = (CFGameStatus*)this->getChildren()->objectAtIndex(gifttype);
    float targetY = target->getPositionY();
    target->setPosition(ccp(0, 0));
    target->addGift();
    this->reorderStatuses(gifttype, targetY);
}

void CFGameStatusBoard::showGift(int gifttype){
    CFGameStatus* target = (CFGameStatus*)this->getChildren()->objectAtIndex(gifttype);
    float targetY = target->getPositionY();
    target->setPosition(ccp(0, 0));
    target->showGift();
    this->reorderStatuses(gifttype, targetY);

}

void CFGameStatusBoard::reorderStatuses(int gifttype, float targetY){
    CCArray* children = this->getChildren();
    int count = children->count();
    for(int i = 0; i < count;i++){
        if(gifttype == i){
            continue;
        }
        CFGameStatus* status = (CFGameStatus*)this->getChildren()->objectAtIndex(i);
        float statusY = status->getPositionY();
        if(statusY>=targetY){
            status->setPosition(ccp(0, statusY-status->getContentSize().height));
        }
    }
}

CCSize CFGameStatusBoard::getContentSize(){
    return this->size;
}