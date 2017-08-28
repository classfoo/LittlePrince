#include "CFGameStatus.h"

void CFGameStatusListener::onGameTaskAward(int gifttype, const char* awardname, int seconds){
}

CFGameStatus::CFGameStatus():label(NULL),giftcount(0),gift(NULL),award(NULL){

}

CFGameStatus::~CFGameStatus(){

}

CFGameStatus* CFGameStatus::create(int gifttype, CFGameStatusListener* listener, CFGameContext *context){
    CFGameStatus* status = new CFGameStatus();
    status->gifttype = gifttype;
    status->context = context;
    status->listener = listener;
    status->giftname = context->getCurrentLevel()->getGiftName(gifttype);
    status->giftawardcount = context->getCurrentLevel()->getGiftAwardCount(gifttype);
    status->giftseconds = context->getCurrentLevel()->getGiftSeconds(gifttype);
    status->awardname = context->getCurrentLevel()->getGiftAward(gifttype);
    status->awardseconds = context->getCurrentLevel()->getGiftAwardSeconds(gifttype);
    status->init();
    status->autorelease();
    return status;
}

bool CFGameStatus::init(){
    this->award = CCNode::create();
    this->award->setVisible(false);
    this->award->setPosition(ccp(96, 32));
    CCSprite* awardbg = CCSprite::create("task-bg.png");
    this->award->addChild(awardbg);
    CCSprite* awardicon = CCSprite::create(CCString::createWithFormat("%s.png", this->awardname)->getCString());
    this->awardscale = this->getFitScale(awardicon);
    this->award->addChild(awardicon);
    this->addChild(award);
    CCString* giftname = CCString::createWithFormat("%s.png", this->giftname);
    this->gift = CCSprite::create(giftname->getCString());
    this->giftscale = this->getFitScale(gift);
    this->gift->setPosition(ccp(32,32));
    this->addChild(this->gift);
    this->label = CCLabelBMFont::create("X0", "Sniglet32.fnt", 192);
    this->label->setPosition(ccp(96, 32));
    this->addChild(label);
    this->setVisible(false);
    this->scheduleUpdate();
    return true;
}

void CFGameStatus::update(float dt){
    time_t current;
    time(&current);
    long during = current - this->starttime;
    if(during > this->giftseconds){
        this->status = 0;
        //this->setVisible(false);
    }
}

void CFGameStatus::showGift(){
    this->setVisible(true);
    this->gift->runAction(CCSequence::create(CCScaleTo::create(0.3, 1.5),CCScaleTo::create(0.3, giftscale), NULL));
    this->label->runAction(CCSequence::create(CCScaleTo::create(0.3, 1.5),CCScaleTo::create(0.3, 1), NULL));
    this->giftcount=0;
    CCString* counttext = CCString::createWithFormat("X%i", this->giftcount);
    this->label->setString(counttext->getCString());}

void CFGameStatus::addGift(){
    this->setVisible(true);
    this->gift->runAction(CCSequence::create(CCScaleTo::create(0.3, 1.5),CCScaleTo::create(0.3, giftscale), NULL));
    this->label->runAction(CCSequence::create(CCScaleTo::create(0.3, 1.5),CCScaleTo::create(0.3, 1), NULL));
    this->giftcount++;
    CCString* counttext = CCString::createWithFormat("X%i", this->giftcount);
    this->label->setString(counttext->getCString());
    time(&this->starttime);
    if(giftcount==giftawardcount){
        this->listener->onGameTaskAward(this->gifttype, this->awardname, this->awardseconds);
        this->giftcount = 0;
        this->runAwardAction();
    }
    this->context->playEffect("kidscheering.mp3", false);
}

void CFGameStatus::runAwardAction(){
    CCFiniteTimeAction* action1 = CCCallFunc::create(this,SEL_CallFunc(&CFGameStatus::showAward));
    CCFiniteTimeAction* action2 = CCScaleTo::create(0.5, 2);
    CCFiniteTimeAction* action3 = CCScaleTo::create(0.5, awardscale);
    //CCFiniteTimeAction* action4 = CCCallFunc::create(this,SEL_CallFunc(&CFGameStatus::hideAward));
    CCSequence* seq = CCSequence::create(action1,action2,action3, NULL);
    this->award->runAction(seq);
}

void CFGameStatus::showAward(){
    this->gift->setVisible(false);
    this->label->setVisible(false);
    this->award->setVisible(true);
}

void CFGameStatus::hideAward(){
    this->gift->setVisible(true);
    this->label->setVisible(true);
    this->award->setVisible(false);
}

CCSize CFGameStatus::getContentSize(){
    return CCSize(256, 64);
}

float CFGameStatus::getFitScale(cocos2d::CCSprite *sprite){
    CCSize size = sprite->getContentSize();
    int width = size.width>size.height?size.width:size.height;
    return 48.0f/width;
}