#ifndef __Asteroid__CFContactListener__
#define __Asteroid__CFContactListener__

#include "cocos2d.h"
#ifdef __OBJC__
#include "Box2D.h"
#else
#include "Box2D/Box2D.h"
#endif
#include "CFNode.h"
#include "CFPrince.h"
#include "CFNpc.h"
#include "CFPlanet.h"

#ifdef __OBJC__
#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#endif
using namespace cocos2d;

#include <iostream>

class CFContactListener:public b2ContactListener{
public:
    // Called when two fixtures begin to touch.
    virtual void BeginContact(b2Contact* contact);
    
    // Called when two fixtures cease to touch.
    virtual void EndContact(b2Contact* contact);
};
#endif
