#include "CFNpc.h"
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
#define PI_ 3.14159265358979323846

CFNpc::CFNpc(void):body(NULL),circle(0),lifeTime(0),night(false){

}

CFNpc::~CFNpc(void){
    if(this->body!= NULL && this->context != NULL){
        this->context->getSpaceContext()->getWorld()->DestroyBody(this->body);
        this->body = NULL;
    }
}

//NPCs
bool CFNpc::init(){
    bool ret = false;
    do{
        this->setNPCPosition();
        this->sunRotSpeed = this->context->getCurrentLevel()->getSunRotSpeed();
        scheduleUpdate();
        ret = true;
    }while(0);
    return ret;
}

void CFNpc::update(float dt){
    this->setNPCPosition();
    float sunRotSpeed = this->context->getCurrentLevel()->getSunRotSpeed();
    float rot =(lifeTime++)*sunRotSpeed;
    if(rot>=2*PI_*(circle)){
        this->onCircle(circle++);
    }
    CFUtil::updateBody(this->getBody(), this, this->context);
}

b2Body* CFNpc::getBody(){
    return NULL;
}

void CFNpc::setNPCPosition(){
    if(context->getSpaceContext() == NULL){
        return;
    }
    //CCLog("posx:%f,posy:%f", planet->getR(), planet->getRot());
    float basex = context->getSpaceContext()->getPlanetX();
    float basey = context->getSpaceContext()->getPlanetY();
    float pzoom = context->getSpaceContext()->getPlanetZoom();
    float pr = context->getCurrentLevel()->getPlanetR();
    float height =(pr/2 + this->height);
    float baseh = height*pzoom;
    float rotSpeed = -atanf(speed/height);
    this->rot += context->getSpaceContext()->getPlanetRotSpeed() + rotSpeed;
    //CCLog("basex:%f,basey:%f,pzoom:%f,pr:%f,rot:%f", basex, basey, pzoom, pr, rot);
    if(this->rot > 2*PI_){
        //CCLog("zoom:%f" ,this->rot);
        this->rot -= 2*PI_;
    }else if(this->rot <= -2*PI_){
        this->rot += 2*PI_;
    }
    //CCLog("ROT:%f", -rot*180/PI_);
    this->setRotation(-rot*180/PI_);
    this->setScale(context->getSpaceContext()->getPlanetZoom());
    this->setPositionX(basex + baseh*sinf(-rot));
    this->setPositionY(basey + baseh*cosf(-rot));
}

void CFNpc::onCircle(int circle){
    //CCLog("circle:%i", circle);
}

/**
 * 通过opengl绘制的NPC抽象实现
 */
CFGLNpc::CFGLNpc():z(0),cloud(0),textureDay(NULL),textureNight(NULL),v(NULL),n(NULL),t(NULL){
    //顶点
    v = (ccVertex3F*)malloc(4*sizeof *v);
    //法线
    n = (ccVertex3F*)malloc(4*sizeof *n);
    //纹理
    t =  (ccVertex2F*)malloc(4*sizeof *t);
}

CFGLNpc::~CFGLNpc(){
    if(v != NULL){
        free(v);
        v = NULL;
    }
    if(n != NULL){
        free(n);
        n = NULL;
    }
    if(t != NULL){
        free(t);
        t = NULL;
    }
}

void CFGLNpc::draw(){
    CFShader* shader = this->context->getSpaceContext()->getShader();
    //XXX 确保gl绘制的光线比星球和天空延迟45度,已取得较好效果
    float sunrot = context->getSpaceContext()->getSunRot() - PI_/4;
    shader->setShaderUniforms(CFSHADER_NPC, sunrot, this);
    this->genItemPoints(v, n, t);
    if(this->textureDay != NULL){
        ccGLBindTexture2DN((GLuint)0,(GLuint)this->textureDay->getName());
    }
    if(this->textureNight != NULL){
        ccGLBindTexture2DN((GLuint)1,(GLuint)this->textureNight->getName());
    }
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, 0, v);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, t);
    glVertexAttribPointer(kCCVertexAttrib_Normals, 3, GL_FLOAT, GL_FALSE, 0, n);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void CFGLNpc::genItemPoints(ccVertex3F *v, ccVertex3F *n, ccVertex2F *t){
    float width = this->textureDay->getPixelsWide();
    float height = this->textureDay->getPixelsHigh();
    
    float r = this->context->getCurrentLevel()->getPlanetR()/2;
    float yscale = r-r*cos(asin(width/(2*r)));
    
    v->x =-width/2 ,v->y = -yscale,v->z = this->z;
    n->x = 1;n->y =1,n->z = 1;
    t->x = 0;t->y = 1;
    v++,n++,t++;
    
    v->x =-width/2 ,v->y = height,v->z = this->z;
    n->x = 1;n->y =1,n->z = 1;
    t->x = 0;t->y = 0;
    v++,n++,t++;
    
    v->x =width/2 ,v->y = -yscale,v->z = this->z;
    n->x = 1;n->y =1,n->z = 1;
    t->x = 1;t->y = 1;
    v++,n++,t++;
    
    v->x =width/2 ,v->y = height,v->z = this->z;
    n->x = 1;n->y =1,n->z = 1;
    t->x = 1;t->y = 0;
}
