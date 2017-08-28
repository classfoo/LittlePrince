#include "CFGameLayer.h"
#include <stddef.h>

#ifdef __OBJC__
	#import <UIKit/UIKit.h>
	#import <OpenGLES/EAGL.h>
	#import <OpenGLES/ES1/gl.h>
	#import <OpenGLES/ES1/glext.h>
#else
	//#include <EGL/EGL.h>
	//#include <GLES/gl.h>
	//#include <GLES/glext.h>
#endif

using namespace cocos2d;

CFGameLayer::CFGameLayer(void){

}

CFGameLayer::~CFGameLayer(){
    if(context){
        delete context;
        context = NULL;
    }
}

CCScene* CFGameLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        CFGameLayer *layer = CFGameLayer::create();
        CC_BREAK_IF(! layer);
        scene->addChild(layer);
    } while (0);
    return scene;
}

bool CFGameLayer::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());
        setTouchEnabled(true);
        setAccelerometerEnabled(true);
        this->context = CFGameContext::create();
        CFGameBoardContext* boardContext = CFGameBoard::create(context);
        CFGameSpaceContext* spaceContext = CFGameSpace::create(context);
        this->context->setSpaceContext(spaceContext);
        this->context->setBoardContext(boardContext);
        this->addChild(this->context);
        int currentLevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("lastLevel", 1);
        context->changeToLevel(currentLevel);
        bRet = true;
    } while (0);
    return bRet;
}

void CFGameLayer::ccTouchesBegan(CCSet *touches, CCEvent *pEvent){
    CCTouch* touch = (CCTouch*)(*(touches->begin()));
    if(!touch)
        return;
    time(&beginTouchTime);
    beginTouchLocation = touch->getLocationInView();
    this->context->onBeganTouch(beginTouchTime, beginTouchLocation);
}

void CFGameLayer::ccTouchesMoved(cocos2d::CCSet *touches, cocos2d::CCEvent *event){
    CCTouch* touch = (CCTouch*)(*(touches->begin()));
    if(!touch)
        return;
    //CCPoint start = touch->getStartLocationInView();
    //CCPoint end = touch->getLocationInView();
    //this->context->onTouch(start, end);
}

void CFGameLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    CCTouch* touch = (CCTouch*)(*(touches->begin()));
    if(!touch)
        return;
    time_t endTouchTime;
    time(&endTouchTime);
    CCPoint endTouchLocation = touch->getLocationInView();
    this->context->onEndTouch(beginTouchTime, beginTouchLocation, endTouchTime, endTouchLocation);
}

void CFGameLayer::ccTouchesCancelled(cocos2d::CCSet *touches, cocos2d::CCEvent *event){

}
