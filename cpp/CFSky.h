#ifndef __Asteroid__CFSky__
#define __Asteroid__CFSky__

#include <iostream>
#include "CFNode.h"
#include "CFGameContext.h"
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
/**
 * Sky Box
 */
class CFSky:public CFNode{
private:
    CFGameContext* context;
    GLint slices;//圆的轴数，轴越多圆弧越弯曲
    GLint stacks;//饱和度，值越大，越鼓
    ccVertex3F* v;
    ccVertex3F* n;
    ccVertex2F* t;
    float skyrot;
    void genSkyPoints(GLfloat x, GLfloat y, GLfloat z, GLfloat rot, GLfloat radius,ccVertex3F* v,ccVertex3F* n,ccVertex2F* t);
public:
    CFSky(void);
    virtual ~CFSky(void);
    static CFSky* create(CFGameContext* context);
    virtual bool init();
    virtual void draw();
    virtual b2Body* getBody();
};

#endif
