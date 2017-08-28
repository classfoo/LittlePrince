#include "CFGameSpace.h"

CFGameSpace::CFGameSpace(void):inited(false),sky(NULL),planet(NULL), planetItems(NULL), princeItems(NULL), storyboard(NULL),tipsboard(NULL),prince(NULL), boardItems(NULL), statusboard(NULL), petItems(NULL),pet(NULL),clouds(NULL),enemies(NULL), gifts(NULL),woohoo(NULL){
    gbcache = gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    gbcache->reset();
    gbcache->addShapesWithFile("box2d.plist");
    //shader效果
    this->shader = new CFShader();    
    b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
    bool doSleep = false;
    world = new b2World(gravity);
    world->SetAllowSleeping(doSleep);
    listener = new CFContactListener();
    world->SetContactListener(listener);
}

CFGameSpace::~CFGameSpace(void){
    if(world != NULL){
        delete world;
        world = NULL;
    }
    if(this->shader != NULL){
        delete shader;
        shader = NULL;
    }
    if(gbcache != NULL){
        delete gbcache;
        gbcache = NULL;
    }
    if(listener!=NULL){
        delete listener;
        listener = NULL;
    }
}

CFGameSpace* CFGameSpace::create(CFGameContext* context){
    CFGameSpace* game = new CFGameSpace();
    game->context = context;
    game->autorelease();
    return game;
}

bool CFGameSpace::init(){
    inited = false;
    do{
        //依次加载天空，星球，星球场景，宠物，小王子，得分榜
        //this->onChangeToLevel(NULL);
        //最后加载菜单
        this->loadMenus();
        scheduleUpdate();
        inited = true;
    }while(0);
    return inited;
}

void CFGameSpace::update(float dt){
    int velocityIterations = 4;
    int positionIterations = 1;
    world->Step(dt, velocityIterations, positionIterations);
}

void CFGameSpace::loadMenus(){
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    //close menu
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png","CloseSelected.png",this->context,SEL_MenuHandler(&CFGameContext::pauseGame));
    pCloseItem->setPosition(ccp(origin.x  + pCloseItem->getContentSize().width/2 ,origin.y + size.height - pCloseItem->getContentSize().height/2));
    CCMenu* closeMenu = CCMenu::create(pCloseItem, NULL);
    closeMenu->setPosition(CCPointZero);
    this->addChild(closeMenu, 1);
}

void CFGameSpace::onStartGame(cocos2d::CCObject *pSender){
    if(this->statusboard != NULL){
        this->statusboard->setVisible(true);
    }
}

void CFGameSpace::onPauseGame(CCObject* pSender){
    if(this->statusboard != NULL){
        this->statusboard->setVisible(false);
    }
    if(this->storyboard != NULL){
        this->storyboard->setVisible(false);
    }
}

void CFGameSpace::onResumeGame(cocos2d::CCObject *pSender){
    if(this->statusboard != NULL){
        this->statusboard->setVisible(true);
    }
    if(this->storyboard != NULL){
        this->storyboard->setVisible(true);
    }
}

void CFGameSpace::onPassGame(cocos2d::CCObject *pSender){
    if(this->statusboard != NULL){
        this->statusboard->setVisible(true);
    }
}

void CFGameSpace::onCloseGame(cocos2d::CCObject *pSender){
    //TODO
}

void CFGameSpace::onChangeToLevel(CCObject *pSender, int level){
    //再次加载天空
    this->reloadSky();
    //再次加载planet
    this->reloadPlanet();
    //再次加载星球场景
    this->reloadPlanetItems();
    //再次加载宠物
    this->reloadPet();
    //再次加载云容器
    this->reloadClouds();
    //再次加载enemies容器
    this->reloadEnemies();
    //再次加载gifts
    this->reloadGifts();
    //再次加载英雄
    this->reloadPrince();
    //再次加载得分榜
    this->reloadBoards();
}

void CFGameSpace::reloadSky(){
    //首先加载天空
    if(this->sky != NULL){
        this->sky->removeFromParentAndCleanup(true);
    }
    this->sky = CFSky::create(this->context);
    this->addChild(sky);
}

void CFGameSpace::reloadPlanet(){
    //其次加载星球
    if(this->planet != NULL){
        this->planet->removeFromParentAndCleanup(true);
    }
    this->planet = CFPlanet::create(this->context);
    this->addChild(planet);
}

void CFGameSpace::reloadPlanetItems(){
    if(this->planetItems != NULL){
        this->planetItems->removeFromParentAndCleanup(true);
    }
    this->planetItems = CCNode::create();
    this->addChild(planetItems);
    CFGameLevel* level = this->context->getCurrentLevel();
    CCArray* items =  level->getPlanetItems();
    if(items == NULL){
        return;
    }
    for (int i = 0; i<items->count(); i++) {
        CCDictionary* dict = (CCDictionary*)items->objectAtIndex(i);
        const char* name = CFCocosUtil::getStringFromDict(dict, "name", "volcano");
        //CCLog("%s", name);
        const char* night = CFCocosUtil::getStringFromDict(dict, "night", NULL);
        float initHeight = CFCocosUtil::getFloatFromDict(dict, "initHeight", 0);
        float initRot = CFCocosUtil::getFloatFromDict(dict, "initRot", 0);
        float initSpeed = CFCocosUtil::getFloatFromDict(dict, "initSpeed", 0);
        float z = CFCocosUtil::getIntFromDict(dict, "z", 0);
        const char* product = CFCocosUtil::getStringFromDict(dict, "product", NULL);
        CFPlanetItem* item = CFPlanetItem::create(i, name, night, initHeight, initRot, initSpeed,z,product, this->context);
        this->planetItems->addChild(item);
    }
}

void CFGameSpace::reloadBoards(){
    if(this->boardItems != NULL){
        this->boardItems->removeAllChildrenWithCleanup(true);
    }
    this->boardItems = CCNode::create();
    this->boardItems->setPosition(ccp(0, 0));
    this->addChild(boardItems);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    //游戏gift获取后的显示区域
    this->statusboard = CFGameStatusBoard::create(this, this->context);
    this->statusboard->setVisible(false);
    CCSize statusboardSize = this->statusboard->getContentSize();
    this->statusboard->setPosition(ccp(size.width - statusboardSize.width/2, size.height-statusboardSize.height));
    this->boardItems->addChild(this->statusboard);
    //游戏消息提醒区域
    this->storyboard = CFGameStoryBoard::create(this->context);
    this->storyboard->setPosition(ccp(0, size.height));
    //游戏任务提醒区域
    this->tipsboard = CFGameTipsBoard::create(this->context, this->storyboard);
    this->tipsboard->setPosition(ccp(0, size.height));
    //infoboard放到tipsboard之上
    this->boardItems->addChild(this->tipsboard);
    this->boardItems->addChild(this->storyboard);
}

void CFGameSpace::reloadPet(){
    if(this->petItems != NULL){
        this->petItems->removeAllChildrenWithCleanup(true);
    }else{
    }
    this->petItems = CCNode::create();
    this->addChild(this->petItems);
    this->pet = CFPet::create(this->context);
    this->petItems->addChild(this->pet);
}

void CFGameSpace::reloadPrince(){
    if(this->princeItems != NULL){
        this->princeItems->removeAllChildrenWithCleanup(true);
    }
    this->princeItems = CCNode::create();
    this->addChild(this->princeItems);
    this->prince = CFPrince::create(this->context);
    this->prince->setSpeed(10);
    this->princeItems->addChild(this->prince);
}

void CFGameSpace::reloadClouds(){
    if(this->clouds != NULL){
        this->clouds->removeAllChildrenWithCleanup(true);
    }
    this->clouds = CCNode::create();
    this->addChild(this->clouds);

}

void CFGameSpace::reloadEnemies(){
    if(this->enemies != NULL){
        this->enemies->removeAllChildrenWithCleanup(true);
    }
    this->enemies = CCNode::create();
    this->addChild(this->enemies);

}

void CFGameSpace::reloadGifts(){
    if(this->gifts != NULL){
        this->gifts->removeAllChildrenWithCleanup(true);
    }
    this->gifts = CCNode::create();
    this->addChild(this->gifts);

}

void CFGameSpace::onBeganTouch(time_t beginTouchTime, cocos2d::CCPoint beginTouchLocation){
    if(this->prince == NULL){
        return;
    }
    this->prince->onBeganTouch(beginTouchTime, beginTouchLocation);
}

void CFGameSpace::onEndTouch(time_t beginTouchTime, cocos2d::CCPoint beginTouchLocation, time_t endTouchTime, cocos2d::CCPoint endTouchLocation){
    if(this->prince == NULL){
        return;
    }
    this->prince->onEndTouch(beginTouchTime, beginTouchLocation, endTouchTime, endTouchLocation);
}

void CFGameSpace::showTips(CCArray *tips){
    if(this->tipsboard == NULL){
        return;
    }
    this->tipsboard->setTips(tips);
}

void CFGameSpace::showStories(){
    if(this->storyboard == NULL){
        return;
    }
    this->storyboard->showStory();
}

bool CFGameSpace::isActive(){
    return false;
}

float CFGameSpace::getSpeed(){
    if(this->prince == NULL){
        return 0;
    }
    return this->prince->getSpeed();
}

void CFGameSpace::setSpeed(float speed){
    if(this->prince == NULL){
        return;
    }
    this->prince->setSpeed(speed);
}


void CFGameSpace::speedRight(){
    if(this->prince == NULL){
        return;
    }
    this->prince->speedRight();
}

void CFGameSpace::speedLeft(){
    if(this->prince == NULL){
        return;
    }
    this->prince->speedLeft();
}

void CFGameSpace::jump(float force){
    if(this->prince == NULL){
        return;
    }
    this->prince->jump(force);
}

void CFGameSpace::setEnergy(int energy){
    this->energy = energy;
}

void CFGameSpace::recordEnergy(int score){
    this->energy += score;
    if(this->energy < 0){
        this->energy = 0;
    }
}

int CFGameSpace::getEnergy(){
    return this->energy;
}

void CFGameSpace::recordGift(int gifttype){
    this->statusboard->addGift(gifttype);
}

void CFGameSpace::addCloud(const char* name, int initHeight, float initRot){
    if(this->clouds == NULL || this->clouds->getChildrenCount()>=10){
        return;
    }
    static int cloudtype = 0;
    if(cloudtype >9){
        cloudtype=0;
    }
    CCString* cloudName = CCString::createWithFormat("%s%d", name, cloudtype);
    CFCloud* cloud = CFCloud::create(cloudName->getCString(), initHeight, initRot, CCRANDOM_MINUS1_1()*10, this->context);
    this->clouds->addChild(cloud);
    cloudtype++;
}

void CFGameSpace::addEnemy(const char* enemyName, int enemyType, float initHeight,float initRot, float initSpeed){
    CFEnemy* enemy = CFEnemy::create(enemyName, enemyType, initHeight, initRot, initSpeed, this->context);
    this->enemies->addChild(enemy);
}

void CFGameSpace::addGift(int type, float initHeight, float initRot, float initSpeed){
    if(type == -1){
        return;
    }
    CFGameLevel* level = level =this->context->getCurrentLevel();
    const char* name = level->getGiftName(type);
    if(name == NULL){
        return;
    }
    int energy = level->getGiftEnergy(type);
    int action = level->getGiftAction(type);
    CFGift* gift = CFGift::create(type, energy, action, name, initHeight, initRot, initSpeed, context);
    this->gifts->addChild(gift);
}


void CFGameSpace::onGameTaskAward(int gifttype, const char* awardname, int seconds){
    this->prince->onGameTaskAward(gifttype, awardname, seconds);
    this->showWoohoo(awardname);
}

void CFGameSpace::onGameTaskStory(cocos2d::CCDictionary *task, int taskindex){
    if(this->prince!=NULL){
        this->prince->onGameTaskStory(task, taskindex);
    }
}

void CFGameSpace::onGameTaskStart(cocos2d::CCDictionary *task, int taskindex){
    if(this->prince != NULL){
        this->prince->onGameTaskStart(task, taskindex);
    }
    if(this->pet != NULL){
        this->pet->onGameTaskStart(task, taskindex);
    }
    if(this->statusboard != NULL){
        int status = CFCocosUtil::getIntFromDict(task, "status", 3);
        this->statusboard->showGift(status-3);
    }
}

void CFGameSpace::onGameTaskOngoing(cocos2d::CCDictionary *task, int taskindex){
    if(this->pet != NULL){
        this->pet->onGameTaskOngoing(task, taskindex);
    }
}

void CFGameSpace::onGameTaskComplete(cocos2d::CCDictionary *task, int taskindex){
    if(this->prince != NULL){
        this->prince->onGameTaskComplete(task, taskindex);
    }
    if(this->pet != NULL){
        this->pet->onGameTaskComplete(task, taskindex);
    }
    this->hideWoohoo();
}

void CFGameSpace::showWoohoo(const char *awardname){
    if(this->woohoo != NULL){
        this->woohoo->removeFromParentAndCleanup(true);
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    this->woohoo = CCLabelBMFont::create("WooHoo WooHoo", "LevelBig.fnt");
    this->woohoo->setPosition(ccp(size.width/2,size.height*5/6));
    this->woohoo->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(3, 1.3), CCScaleTo::create(3,1), NULL)));
    this->addChild(this->woohoo);
}

void CFGameSpace::hideWoohoo(){
    if(this->woohoo == NULL){
        return;
    }
    this->woohoo->removeFromParentAndCleanup(true);
    this->woohoo = NULL;
}

void CFGameSpace::onBeforePassGame(){
    //this->jump(700000);
    this->prince->setHeight(500000);
}

void CFGameSpace::onDoPassGame(){

}

void CFGameSpace::onAfterPassGame(){
    this->prince->setHeight(0);
}

CFNode* CFGameSpace::getPrince(){
    return this->prince;
}

CFShader* CFGameSpace::getShader(){
    return this->shader;
}

b2World* CFGameSpace::getWorld(){
    return this->world;
}

float CFGameSpace::getPlanetX(){
    if(this->planet == NULL){
        return 0;
    }
    return this->planet->getX();
}

float CFGameSpace::getPlanetY(){
    if(this->planet == NULL){
        return 0;
    }
    return this->planet->getY();
}

float CFGameSpace::getPlanetZoom(){
    if(this->planet == NULL){
        return 0;
    }
    return this->planet->getZoom();
}

float CFGameSpace::getPlanetRotSpeed(){
    if(this->planet == NULL){
        return 0;
    }
    return this->planet->getRotSpeed();
}

float CFGameSpace::getPlanetRot(){
    if(this->planet == NULL){
        return 0;
    }
    return this->planet->getRot();
}

float CFGameSpace::getSunRot(){
    if(this->planet == NULL){
        return 0;
    }
    return this->planet->getSunRot();
}

float CFGameSpace::getHeroHeight(){
    if(this->prince == NULL){
        return 0;
    }
    return this->prince->getHeight();
}

float CFGameSpace::getHeroSpeed(){
    if(this->prince == NULL){
        return 0;
    }
    return this->prince->getLineSpeed();
}

b2Body* CFGameSpace::getHeroBody(){
    if(this->prince == NULL){
        return NULL;
    }
    return this->prince->getBody();
}
