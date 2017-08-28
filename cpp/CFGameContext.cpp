#include "CFGameContext.h"

CFGameSpaceContext::CFGameSpaceContext(){

}

CFGameSpaceContext::~CFGameSpaceContext(){

}

bool CFGameSpaceContext::isActive(){
    return false;
}

void CFGameSpaceContext::onStartGame(CCObject *pSender){

}

void CFGameSpaceContext::onPauseGame(CCObject *pSender){

}

void CFGameSpaceContext::onResumeGame(CCObject *pSender){

}

void CFGameSpaceContext::onCloseGame(CCObject *pSender){

}

void CFGameSpaceContext::onPassGame(CCObject* pSender){

}

void CFGameSpaceContext::onChangeToLevel(CCObject *pSender, int level){

}

void CFGameSpaceContext::onGameTaskStory(cocos2d::CCDictionary *task, int taskindex){

}

void CFGameSpaceContext::onGameTaskStart(cocos2d::CCDictionary *task, int taskindex){

}

void CFGameSpaceContext::onGameTaskOngoing(cocos2d::CCDictionary *task, int taskindex){

}

void CFGameSpaceContext::onGameTaskComplete(cocos2d::CCDictionary *task, int taskindex){

}

void CFGameSpaceContext::onBeforePassGame(){

}

void CFGameSpaceContext::onDoPassGame(){

}

void CFGameSpaceContext::onAfterPassGame(){

}

float CFGameSpaceContext::getSpeed(){
    return 0;
}

void CFGameSpaceContext::setSpeed(float speed){
}

void CFGameSpaceContext::speedRight(){
}

void CFGameSpaceContext::speedLeft(){
}

void CFGameSpaceContext::jump(float force){
}

void CFGameSpaceContext::recordEnergy(int energy){
}

void CFGameSpaceContext::setEnergy(int energy){
}

int CFGameSpaceContext::getEnergy(){
    return 0;
}

void CFGameSpaceContext::recordGift(int gifttype){

}

void CFGameSpaceContext::addCloud(const char* name, int initHeight, float initRot){

}

void CFGameSpaceContext::addEnemy(const char* filename, int enemyType, float initHeight,float initRot, float initSpeed){

}

void CFGameSpaceContext::addGift(int type, float initHeight, float initRot, float initSpeed){

}

void CFGameSpaceContext::showTips(CCArray* tips){
}

void CFGameSpaceContext::showStories(){

}

CFNode* CFGameSpaceContext::getPrince(){
    return NULL;
}

void CFGameSpaceContext::onBeganTouch(time_t beginTouchTime, cocos2d::CCPoint beginTouchLocation){
}

void CFGameSpaceContext::onEndTouch(time_t beginTouchTime, cocos2d::CCPoint beginTouchLocation, time_t endTouchTime, cocos2d::CCPoint endTouchLocation){
}

CFShader* CFGameSpaceContext::getShader(){
    return NULL;
}

b2World* CFGameSpaceContext::getWorld(){
    return NULL;
}


float CFGameSpaceContext::getPlanetX(){
    return 0;
}

float CFGameSpaceContext::getPlanetY(){
    return 0;
}

float CFGameSpaceContext::getPlanetZoom(){
    return 0;
}

float CFGameSpaceContext::getPlanetRotSpeed(){
    return 0;
}

float CFGameSpaceContext::getPlanetRot(){
    return 0;
}

float CFGameSpaceContext::getSunRot(){
    return 0;
}

float CFGameSpaceContext::getHeroHeight(){
    return 0;
}

float CFGameSpaceContext::getHeroSpeed(){
    return 0;
}

b2Body* CFGameSpaceContext::getHeroBody(){
    return NULL;
}

/*游戏选择界面*/
void CFGameBoardContext::onStartGame(cocos2d::CCObject *pSender){
    
}

void CFGameBoardContext::onPauseGame(cocos2d::CCObject *pSender){
    
}

void CFGameBoardContext::onResumeGame(cocos2d::CCObject *pSender){
    
}

void CFGameBoardContext::onCloseGame(cocos2d::CCObject *pSender){
    
}

void CFGameBoardContext::onPassGame(cocos2d::CCObject *pSender){

}

void CFGameBoardContext::onChangeToLevel(cocos2d::CCObject *pSender, int level){

}

void CFGameBoardContext::onBeforePassGame(){

}

void CFGameBoardContext::onDoPassGame(){

}

void CFGameBoardContext::onAfterPassGame(){

}

/*游戏主环境*/
CFGameContext::CFGameContext():started(false),english(false),boardContext(NULL),spaceContext(NULL),level(NULL),gamepassboard(NULL){
}

CFGameContext::~CFGameContext(){
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

bool CFGameContext::init(){
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCNode::init());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("jump.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("thunder.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("locked.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("mie.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("coin.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("tips.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("storystart.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("hit.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("taskstart.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("footstep.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("clapping.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("kidscheering.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("gamestart.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("flying.mp3").c_str());

        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("1.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("2.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("3.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("4.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("5.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("6.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("7.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("8.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("9.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("10.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("11.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("12.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("13.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("14.mp3").c_str());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCFileUtils::sharedFileUtils()->fullPathForFilename("15.mp3").c_str());
        //this->playMusic("loveromance.mp3", true);
        ccLanguageType lang = CCApplication::sharedApplication()->getCurrentLanguage();
        switch (lang) {
            case cocos2d::kLanguageChinese:
                this->english = false;
                this->lang = "cn";
                break;
            case cocos2d::kLanguageFrench:
                this->english = false;
                this->lang = "fr";
                break;
            case cocos2d::kLanguageKorean:
                this->english = false;
                this->lang = "kr";
                break;
            case cocos2d::kLanguageJapanese:
                this->english = false;
                this->lang = "jp";
                break;
            default:
                this->english = true;
                this->lang=NULL;
                break;
        }
        bRet = true;
    } while (0);
    return bRet;
}

void CFGameContext::playEffect(const char *name, bool loop){
    string jump = CCFileUtils::sharedFileUtils()->fullPathForFilename(name);
    SimpleAudioEngine::sharedEngine()->playEffect(jump.c_str(), loop);
}

void CFGameContext::playMusic(const char *name, bool loop){
    string jump = CCFileUtils::sharedFileUtils()->fullPathForFilename(name);
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.1);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(jump.c_str(), loop);
}

void CFGameContext::startGame(cocos2d::CCObject *pSender){
    if(this->boardContext != NULL){
        this->boardContext->onStartGame(pSender);
    }
    if(this->spaceContext != NULL){
        this->spaceContext->onStartGame(pSender);
    }
    this->playEffect("gamestart.mp3", false);
    this->started = true;
}

void CFGameContext::pauseGame(cocos2d::CCObject *pSender){
    if(this->boardContext != NULL){
        this->boardContext->onPauseGame(pSender);
    }
    if(this->spaceContext != NULL){
        this->spaceContext->onPauseGame(pSender);
    }
    this->started = false;
}

void CFGameContext::resumeGame(cocos2d::CCObject *pSender){
    if(this->boardContext != NULL){
        this->boardContext->onResumeGame(pSender);
    }
    if(this->spaceContext != NULL){
        this->spaceContext->onResumeGame(pSender);
    }
    this->playEffect("gamestart.mp3", false);
    this->started = true;
}

void CFGameContext::lockedGame(cocos2d::CCObject *pSender){
    this->playEffect("locked.mp3", false);
}

void CFGameContext::closeGame(cocos2d::CCObject *pSender){
    if(this->boardContext != NULL){
        this->boardContext->onCloseGame(pSender);
    }
    if(this->spaceContext != NULL){
        this->spaceContext->onCloseGame(pSender);
    }
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
        CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    #else
        CCDirector::sharedDirector()->end();
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
        #endif
    #endif
}

void CFGameContext::passGame(cocos2d::CCObject *pSender){
    this->onGamePass(NULL, 0);
}

bool CFGameContext::isGameStarted(){
    return this->started;
}

bool CFGameContext::isEnglish(){
    return this->english;
}

const char* CFGameContext::getLanguage(){
    return this->lang;
}

CFGameLevel* CFGameContext::changeToLevel(int level){
    if(this->level == NULL){
        this->level = this->loadLevel(level);
    }
    if(this->level->getLevel() != level){
        CFGameLevel* todelete = this->level;
        this->level = this->loadLevel(level);
        delete todelete;
    }
    if(this->boardContext != NULL){
        this->boardContext->onChangeToLevel(this, level);
    }
    if(this->spaceContext != NULL){
        this->spaceContext->onChangeToLevel(this, level);
    }
    CCUserDefault::sharedUserDefault()->setIntegerForKey("lastLevel", level);
    CCUserDefault::sharedUserDefault()->flush();
    return this->level;
}

CFGameLevel* CFGameContext::getCurrentLevel(){
    if(this->level == NULL){
        int lastLevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("lastLevel", 1);
        this->changeToLevel(lastLevel);
    }
    return this->level;
}

CFGameLevel* CFGameContext::loadLevel(int level){
    CCString* string = this->isEnglish()?CCString::createWithFormat("level%d.plist", level):CCString::createWithFormat("level%d_%s.plist", level,this->getLanguage());
    CCDictionary* dict = CCDictionary::createWithContentsOfFile(string->getCString());
    CFGameLevel* pLevel = CFGameLevel::create(level, dict);
    return pLevel;
}

void CFGameContext::onBeganTouch(time_t beginTouchTime, CCPoint beginTouchLocation){
    if(!this->isGameStarted()){
        return;
    }
    this->spaceContext->onBeganTouch(beginTouchTime, beginTouchLocation);
}

void CFGameContext::onEndTouch(time_t beginTouchTime, CCPoint beginTouchLocation, time_t endTouchTime, CCPoint endTouchLocation){
    if(!this->isGameStarted()){
        return;
    }
    this->spaceContext->onEndTouch(beginTouchTime, beginTouchLocation, endTouchTime, endTouchLocation);
}

void CFGameContext::onGamePass(CCDictionary* pet, int countleft){
    this->onBeforePassGame();
}

void CFGameContext::onBeforePassGame(){
    this->started = false;
    if(this->boardContext != NULL){
        this->boardContext->onBeforePassGame();
    }
    if(this->spaceContext != NULL){
        this->spaceContext->onBeforePassGame();
    }
    if(this->gamepassboard != NULL){
        this->gamepassboard->removeFromParentAndCleanup(true);
        this->gamepassboard = NULL;
    }
    this->gamepassboard = CCSprite::create("gamepass.png");
    this->gamepassboard->setVisible(true);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    gamepassboard->setPosition(ccp(size.width/2,size.height/2));
    this->addChild(gamepassboard);
    const char* info = this->level->getGamePassInfo();
    const ccColor3B color = ccc3(8, 36, 239);
    CFLabel* label = CFLabel::create(info, "Sniglet32.fnt", 32, color, gamepassboard->getContentSize().width*0.8, gamepassboard->getContentSize().height*0.8);
    label->setPosition(ccp(gamepassboard->getContentSize().width/2, gamepassboard->getContentSize().height/2));
    gamepassboard->addChild(label);
    
    CCSequence* action1 = CCSequence::create(CCScaleTo::create(1, 1.2), CCScaleTo::create(1, 1), NULL);
    CCRepeat* action2 = CCRepeat::create(action1, 2);
    gamepassboard->runAction(CCSequence::create(action2, CCCallFunc::create(this, SEL_CallFunc(&CFGameContext::onDoPassGame)), NULL));
}

void CFGameContext::onDoPassGame(){
    if(this->boardContext != NULL){
        this->boardContext->onDoPassGame();
    }
    if(this->spaceContext != NULL){
        this->spaceContext->onDoPassGame();
    }
    int currentLevel = this->level->getLevel();
    this->changeToLevel(currentLevel+1);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("currentProgress", currentLevel+1);
    CCUserDefault::sharedUserDefault()->flush();
    if(gamepassboard != NULL){
        gamepassboard->removeAllChildrenWithCleanup(true);
        const char* info = this->level->getGameStartInfo();
        const ccColor3B color = ccc3((GLuint)8, (GLuint)36, (GLuint)239);
        CFLabel* label = CFLabel::create(info, "Sniglet32.fnt", 32, color, gamepassboard->getContentSize().width*0.8,gamepassboard->getContentSize().height*0.8);
        label->setPosition(ccp(gamepassboard->getContentSize().width/2, gamepassboard->getContentSize().height/2));
        gamepassboard->addChild(label);

        CCSequence* action1 = CCSequence::create(CCScaleTo::create(1, 1.2), CCScaleTo::create(1, 1), NULL);
        CCRepeat* action2 = CCRepeat::create(action1, 2);
        gamepassboard->runAction(CCSequence::create(action2, CCCallFunc::create(this, SEL_CallFunc(&CFGameContext::onAfterPassGame)), NULL));
    }
}

void CFGameContext::onAfterPassGame(){
    if(this->boardContext != NULL){
        this->boardContext->onAfterPassGame();
    }
    if(this->spaceContext != NULL){
        this->spaceContext->onAfterPassGame();
    }
    if(this->gamepassboard != NULL){
        this->gamepassboard->setVisible(false);
        this->gamepassboard->removeFromParentAndCleanup(true);
        this->gamepassboard = NULL;
    }
    this->startGame(this);
}

void CFGameContext::onGameTaskStory(cocos2d::CCDictionary *task, int taskindex){
    if(this->spaceContext != NULL){
        this->spaceContext->onGameTaskStory(task, taskindex);
    }
}

void CFGameContext::onGameTaskStart(CCDictionary *task, int taskindex){
    if(this->spaceContext != NULL){
        this->spaceContext->onGameTaskStart(task,taskindex);
    }
}

void CFGameContext::onGameTaskOngoing(cocos2d::CCDictionary *task, int taskindex){
    if(this->spaceContext != NULL){
        this->spaceContext->onGameTaskOngoing(task,taskindex);
    }
}

void CFGameContext::onGameTaskComplete(CCDictionary *task, int taskindex){
    if(this->spaceContext != NULL){
        this->spaceContext->onGameTaskComplete(task, taskindex);
    }
}

void CFGameContext::setBoardContext(CFGameBoardContext *boardContext){
    this->boardContext = boardContext;
    this->boardContext->init();
    this->addChild(boardContext);
}

CFGameBoardContext* CFGameContext::getBoardContext(){
    return this->boardContext;
}

void CFGameContext::setSpaceContext(CFGameSpaceContext *spaceContext){
    this->spaceContext = spaceContext;
    this->spaceContext->init();
    this->addChild(spaceContext);
}

CFGameSpaceContext* CFGameContext::getSpaceContext(){
    return this->spaceContext;
}
