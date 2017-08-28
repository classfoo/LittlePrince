#include "CFGameStoryBoard.h"
CFGameStoryBoard::CFGameStoryBoard():label(NULL),showing(false),context(NULL){
    
}

CFGameStoryBoard::~CFGameStoryBoard(){
    
}

CFGameStoryBoard* CFGameStoryBoard::create(CFGameContext* context){
    CFGameStoryBoard* board = new CFGameStoryBoard();
    board->context = context;
    board->init();
    board->autorelease();
    return board;
}

bool CFGameStoryBoard::init(){
    this->scheduleUpdate();
    return true;
}

void CFGameStoryBoard::update(float dt){

}

void CFGameStoryBoard::showStory(){
    if(this->isShowing()){
        return;
    }
    const char * story = this->context->getCurrentLevel()->checkTaskStories(this->context);
    if(story == NULL){
        return;
    }
    if(this->label == NULL){
        this->background = CCMenuItemImage::create("infoboard.png","infoboard.png",this,SEL_MenuHandler(&CFGameStoryBoard::hideInfo));
        CCMenu* infoMenu = CCMenu::create(this->background, NULL);
        infoMenu->setPosition(CCPointZero);
        this->addChild(infoMenu, 1);
        this->size = this->background->getContentSize();
        if(this->label != NULL)this->label->removeFromParentAndCleanup(true);
        const ccColor3B color = ccc3(255, 255, 255);
        this->label = CFLabel::create(story, "LevelMedium.fnt", 32, color, this->background->getContentSize().width*0.8, this->background->getContentSize().height);
        this->label->setPosition(ccp(this->background->getContentSize().width/2, this->background->getContentSize().height/2));
        this->background->addChild(this->label);
        ccLanguageType lang = CCApplication::sharedApplication()->getCurrentLanguage();
        switch (lang) {
            case cocos2d::kLanguageChinese:{
                this->nextTip = CCLabelTTF::create("点击继续...", "Heiti SC", 25);
                break;
            }
            case cocos2d::kLanguageFrench:{
                this->nextTip = CCLabelTTF::create("Touchez Pour Suivant...", "Arial", 25);
                break;
            }
            case cocos2d::kLanguageKorean:{
                this->nextTip = CCLabelTTF::create("다음에 터치...", "Heiti K", 25);
                break;
            }
            case cocos2d::kLanguageJapanese:{
                this->nextTip = CCLabelTTF::create("次へのタッチ...", "Heiti J", 25);
                break;
            }
            default:{
                this->nextTip = CCLabelTTF::create("Touch To Next...", "Arial", 25);
                break;
            }
        }
        this->nextTip->setPosition(ccp(this->background->getContentSize().width/2,this->nextTip->getContentSize().height*1.5));
        this->background->addChild(this->nextTip);
    }else{
        this->label->setString(story);
    }
    this->background->stopAllActions();
    this->nextTip->setVisible(false);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize bgSize = this->background->getContentSize();
    this->background->setPosition(ccp(-winSize.width, -winSize.height/2));
    this->showing = true;
    CCMoveTo* action1 = CCMoveTo::create(0.3, ccp(winSize.width/2, -winSize.height/2));
    CCScaleTo* action2 = CCScaleTo::create(1, 1.1);
    CCScaleTo* action3 = CCScaleTo::create(1, 1);
    CCCallFunc* action4 = CCCallFunc::create(this, SEL_CallFunc(&CFGameStoryBoard::showNextTip));
    CCSequence* seq = CCSequence::create(action1, action2,action3, action4, NULL);
    this->background->runAction(seq);
    this->context->playEffect("storystart.mp3", false);
}

void CFGameStoryBoard::showNextTip(){
    this->nextTip->setVisible(true);
}

void CFGameStoryBoard::hideInfo(){
    if(!this->nextTip->isVisible()){
        return;
    }
    if(!this->context->isGameStarted()){
        return;
    }
    this->context->playEffect("hit.mp3",false);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCMoveTo* action4 = CCMoveTo::create(0.5, ccp(-winSize.width, -winSize.height/2));
    CCCallFunc* action5 = CCCallFunc::create(this, SEL_CallFunc(&CFGameStoryBoard::setIsNotShowing));
    CCSequence* seq = CCSequence::create(action4, action5 ,NULL);
    this->background->runAction(seq);
}

void CFGameStoryBoard::setIsNotShowing(){
    this->showing = false;
    this->showStory();
}

bool CFGameStoryBoard::isShowing(){
    return this->showing;
}