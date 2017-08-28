#include "CFPrince.h"

#define RUNSPEED 10
#define MAXSPEED 20

CFPrince::CFPrince():spadeVisible(false),swordVisible(false),isready(true),animationIndex(0),zoom(1),status(0),targetHeight(-1),highspeedParticle(NULL),award(NULL),body(NULL),node(NULL),armature(NULL){
    this->type = TYPE_HERO;
}

CFPrince::~CFPrince(){
    if(this->body!= NULL){
        if(context != NULL){
            this->context->getSpaceContext()->getWorld()->DestroyBody(this->body);
        }
    }
    if(this->node!= NULL){
        if(context != NULL){
            this->context->getSpaceContext()->getWorld()->DestroyBody(this->node);
        }
    }
}

CFPrince* CFPrince::create(CFGameContext* context){
    CFPrince* pPrince = new CFPrince();
    pPrince->context = context;
    pPrince->init();
    pPrince->autorelease();
    return pPrince;
}

bool CFPrince::init(){
    bool ret = false;
    do{
        //为prince设置初始位置，避免加载时位置错乱
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        this->setPosition(ccp(size.width/2, size.height/2));
        CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Hero0.png", "Hero0.plist", "Hero.ExportJson");
        this->armature = CCArmature::create("Hero");
        this->addChild(this->armature);
        this->armature->getAnimation()->playWithIndex(0);
        this->r = this->context->getCurrentLevel()->getPlanetR()/2;
        this->maxrotspeed = MAXSPEED/r;
        this->setSpadeVisible(false);
        this->setSwordVisible(false);
        scheduleUpdate();
        ret = true;
    }while(0);
    return ret;
}

void CFPrince::update(float dt){
    static int frame = 0;
    frame++;
    if(frame%60==0){
        frame = 0;
    }
    this->updateSpeed();
    this->updateBody();
    this->updateNode();
    this->updateArmature();
    this->updateEnergy(frame);
    this->updateStatus();
    this->updateTargetHeight();
    lastpos = this->getBody()->GetPosition();
}

void CFPrince::updateSpeed(){
    if(!this->context->isGameStarted()){
        //on pause
        if(this->speed>3){
            this->setSpeed(this->speed-1);
            this->jump(-100000);
        }else if(this->speed<-3){
            this->setSpeed(this->speed+1);
            this->jump(-100000);
        }
        return;
    }
    this->speed = rotspeed*(r+ height);
}

void CFPrince::updateBody(){
    b2Vec2 pos = this->getBody()->GetPosition();
    int energy = this->context->getSpaceContext()->getEnergy();
    if(energy <=0){//但energy大于0，不固定作用地心引力
        b2Vec2 F = b2Vec2(0, -1000);
        this->getBody()->ApplyForce(F,pos);
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    float x = size.width/2;
    float planetTop = this->context->getCurrentLevel()->getPlanetTop();
    float y = planetTop + pos.y* PTM_RATIO;
    float topline = this->getTop();
    this->zoom = y<topline?1:(topline/y<0.2?0.2:topline/y);
    this->setScale(this->zoom);
    y = y>topline?topline:y;
    this->setPosition(CCPointMake( x,  y));
    this->setRotation(CC_RADIANS_TO_DEGREES(this->getBody()->GetAngle()));
}

void CFPrince::updateNode(){
    CFUtil::updateBody(this->getNode(), this, this->context);
}

//magic: 0:run,1:attack,2:dead,3:jump,4:walk,5:down
void CFPrince::updateArmature(){
    //切换方向
    if(this->speed > 0){
        this->armature->setRotationY(0);
    }else if(this->speed<0){
        this->armature->setRotationY(180);
    }
    if(this->isFlying()){
        b2Vec2 pos = this->getBody()->GetPosition();
        if(pos.y<lastpos.y){
            //切换飞行状态和行走状态
            this->playByIndex(5);
            return;
        }else{
            this->playByIndex(3);
            return;
        }
    }
    //切换走动状态和跑动状态
    if(this->isRunning()){
        this->playByIndex(0);
    }else{
        this->playByIndex(4);
    }
}

void CFPrince::updateEnergy(int frame){
    int energy = this->context->getSpaceContext()->getEnergy();
    if(this->isFlying()){
        int energy = this->context->getSpaceContext()->getEnergy();
        b2Vec2 pos = this->getBody()->GetPosition();
        if(pos.y>lastpos.y){
            if(frame%3==0){
                this->context->getSpaceContext()->recordEnergy(-2);
            }
        }else{
            this->context->getSpaceContext()->setEnergy(0);
        }
        if(energy<=0){
            //force
            this->jump(-10000);
            return;
        }
        return;
    }else{
        if(energy<=0){
            //int speed = this->getSpeed();
            //this->setSpeed(speed>0?20:-20);
        }else{
            if(this->isRunning()){
                if(frame%30==0){
                    this->context->getSpaceContext()->recordEnergy(-1);
                }
            }
        }
    }
}

void CFPrince::updateStatus(){
    if(this->status >= 3){
        long current;
        time(&current);
        long during = current - this->starttime;
        if(during > awardseconds){
            this->resetAward();
        }
        return;
    }
    if(spadeVisible){
        this->status = 1;
        return;
    }
    if(swordVisible){
        this->status = 2;
        return;
    }
    this->status = 0;
}

void CFPrince::updateTargetHeight(){
    if(this->targetHeight <=0){
        return;
    }
    if(this->getHeight()<this->targetHeight){
        this->jump(7000000);
    }else{
        this->jump(-7000000);
    }
}

void CFPrince::onGameTaskAward(int awardtype, const char* awardname, int seconds){
    if(awardtype+3 <= this->status){//如果status比现有status低，那么不替代
        return;
    }
    //如果status与当前task高，那么不替代
    CFGameLevel* level = this->context->getCurrentLevel();
    int taskstatus = level->getCurrentTaskStatus();
    if(awardtype + 3 > taskstatus){
        return;
    }
    this->status = awardtype+3;
    //加载task图标
    if(this->award != NULL){
        this->award->removeFromParentAndCleanup(true);
    }
    this->award = CCNode::create();
    int princeWidth = this->armature->getContentSize().width;
    int princeHeight = this->armature->getContentSize().height;
    award->setPosition(ccp(princeWidth/2, princeHeight*1.2));
    this->addChild(award);
    CCSprite* bg = CCSprite::create("task-bg.png");
    award->addChild(bg);
    CCString* name = CCString::createWithFormat("%s.png", awardname);
    CCSprite* sprite = CCSprite::create(name->getCString());
    award->addChild(sprite);
    
    //加载动画
    CCParticleSystemQuad *emitter1 = CCParticleSystemQuad::create("update.plist");
    emitter1->setBlendAdditive(true);//是否混合
    emitter1->setPosition(ccp(0,0));
    emitter1->setAutoRemoveOnFinish(true);
    this->addChild(emitter1);
    this->status = awardtype + 3;//magic:0为走动，跑动，1为铁铲，2为剑
    time(&this->starttime);
    this->awardseconds = seconds;
    this->context->playEffect("flying.mp3", false);
    //自动导航到pet处
    this->context->getSpaceContext()->setEnergy(0);
    this->setHeight(1);
    int speed = this->getSpeed();
    if(speed>0){
        this->setSpeed(100);
    }else{
        this->setSpeed(-100);
    }
    this->isready = false;
}

void CFPrince::onGameTaskStory(cocos2d::CCDictionary *task, int taskindex){
    this->resetAward();
    this->setSpeed(0);
    this->isready = false;
}

void CFPrince::onGameTaskStart(cocos2d::CCDictionary *task, int taskindex){
    this->resetAward();
    this->setSpeed(0);
    this->isready = true;
    int princeStatus = CFCocosUtil::getIntFromDict(task, "prince", 0);
    switch (princeStatus) {
        case 0:
            this->setSpadeVisible(false);
            this->setSwordVisible(false);
            break;
        case 1:
            this->setSpadeVisible(true);
            this->setSwordVisible(false);
            break;
        case 2:
            this->setSpadeVisible(false);
            this->setSwordVisible(true);
            break;
    }
    this->context->playEffect("taskstart.mp3", false);
}

void CFPrince::onGameTaskComplete(cocos2d::CCDictionary *task, int taskindex){
    this->isready = true;
    this->setSpeed(this->getSpeed()>0?-3:3);
    this->setHeight(0);
    this->resetAward();
}

void CFPrince::resetAward(){
    this->awardseconds = 0;
    this->starttime = -1;
    this->status = 0;
    if(this->award != NULL){
        this->award->removeFromParentAndCleanup(true);
        this->award = NULL;
    }
}

float CFPrince::getSpeed(){
    return this->speed;
}


void CFPrince::setSpeed(float speed){
    if(!this->isready){
        return;
    }
    this->rotspeed = speed/(r+this->height);
}

void CFPrince::speedRight(){
    if(!this->isready){
        return;
    }
    if(this->rotspeed < 0){
        this->rotspeed = -this->rotspeed/2;
    }else{
        if(this->rotspeed < maxrotspeed){
            this->rotspeed+=maxrotspeed/3;
        }
    }
}

void CFPrince::speedLeft(){
    if(!this->isready){
        return;
    }
    if(this->rotspeed <= 0){
        if(this->rotspeed > -maxrotspeed){
            this->rotspeed-=maxrotspeed/3;
        }
    }else{
        this->rotspeed = -this->rotspeed/2;
    }
}

void CFPrince::jump(float force){
    if(!this->isready){
        return;
    }
    b2Vec2 F;
    F.x = 0;
    F.y = force;
    b2Vec2 pos = this->getBody()->GetPosition();
    this->getBody()->ApplyForce(F,pos);
    this->updateArmature();
    if(force >0){
        //this->context->getSpaceContext()->addEnergy(-force);
    }
}

bool CFPrince::isFlying(){
    return this->getHeight() > this->armature->getContentSize().height;
}

bool CFPrince::isRunning(){
    return abs(this->speed)>=RUNSPEED;
}

void CFPrince::playByIndex(int index){
    if(index == animationIndex){
        return;
    }
    this->armature->getAnimation()->playWithIndex(index);
    animationIndex = index;
}

float CFPrince::getHeight(){
    return this->getBody()->GetPosition().y*PTM_RATIO;
}

void CFPrince::setHeight(float height){
    this->targetHeight = height;
}

float CFPrince::getWeight(){
    return this->context->getCurrentLevel()->getHeroWeight();
}

float CFPrince::getZoom(){
    return this->zoom;
}

float CFPrince::getTop(){
    return this->context->getCurrentLevel()->getHeroTop();
}

void CFPrince::onBeganTouch(time_t beginTouchTime, cocos2d::CCPoint beginTouchLocation){
}

void CFPrince::onEndTouch(time_t beginTouchTime, CCPoint beginTouchLocation, time_t endTouchTime, cocos2d::CCPoint endTouchLocation){
        if(abs(beginTouchLocation.x-endTouchLocation.x)<20 && abs(beginTouchLocation.y-endTouchLocation.y)<20){
            CCSize size = CCDirector::sharedDirector()->getWinSize();
            if(endTouchLocation.x>size.width/2){
                this->speedRight();
            }else{
                this->speedLeft();
            }
        }else{
            float speed = beginTouchLocation.x - endTouchLocation.x;
            if(speed>0){
                this->speedLeft();
            }else{
                this->speedRight();
            }
            float jump = beginTouchLocation.y - endTouchLocation.y;
            if(this->isFlying()&&this->context->getSpaceContext()->getEnergy()<=0){
                return;
            }
            this->jump(jump*300);
        }
}

void CFPrince::onConflict(b2Contact *contact, CFNode *other){
    if(!this->context->isGameStarted()){
        return;
    }
    if(other->getType() == TYPE_CLOUD){
    }
    if(other->getType() == TYPE_ENEMY){
    }
    if(other->getType() == TYPE_GIFT){
    }
}

void CFPrince::onEndConflict(b2Contact *contact, CFNode *other){
}

int CFPrince::getStatus(){
    return this->status;
}

b2Body* CFPrince::getBody(){
    if(this->body != NULL){
        return this->body;
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(size.width/(2*PTM_RATIO), size.height/(2*PTM_RATIO));
    bodyDef.fixedRotation = true;
    //bodyDef.userData = this;
    bodyDef.linearDamping=0.0f;
    bodyDef.angularDamping=0.0f;
    this->body = context->getSpaceContext()->getWorld()->CreateBody(&bodyDef);
    gbox2d::GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(this->body, "prince");//把生成的刚体和形状绑在一起
    this->body->SetTransform(b2Vec2(size.width/(2*PTM_RATIO),size.height/(2*PTM_RATIO)), 0);
    this->setAnchorPoint(gbox2d::GB2ShapeCache::sharedGB2ShapeCache()->anchorPointForShape("prince"));//设置锚点
    this->lastpos = this->body->GetPosition();
    return this->body;
}

CCSize CFPrince::getContentSize(){
    if(this->armature == NULL){
        return CFNode::getContentSize();
    }
    return this->armature->getContentSize();
}

b2Body* CFPrince::getNode(){
    if(this->node == NULL){
        //用于碰撞检测的body
        this->node = CFUtil::createBody("princenode", this, this->context->getSpaceContext()->getWorld());
    }
    return this->node;
}

bool CFPrince::isReady(){
    return this->isready;
}

void CFPrince::setSpadeVisible(bool visible){
    spadeVisible = visible;
    CCBone* spade = this->armature->getBone("spade");
    int index = spade->getDisplayManager()->getCurrentDisplayIndex();
    spade->removeDisplay(index);
    if(visible){
        spade->addDisplay(CCSkin::createWithSpriteFrameName("spade.png"), index);
        spade->changeDisplayWithIndex(index, true);
    }else{
        CCSkin* skin = NULL;
        spade->addDisplay(skin, index);
        spade->changeDisplayWithIndex(index, true);
    }
}

void CFPrince::setSwordVisible(bool visible){
    swordVisible = visible;
    CCBone* sword = this->armature->getBone("sword");
    int index = sword->getDisplayManager()->getCurrentDisplayIndex();
    sword->removeDisplay(index);
    if(visible){
        sword->addDisplay(CCSkin::createWithSpriteFrameName("sward.png"), index);
        sword->changeDisplayWithIndex(index, true);
    }else{
        CCSkin* skin = NULL;
        sword->addDisplay(skin, index);
        sword->changeDisplayWithIndex(index, true);
    }
}
