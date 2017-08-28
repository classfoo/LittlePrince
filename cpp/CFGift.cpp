#include "CFGift.h"
CFGift::CFGift():sprite(NULL){
    this->type = TYPE_GIFT;
}

CFGift::~CFGift(){
}

CFGift* CFGift::create(int type, int energy, int action, const char* name, float initHeight, float initRot, float initSpeed, CFGameContext *context){
    CFGift* gift = new CFGift();
    gift->height = initHeight;
    gift->rot = initRot;
    gift->speed = initSpeed;
    gift->context = context;
    gift->name = name;
    gift->type = type;
    gift->energy = energy;
    gift->action = action;
    gift->init();
    gift->setScale(1/300.0f);
    gift->autorelease();
    return gift;
}

bool CFGift::init(){
    bool ret = false;
    do{
        if(!CFNpc::init()){
            return ret;
        }
        if(this->action == 0){
            this->sprite = this->initCommonSprite();
        }
        else if(this->action == 1){
            this->sprite = this->initCommonSprite();
            CCRotateBy* rotate = CCRotateBy::create(1, 360,360);
            CCRepeatForever* action = CCRepeatForever::create(rotate);
            sprite->runAction(action);
            ret = true;
        }else if(this->action == 2){
            this->sprite = this->initBallonSprite("ballon-yellow.png");
        }else if(this->action == 3){
            this->sprite = this->initBallonSprite("ballon-red.png");
        }else if(this->action == 4){
            this->sprite = this->initBallonSprite("ballon-many.png");
        }else if(this->action == 5){
            this->sprite = this->initAnimationSprite();
        }
        ret = true;
    }while(0);
    return ret;
}

CCNode* CFGift::initCommonSprite(){
    CCString* filename = CCString::createWithFormat("%s.png", name);
    CCSprite* sprite = CCSprite::create(filename->getCString());
    this->size = sprite->getContentSize();
    this->addChild(sprite);
    return sprite;
}

CCNode* CFGift::initBallonSprite(const char* ballonname){
    CCSprite* ballon = CCSprite::create(ballonname);
    this->addChild(ballon);
    this->size = ballon->getContentSize();
    CCSprite* bg = CCSprite::create("task-bg.png");
    bg->setPosition(ccp(this->size.width/2, 0));
    ballon->addChild(bg);
    CCString* filename = CCString::createWithFormat("%s.png", name);
    CCSprite* gift = CCSprite::create(filename->getCString());
    gift->setPosition(ccp(bg->getContentSize().width/2, bg->getContentSize().height/2));
    bg->addChild(gift);
    return ballon;
}

CCNode* CFGift::initAnimationSprite(){
    CCString* name0 = CCString::createWithFormat("%s0.png", this->name);
    CCString* name1 = CCString::createWithFormat("%s1.png", this->name);
    CCString* name2 = CCString::createWithFormat("%s2.png", this->name);
    CFAnimate* animate = CFAnimate::create(name0->getCString(), name1->getCString(),name2->getCString(), 0.2f);
    this->addChild(animate);
    return animate;
}

void CFGift::update(float dt){
    this->updateByAction0(dt);
    CFNpc::update(dt);
    if(this->speed > 0){
        this->sprite->setRotationY(0);
    }else{
        this->sprite->setRotationY(180);
    }
}

void CFGift::updateByAction0(float dt){
    float bottom = this->getBottomHeight();
    float top = this->getTopHeight();
    if(this->height<bottom){
        this->height += 20*CCRANDOM_0_1();
    }else{
        if(this->context->isGameStarted()){
            if(this->height<top){
                this->height+=CCRANDOM_0_1();
            }else if(this->height>=top){
                this->removeFromParentAndCleanup(true);
            }
        }
    }
    //按照300为单位进行scale，便于看清楚飞起来的东西
    if(this->height<300){
        this->sprite->setScale(this->height/300);
    }else{
        this->sprite->setScale(1);
    }

}

void CFGift::updateByAction1(float dt){
    float bottom = this->getBottomHeight();
    float top = this->getTopHeight();
    if(this->height<bottom){
        this->height += 20*CCRANDOM_0_1();
        this->setScale(this->height/bottom);
    }else{
        if(this->context->isGameStarted()){
            if(this->height<top){
                this->height+=CCRANDOM_0_1();
            }else if(this->height>=top){
                this->removeFromParentAndCleanup(true);
            }
        }
    }
}

void CFGift::updateByAction2(float dt){
    float bottom = this->getBottomHeight();
    float top = this->getTopHeight();
    if(this->height<bottom){
        this->height += 10*CCRANDOM_0_1();
        this->setScale(this->height/bottom);
    }else{
        if(this->context->isGameStarted()){
            if(this->height<top){
                this->height+=1*CCRANDOM_0_1();
            }else if(this->height>=top){
                this->removeFromParentAndCleanup(true);
            }
        }
    }
}

void CFGift::updateByAction3(float dt){
    float bottom = this->getBottomHeight();
    float top = this->getTopHeight();
    if(this->height<bottom){
        this->height += 10;
        this->setScale(this->height/bottom);
    }else{
        if(this->context->isGameStarted()){
            if(this->height<top){
                this->height+=1*CCRANDOM_0_1();
            }else if(this->height>=top){
                this->removeFromParentAndCleanup(true);
            }
        }
    }
}

void CFGift::updateByAction4(float dt){
    float bottom = this->getBottomHeight();
    float top = this->getTopHeight();
    if(this->height<bottom){
        this->height += 10*CCRANDOM_0_1();
        this->setScale(this->height/bottom);
    }else{
        if(this->context->isGameStarted()){
            if(this->height<top){
                this->height+=1*CCRANDOM_0_1();
            }else if(this->height>=top){
                this->removeFromParentAndCleanup(true);
            }
        }
    }
}

void CFGift::updateByAction5(float dt){
    this->updateByAction2(dt);
}

void CFGift::onCircle(int circle){
    this->speed = (rand()%20)*CCRANDOM_MINUS1_1();
}

void CFGift::onConflict(b2Contact *contact, CFNode *other){
    if(!this->context->isGameStarted()){
        return;
    }
    if(other->getType() == TYPE_HERO && !conflicted){
        if(this->height<=200){
            return;
        }
        CFPrince* prince = (CFPrince*) other;
        if(!prince->isReady()){
            return;
        }
        this->context->getSpaceContext()->recordGift(this->type);
        CFParticle* par = CFParticle::create("ring.plist", this->getHeight(), this->getRot(), this->getLineSpeed(), this->context);
        this->context->addChild(par);
        this->removeFromParentAndCleanup(true);
        this->context->getSpaceContext()->recordEnergy(this->energy);
        this->context->getSpaceContext()->jump((this->type+1)*500000);
        
        CCParticleSystemQuad *emitter1 = CCParticleSystemQuad::create("update.plist");
        emitter1->setBlendAdditive(true);//是否混合
        emitter1->setPosition(ccp(0,0));
        emitter1->setAutoRemoveOnFinish(true);
        emitter1->setRotation(prince->getSpeed()>0?5:-5);
        prince->addChild(emitter1);
        CCString* music = CCString::createWithFormat("%i.mp3", rand()%15+1);
        this->context->playEffect(music->getCString(), false);
        this->context->playEffect("jump.mp3", false);
        conflicted=true;
    }
    if(other->getType() == TYPE_GIFT){
        CFGift* othergift = (CFGift*)other;
        float linespeed = this->getLineSpeed();
        this->setLineSpeed(-othergift->getLineSpeed());
        othergift->setLineSpeed(-linespeed);
    }
    this->speed = (rand()%20)*CCRANDOM_MINUS1_1();
}

void CFGift::onEndConflict(b2Contact *contact, CFNode *other){
}

b2Body* CFGift::getBody(){
    if(this->body != NULL){
        return this->body;
    }
    this->body = CFUtil::createBody(this->name, this, this->context->getSpaceContext()->getWorld());
    return this->body;
}

CCSize CFGift::getContentSize(){
    return this->size;
}

float CFGift::getBottomHeight(){
    return 200+100*(this->type+1);
}

float CFGift::getTopHeight(){
    return 500*(this->type + 1);
}