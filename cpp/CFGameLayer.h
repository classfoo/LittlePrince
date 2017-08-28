#ifndef __CFGAMELAYER_H__
#define __CFGAMELAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#ifdef __OBJC__
	#import <UIKit/UIKit.h>
	#import <OpenGLES/EAGL.h>
	#import <OpenGLES/ES1/gl.h>
	#import <OpenGLES/ES1/glext.h>
	#include "Box2D.h"
#else
	//#include <EGL/EGL.h>
	//#include <GLES/gl.h>
	//#include <GLES/glext.h>
	//#include "Box2D/Box2D.h"
#endif
#include <stddef.h>
#include "SimpleAudioEngine.h"

#include "CFGameContext.h"
#include "CFGameBoard.h"
#include "CFGameSpace.h"
#include "time.h"

#define LIMIT_TOP 0.6
#define LIMIT_BOTTOM 0.2

USING_NS_CC;
USING_NS_CC_EXT;

class CFGameLayer : public CCLayer
{
private:
    CFGameContext* context;
    CCPoint beginTouchLocation;
    time_t beginTouchTime;
public:
    CFGameLayer(void);
    virtual ~CFGameLayer(void);
    virtual bool init();
    //添加广告必须
    static void addAd();//添加iad
    static void deletAd();//删除iad
    static void * view;//EGLView指针
    
    static CCScene* scene();
    virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
    virtual void ccTouchesMoved(CCSet *touches, CCEvent *event);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    virtual void ccTouchesCancelled(CCSet *touches, CCEvent *event);
    CREATE_FUNC(CFGameLayer);
};

#endif
