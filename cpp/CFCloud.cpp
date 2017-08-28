#include "CFCloud.h"

CFCloud::CFCloud():destroy(false),name(NULL),sprite(NULL),armature(NULL){
    this->type = TYPE_CLOUD;
}

CFCloud::~CFCloud(){
}

CFCloud* CFCloud::create(const char* name, float initHeight, float initRot, float initSpeed, CFGameContext* context){
    CFCloud* cloud = new CFCloud();
    cloud->name = name;
    cloud->height = initHeight;
    cloud->rot = initRot;
    cloud->speed = initSpeed;
    cloud->context = context;
    cloud->autorelease();
    cloud->sprite = CCSprite::create(CCString::createWithFormat("%s.png", name)->getCString());
    cloud->addChild(cloud->sprite);
    cloud->init();
    return cloud;
}

bool CFCloud::init(){
    bool ret = false;
    do{
        if(!CFNpc::init()){
            return ret;
        }
        ret = true;
    }while(0);
    return ret;
}

void CFCloud::update(float dt){
    CFNpc::update(dt);
    float height = this->getHeight();
    if(height<300){
        this->setHeight(height+20);
        float scale = this->getScale();
        this->setScale(scale*height/1000);
    }else if(height<1000){
        this->setHeight(height+10);
        float scale = this->getScale();
        this->setScale(scale*height/1000);
    }
}


void CFCloud::dropEnemy(){
    if(this->destroy){
        return;
    }
    CFGameLevel* level = this->context->getCurrentLevel();
    if(!level->checkEnemyCountLimit()){
        return;
    }
    int typecount = level->getEnemyTypeCount();
    if(typecount == 0){
        return;
    }
    int typeindex = 0;
    for(int i = 0;i < typecount;i++){
        if(CCRANDOM_0_1() > 0.6){
            typeindex = i;
            break;
        }
        typeindex = i;
    }
    const char* enemyName = level->getEnemyName(typeindex, 0);
    this->context->getSpaceContext()->addEnemy(enemyName, typeindex, this->height, this->rot, this->speed);
    level->recordEnemyCount(1);
}

void CFCloud::generatePet(){
    if(this->destroy){
        return;
    }
}

void CFCloud::onCircle(int circle){
    if(!this->context->isGameStarted()){
        return;
    }
    if(circle == 5){
        this->dropEnemy();
        this->destroy = true;
        this->removeFromParentAndCleanup(true);
        return;
    }
    this->sprite->setColor(ccc3((GLubyte)(255-circle*100),(GLubyte)(255-circle*100),(GLubyte)(255-circle*100)));
    this->dropEnemy();
}

void CFCloud::onConflict(b2Contact *contact, CFNode *other){
    if(!this->context->isGameStarted()){
        return;
    }
    if(this->height<=500){
        return;
    }
    if(other->getType() == TYPE_HERO){
        this->dropEnemy();
        this->context->getSpaceContext()->jump(5000000);
        CCString* music = CCString::createWithFormat("%i.mp3", rand()%15+1);
        this->context->playEffect(music->getCString(), false);
        this->context->playEffect("thunder.mp3",false);
    }
}

void CFCloud::onEndConflict(b2Contact *contact, CFNode *other){

}

CCSize CFCloud::getContentSize(){
    return this->sprite->getContentSize();
}

b2Body* CFCloud::getBody(){
    if(this->body != NULL){
        return this->body;
    }
    this->body = CFUtil::createBody(this->name, this, this->context->getSpaceContext()->getWorld());
    return this->body;
}
