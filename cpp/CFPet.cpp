#include "CFPet.h"

CFPet::CFPet():icon(NULL),tips(NULL),tipsboard(NULL),product(NULL){
    this->type = TYPE_PET;
}

CFPet::~CFPet(){
}

CFPet* CFPet::create(CFGameContext *context){
    CFPet* pet = new CFPet();
    CFGameLevel* level = context->getCurrentLevel();
    pet->name = level->getPetName();
    pet->height = level->getPetInitHeight();
    pet->rot = level->getPetInitRot();
    pet->speed = level->getPetInitSpeed();
    pet->product = level->getPetProduct();
    pet->context = context;
    pet->init();
    pet->autorelease();
    return pet;
}

bool CFPet::init(){
    bool ret = false;
    do{
        if(!CFNpc::init()){
            return ret;
        }
        this->initSprite(this->name);
        ret = true;
    }while(0);
    return ret;
}

void CFPet::initSprite(const char* name){
    CCString* textureDay = CCString::createWithFormat("%s.png", name);
    this->textureDay = CCTextureCache::sharedTextureCache()->addImage(textureDay->getCString());
    this->textureNight = CCTextureCache::sharedTextureCache()->addImage("transparent.png");
    this->size =CCSize(this->textureDay->getPixelsWide(), this->textureDay->getPixelsHigh());
}

void CFPet::update(float dt){
    CFNpc::update(dt);
}

void CFPet::onCircle(int circle){
    if(!this->context->isGameStarted()){
        return;
    }
    CFPet::generateCloud();
    //this->showWords();
}

void CFPet::onConflict(b2Contact *contact, CFNode *other){
    if(!this->context->isGameStarted()){
        return;
    }
    if(TYPE_HERO != other->getType()){
        return;
    }
    CCString* music = CCString::createWithFormat("%i.mp3", rand()%15+1);
    this->context->playEffect(music->getCString(), false);
    this->generateCloud();
    CFPrince* prince = (CFPrince*) other;
    int status = prince->getStatus();
    if(this->context->getCurrentLevel()->checkTaskComplete(status, this->context)){
        return;
    }
    this->showWords();
    this->context->getSpaceContext()->showStories();
}

void CFPet::onEndConflict(b2Contact *contact, CFNode *other){
    
}

void CFPet::onGameTaskStart(cocos2d::CCDictionary *task, int taskindex){
    const char* name = CFCocosUtil::getStringFromDict(task, "icon", NULL);
    if(name == NULL){
        return;
    }
    if(this->icon != NULL){
        this->icon->stopAllActions();
        this->icon->removeFromParentAndCleanup(true);
    }
    this->icon = CCNode::create();
    this->icon->setPosition(ccp(0, this->getContentSize().height+100));
    this->addChild(this->icon);
    CCSprite* bg = CCSprite::create("task-bg.png");
    this->icon->addChild(bg);
    CCSprite* status = CCSprite::create(CCString::createWithFormat("%s.png", name)->getCString());
    status->setColor(ccc3(100, 100, 100));
    this->icon->addChild(status);
    this->icon->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(0.5, 1.5),CCScaleTo::create(0.5, 1),NULL)));
}

void CFPet::onGameTaskOngoing(cocos2d::CCDictionary *task, int taskindex){
    CCArray* tips = (CCArray*)task->objectForKey("tips");
    if(tips == NULL){
        return;
    }
    this->context->getSpaceContext()->showTips(tips);
}

void CFPet::onGameTaskComplete(cocos2d::CCDictionary *task, int taskindex){
    if(this->icon == NULL){
        return;
    }
    CCParticleSystemQuad *emitter1 = CCParticleSystemQuad::create("ring.plist");
    emitter1->setBlendAdditive(true);//是否混合
    emitter1->setPosition(this->icon->getPosition());
    emitter1->setAutoRemoveOnFinish(true);
    this->addChild(emitter1);
    this->icon->stopAllActions();
    //this->icon->runAction(CCMoveTo::create(3, ccp(this->icon->getPosition().x, this->icon->getPosition().y+200)));
    this->icon->removeFromParentAndCleanup(true);
    this->icon = NULL;
    
    //根据task中的属性，决定是否需要更新显示界面
    const char* newpetname = CFCocosUtil::getStringFromDict(task, "pet", NULL);
    if(newpetname != NULL){
        this->initSprite(newpetname);
    }
    this->context->playEffect("clapping.mp3", false);
}

void CFPet::playAtIndex(int index){
    if(this->armature == NULL){
        return;
    }
    this->armature->getAnimation()->playWithIndex(index);
}

void CFPet::showWords(){
    if(this->isShowingInfo()){
        return;
    }
    CFPrince* prince = (CFPrince*)this->context->getSpaceContext()->getPrince();
    if(!prince->isReady()){
        return;
    }
    CCDictionary* words = this->context->getCurrentLevel()->checkPetWords(this->context);
    if(words == NULL){
        return;
    }
    const char* princeWords = CFCocosUtil::getStringFromDict(words, "prince", NULL);
    if(princeWords != NULL){
        CFNode* prince = this->context->getSpaceContext()->getPrince();
        const ccColor3B color = ccc3(249, 240, 8);
        prince->showInfo(princeWords, "sniglet20y.fnt", 25, color, 384, 200, this, SEL_CallFunc(&CFPet::endShowWords));
    }
    const char* petWords = CFCocosUtil::getStringFromDict(words, "pet", NULL);
    if(petWords != NULL){
        const ccColor3B color = ccc3(234, 82, 35);
        this->showInfo(petWords, "Sniglet32.fnt", 32, color, 384, this->getContentSize().height, this, SEL_CallFunc(&CFPet::endShowWords));
    }
}

void CFPet::endShowWords(){
    this->showWords();
}

void CFPet::generateCloud(){
    if(!this->context->isGameStarted()){
        return;
    }
    if(this->product == NULL){
        return;
    }
    this->context->getSpaceContext()->addCloud(this->product, this->getHeight()+this->getContentSize().height, this->getRot());
}

b2Body* CFPet::getBody(){
    if(this->body != NULL){
        return this->body;
    }
    this->body = CFUtil::createBody(this->name, this, this->context->getSpaceContext()->getWorld());
    return this->body;
}

CCSize CFPet::getContentSize(){
    return this->size;
}