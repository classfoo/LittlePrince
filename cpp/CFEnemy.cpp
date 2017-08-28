#include "CFEnemy.h"

CFEnemy::CFEnemy(void){
    this->type = TYPE_ENEMY;
}

CFEnemy::~CFEnemy(void){
}

CFEnemy* CFEnemy::create(const char* filename, int enemyType, float initHeight,float initRot, float initSpeed, CFGameContext* context){
    CFEnemy* pNpc = new CFEnemy();
    pNpc->height = initHeight;
    pNpc->rot = initRot;// + planet->getRot();
    pNpc->speed = initSpeed;
    pNpc->initSpeed = initSpeed;
    pNpc->context = context;
    pNpc->enemyType = enemyType;
    CCString* name = CCString::createWithFormat("%s.png", filename);
    pNpc->textureDay = CCTextureCache::sharedTextureCache()->addImage(name->getCString());
    pNpc->size =CCSize(pNpc->textureDay->getPixelsWide(), pNpc->textureDay->getPixelsHigh());
    pNpc->init();
    pNpc->autorelease();
    return pNpc;
}

bool CFEnemy::init(){
    bool ret = false;
    do{
        if(!CFNpc::init()){
            return false;
        }
        this->maxEnemyStage = this->context->getCurrentLevel()->getEnemyStageCount(this->enemyType);
        ret = true;
    }while(0);
    return ret;
}

void CFEnemy::update(float dt){
    CFNpc::update(dt);
    if(this->height <= 0){//接触到地面
        this->height = 0;
        this->speed = 0;
        this->getBody()->SetActive(true);
        if(this->getEnemyStage() == 0){
            this->setVisible(false);
            this->onCircle(1);
        }else{
            this->setVisible(true);
        }
    }else{
        this->height-=10;
        if(this->height <=0){
            this->getBody()->SetActive(true);
            if(this->getEnemyStage() == 0){
                this->setVisible(false);
                this->onCircle(1);
            }else{
                this->setVisible(true);
            }
        }
    }
    
}

void CFEnemy::onCircle(int circle){
    if(!this->context->isGameStarted()){
        return;
    }
    if(this->height>0){
        return;
    }
    if(circle >= maxEnemyStage){
        return;
    }
    this->enemyStage = circle;
    const char* name = this->context->getCurrentLevel()->getEnemyName(this->enemyType, this->enemyStage);
    if(name == NULL){
        return;
    }
    //reset texture
    CCString* textureName = CCString::createWithFormat("%s.png", name);
    this->textureDay = CCTextureCache::sharedTextureCache()->addImage(textureName->getCString());
    this->textureNight = CCTextureCache::sharedTextureCache()->addImage("transparent.png");
    this->size =CCSize(this->textureDay->getPixelsWide(), this->textureDay->getPixelsHigh());
    //reset body
    if(this->body != NULL){
        this->context->getSpaceContext()->getWorld()->DestroyBody(this->body);
        this->body = CFUtil::createBody(name, this, context->getSpaceContext()->getWorld());
    }
}

void CFEnemy::onConflict(b2Contact *contact, CFNode *other){
    if(!this->context->isGameStarted()){
        return;
    }
    if(other->getType() == TYPE_HERO && !conflicted){
        CFGameLevel* level = this->context->getCurrentLevel();
        CFPrince* prince = (CFPrince*) other;
        if(!prince->isReady()){
            return;
        }
        int pstatus = prince->getStatus();
        if(level->getEnemyCanDestroy(this->enemyType, this->enemyStage, pstatus)){
            int gifttype = level->getEnemyGiftType(this->enemyType, this->enemyStage);
            this->context->getSpaceContext()->addGift(gifttype, this->height, this->rot, this->initSpeed);
            this->removeFromParentAndCleanup(true);
            level->recordEnemyCount(-1);
            this->context->playEffect("footstep.mp3", false);
            conflicted=true;
        }
        return;
    }
    if(other->getType() == TYPE_ENEMY){
        CFEnemy* enemy = (CFEnemy*) other;
        if(this->enemyType != enemy->enemyType){
            return;
        }
        if(this->enemyStage>enemy->enemyStage){
            enemy->removeFromParentAndCleanup(true);
        }else{
            this->removeFromParentAndCleanup(true);
        }
        CFGameLevel* level = this->context->getCurrentLevel();
        level->recordEnemyCount(-1);
        return;
    }
    if(other->getType() == TYPE_PET){
        this->removeFromParentAndCleanup(true);
        CFGameLevel* level = this->context->getCurrentLevel();
        level->recordEnemyCount(-1);
        return;
    }
}

void CFEnemy::onEndConflict(b2Contact *contact, CFNode *other){

}


int CFEnemy::getEnemyStage(){
    return this->enemyStage;
}

b2Body* CFEnemy::getBody(){
    if(this->body != NULL){
        return this->body;
    }
    const char* name = this->context->getCurrentLevel()->getEnemyName(this->enemyType, 0);
    this->body = CFUtil::createBody(name, this, context->getSpaceContext()->getWorld());
    return this->body;
}

CCSize CFEnemy::getContentSize(){
    return this->size;
}