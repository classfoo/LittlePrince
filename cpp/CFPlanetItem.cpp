#include "CFPlanetItem.h"

CFPlanetItem::CFPlanetItem():product(NULL),index(0){
}

CFPlanetItem::~CFPlanetItem(){
}

CFPlanetItem* CFPlanetItem::create(int index, const char* name, const char* night, float initHeight,float initRot, float initSpeed, float z, const char* product, CFGameContext* context){
    CFPlanetItem* item = new CFPlanetItem();
    item->index = index;
    item->height = initHeight;
    item->rot = initRot;
    item->speed = initSpeed;
    item->context = context;
    item->z = z;
    item->product = product;
    item->name = name;
    CCString* textureDay = CCString::createWithFormat("%s.png", name);
    item->textureDay = CCTextureCache::sharedTextureCache()->addImage(textureDay->getCString());
    if(night != NULL){
        CCString* textureNight = CCString::createWithFormat("%s.png", night);
        item->textureNight = CCTextureCache::sharedTextureCache()->addImage(textureNight->getCString());
    }else{
        item->textureNight = CCTextureCache::sharedTextureCache()->addImage("transparent.png");
    }
    item->size =CCSize(item->textureDay->getPixelsWide(), item->textureDay->getPixelsHigh());
    item->init();
    item->autorelease();
    return item;
}

bool CFPlanetItem::init(){
    bool ret = false;
    do{
        CFNpc::init();
        ret = true;
    }while (0);
    return ret;
}

void CFPlanetItem::update(float dt){
    CFNpc::update(dt);
}

void CFPlanetItem::onCircle(int circle){
    this->generateCloud();
    if(this->context->isGameStarted()){
        this->showWords();
    }

}

void CFPlanetItem::onConflict(b2Contact *contact, CFNode *other){
    if(!this->context->isGameStarted()){
        return;
    }
    if(other->getType() != TYPE_HERO){
        return;
    }
    CCString* music = CCString::createWithFormat("%i.mp3", rand()%15+1);
    this->context->playEffect(music->getCString(), false);
    this->generateCloud();
    this->showWords();
}

void CFPlanetItem::showWords(){
    if(this->isShowingInfo()){
        return;
    }
    CCDictionary* words = this->context->getCurrentLevel()->checkPlanetItemWords(this->index, this->context);
    if(words == NULL){
        return;
    }
    const char* princeWords = CFCocosUtil::getStringFromDict(words, "prince", NULL);
    if(princeWords != NULL){
        CFNode* prince = this->context->getSpaceContext()->getPrince();
        const ccColor3B color = ccc3(249, 240, 8);
        prince->showInfo(princeWords, "sniglet20y.fnt", 25, color, 384, 200, this, SEL_CallFunc(&CFPlanetItem::endShowWords));
        return;
    }
    const char* petWords = CFCocosUtil::getStringFromDict(words, "item", NULL);
    if(petWords != NULL){
        const ccColor3B color = ccc3(234, 82, 35);
        this->showInfo(petWords, "Sniglet32.fnt", 32, color, 384, this->getContentSize().height,this, SEL_CallFunc(&CFPlanetItem::endShowWords));
    }
}

void CFPlanetItem::endShowWords(){
    this->showWords();
}

void CFPlanetItem::onEndConflict(b2Contact *contact, CFNode *other){
}

void CFPlanetItem::generateCloud(){
    if(!this->context->isGameStarted()){
        return;
    }
    if(this->product == NULL){
        return;
    }
    this->context->getSpaceContext()->addCloud(this->product, this->getHeight()+this->getContentSize().height, this->getRot());
}

b2Body* CFPlanetItem::getBody(){
    if(this->body != NULL){
        return this->body;
    }
    this->body = CFUtil::createBody(this->name, this, context->getSpaceContext()->getWorld());
    return this->body;
}

CCSize CFPlanetItem::getContentSize(){
    return this->size;
}
