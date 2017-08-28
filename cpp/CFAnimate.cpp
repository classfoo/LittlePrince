#include "CFAnimate.h"

CFAnimate::CFAnimate(){

}

CFAnimate::~CFAnimate(){

}

CFAnimate* CFAnimate::create(const char *frame0, const char* frame1, const char* frame2, float delay){
    CFAnimate* animate = new CFAnimate();
    animate->frame0 = frame0;
    animate->frame1 = frame1;
    animate->frame2 = frame2;
    animate->delay = delay;
    animate->init();
    animate->autorelease();
    return animate;
}

bool CFAnimate::init(){
    CCTextureCache* textureCache = CCTextureCache::sharedTextureCache();
    CCTexture2D* image0 = textureCache->addImage(frame0);
    CCTexture2D* image1 = textureCache->addImage(frame1);
    CCTexture2D* image2 = textureCache->addImage(frame2);
    CCRect rect0 = CCRect(0, 0, image0->getContentSize().width, image0->getContentSize().height);
    CCSpriteFrame* frame0 = CCSpriteFrame::createWithTexture(image0, rect0);
    CCRect rect1 = CCRect(0, 0, image1->getContentSize().width, image1->getContentSize().height);
    CCSpriteFrame* frame1 = CCSpriteFrame::createWithTexture(image1, rect1);
    CCRect rect2 = CCRect(0, 0, image2->getContentSize().width, image2->getContentSize().height);
    CCSpriteFrame* frame2 = CCSpriteFrame::createWithTexture(image2, rect2);
    CCSprite* sprite = CCSprite::createWithSpriteFrame(frame0);
    this->addChild(sprite);
    CCArray* animFrames = CCArray::createWithCapacity(3);
    animFrames->addObject(frame0);
    animFrames->addObject(frame1);
    animFrames->addObject(frame2);
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, delay);
    CCAnimate *animate = CCAnimate::create(animation);
    sprite->runAction(CCRepeatForever::create(animate));
    animFrames->release();
    return true;
}
