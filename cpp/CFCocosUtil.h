#ifndef __Asteroid__CFCocosUtil__
#define __Asteroid__CFCocosUtil__

#include <iostream>

#ifdef __OBJC__
#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import "GLES-Render.h"
#endif

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CFCocosUtil{
public:
    static const char* getStringFromDict(CCDictionary* dict, const char* key, const char* def);
    static float getFloatFromDict(CCDictionary* dict, const char* key, float def);
    static int getIntFromDict(CCDictionary* dict, const char* key, int def);
    static int getIntFromArray(CCArray* array, int index, int def);
    static const char* getStringFromArray(CCArray* array, int index, const char* def);
    static GLuint getTexture(const char* name);
};
#endif
