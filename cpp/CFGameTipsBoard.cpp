#include "CFGameTipsBoard.h"
CFGameTipsBoard::CFGameTipsBoard():showing(false), index(0), background(NULL){
    
}

CFGameTipsBoard::~CFGameTipsBoard(){
    
}

CFGameTipsBoard* CFGameTipsBoard::create(CFGameContext* context, CFGameStoryBoard* infoboard){
    CFGameTipsBoard* board = new CFGameTipsBoard();
    board->context = context;
    board->infoboard = infoboard;
    board->init();
    board->autorelease();
    return board;
}

bool CFGameTipsBoard::init(){
    this->scheduleUpdate();
    return true;
}

void CFGameTipsBoard::update(float dt){
    
}

void CFGameTipsBoard::setTips(CCArray* tips){
    if(tips == NULL || tips->count() == 0){
        return;
    }
    if(this->isShowing()){
        return;
    }
    if(this->infoboard != NULL && this->infoboard->isShowing()){
        return;
    }
    this->showing = true;
    if(index >= tips->count()){
        index = 0;
    }
    if(this->background != NULL){
        this->background->removeFromParentAndCleanup(true);
    }
    this->background = CCSprite::create("tips.png");
    CCDictionary* tip = (CCDictionary*) tips->objectAtIndex(index);
    const char* left = CFCocosUtil::getStringFromDict(tip, "left", NULL);
    const char* right = CFCocosUtil::getStringFromDict(tip, "right", NULL);
    const char* result = CFCocosUtil::getStringFromDict(tip, "result", NULL);
    CCSprite* leftSprite = CCSprite::create(left);
    int gap = 100;
    leftSprite->setScale(this->getFitScale(leftSprite));
    leftSprite->setPosition(ccp(gap, this->background->getContentSize().height/2));
    CCSprite* mulSprite = CCSprite::create("multi.png");
    mulSprite->setPosition(ccp(gap+10+64, this->background->getContentSize().height/2));
    CCSprite* rightSprite = CCSprite::create(right);
    float getFitScale(CCSprite* sprite);
    rightSprite->setPosition(ccp(gap+20+64+mulSprite->getContentSize().width, this->background->getContentSize().height/2));
    CCSprite* equSprite = CCSprite::create("equ.png");
    equSprite->setColor(ccc3(255, 255, 255));
    equSprite->setPosition(ccp(gap+30+64+mulSprite->getContentSize().width+rightSprite->getContentSize().width, this->background->getContentSize().height/2));
    CCSprite* resultSprite = CCSprite::create(result);
    resultSprite->setScale(this->getFitScale(resultSprite));
    resultSprite->setPosition(ccp(gap+40+64+mulSprite->getContentSize().width+rightSprite->getContentSize().width+equSprite->getContentSize().width, this->background->getContentSize().height/2));
    this->background->addChild(leftSprite);
    this->background->addChild(mulSprite);
    this->background->addChild(rightSprite);
    this->background->addChild(equSprite);
    this->background->addChild(resultSprite);
    this->addChild(this->background);
    this->background->stopAllActions();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize bgSize = this->background->getContentSize();
    this->background->setPosition(ccp(-winSize.width, -bgSize.height/2));
    this->showing = true;
    CCMoveTo* action1 = CCMoveTo::create(0.3, ccp(winSize.width/2, -bgSize.height/2));
    CCScaleTo* action2 = CCScaleTo::create(2, 1.2);
    CCScaleTo* action3 = CCScaleTo::create(2, 1);
    CCMoveTo* action4 = CCMoveTo::create(0.5, ccp(-winSize.width, -bgSize.height/2));
    CCCallFunc* action5 = CCCallFunc::create(this, SEL_CallFunc(&CFGameTipsBoard::setIsNotShowing));
    CCSequence* seq = CCSequence::create(action1, action2,action3,action4, action5, NULL);
    this->background->runAction(seq);
    this->context->playEffect("tips.mp3", false);
}

void CFGameTipsBoard::setIsNotShowing(){
    this->showing = false;
    index++;
}

bool CFGameTipsBoard::isShowing(){
    return this->showing;
}

float CFGameTipsBoard::getFitScale(cocos2d::CCSprite *sprite){
    CCSize size = sprite->getContentSize();
    int width = size.width>size.height?size.width:size.height;
    return 48.0f/width;
}