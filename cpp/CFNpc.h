#ifndef __Asteroid__CFNpc__
#define __Asteroid__CFNpc__

#include <iostream>

#include "cocos2d.h"
#ifdef __OBJC__
#include "Box2D.h"
#else
#include "Box2D/Box2D.h"
#endif
#include "CFGameContext.h"
#include "CFNode.h"
#include "CFUtil.h"
#ifdef __IOS__
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

//NPC Objects
class CFNpc: public CFNode{
protected:
    CFGameContext* context;
    long lifeTime;
    int circle;
    bool night;
    int sunRotSpeed;
    b2Body* body;
    void setNPCPosition();
public:
    CFNpc(void);
    virtual ~CFNpc(void);
    virtual bool init();
    void update(float dt);
    virtual b2Body* getBody() = 0;
    //invoke per circle around the planet
    virtual void onCircle(int circle);
};

class CFGLNpc:public CFNpc{
protected:
    CCTexture2D* textureDay;
    CCTexture2D* textureNight;
    ccVertex3F* v;
    ccVertex3F* n;
    ccVertex2F* t;
    float z;
    string name;
    int cloud;
public:
    CFGLNpc(void);
    virtual ~CFGLNpc(void);
    virtual void draw();
    void genItemPoints(ccVertex3F* v,ccVertex3F* n,ccVertex2F* t);
};
#endif
