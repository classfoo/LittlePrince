#include "CFParticle.h"

CFParticle::CFParticle(){
    this->type = TYPE_GIFT;
}

CFParticle::~CFParticle(){
}

CFParticle* CFParticle::create(string name, float initHeight, float initRot, float initSpeed, CFGameContext *context){
    CFParticle* par = new CFParticle();
    par->height = initHeight;
    par->rot = initRot;
    par->speed = initSpeed;
    CCParticleSystemQuad *emitter1 = CCParticleSystemQuad::create(name.c_str());
    emitter1->setBlendAdditive(true);//是否混合
    emitter1->setPosition(ccp(0,0));
    emitter1->setAutoRemoveOnFinish(true);
    par->addChild(emitter1);
    par->context = context;
    par->init();
    par->autorelease();
    return par;
}

bool CFParticle::init(){
    bool ret = false;
    do{
        if(!CFNpc::init()){
            return ret;
        }
        ret = true;
    }while(0);
    return ret;
}

void CFParticle::update(float dt){
    CFNpc::update(dt);
    if(this->getChildrenCount() == 0){
        this->removeFromParentAndCleanup(true);
    }
}

b2Body* CFParticle::getBody(){
    return NULL;
}
