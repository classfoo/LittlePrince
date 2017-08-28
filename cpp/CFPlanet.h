#ifndef __CFPLANET_H__
#define __CFPLANET_H__

#include "cocos2d.h"

#include "CFNode.h"
#include "CFShader.h"
#include "CFGameContext.h"
#include "CFUtil.h"

#ifdef __OBJC__
	#import <UIKit/UIKit.h>
	#import <OpenGLES/EAGL.h>
	#import <OpenGLES/ES1/gl.h>
	#import <OpenGLES/ES1/glext.h>
#else
	//#include <EGL/EGL.h>
	//#include <GLES/gl.h>
	//#include <GLES/glext.h>
	//#include "GLES-Render.h"
#endif
#define GM_ 66.7
#include <stddef.h>
using namespace cocos2d;

class CFPlanet: public CFNode{
private:
    GLint slices;//圆的轴数，轴越多圆弧越弯曲
    GLint stacks;//饱和度，值越大，越鼓
    ccVertex3F* v;
    ccVertex3F* n;
    ccVertex2F* t;
    float zoom;
    float rotSpeed;
    float x;
    float y;
    float sunrot;
    b2Body* body;
    CFGameContext* context;
    void drawPlanet(float R, float top,GLuint texture);
    void genPlanetPoints(GLfloat x, GLfloat y, GLfloat radius, ccVertex3F* v, ccVertex3F* n, ccVertex2F* t);
public:
    CFPlanet(void);
    virtual ~CFPlanet(void);
    static CFPlanet* create(CFGameContext* context);
    virtual bool init();
    virtual void update(float dt);
    virtual void draw();
    virtual b2Body* getBody();
    float getR();
    float getX();
    float getY();
    float getTop();
    float getZoom();
    float getRotSpeed();
    float getSunRot();
};
#endif
