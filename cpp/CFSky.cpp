#include "CFSky.h"

CFSky::CFSky():slices(64),stacks(64),skyrot(0){
    //球顶点
    v = (ccVertex3F*)malloc(stacks*(slices+1)*2*sizeof *v);
    //球法线
    n = (ccVertex3F*)malloc(stacks*(slices+1)*2*sizeof *n);
    //球纹理
    t =  (ccVertex2F*)malloc(stacks*(slices+1)*2*sizeof *t);
}

CFSky::~CFSky(){
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

CFSky* CFSky::create(CFGameContext* context){
    CFSky* sky = new CFSky();
    sky->context=context;
    sky->init();
    sky->autorelease();
    return sky;
}

bool CFSky::init(){
    bool ret = false;
    do{
//        this->skyTexture0 =CCTextureCache::sharedTextureCache()->addImage("blue_sky.png")->getName();
//        this->skyTexture1 =CCTextureCache::sharedTextureCache()->addImage("stars.png")->getName();
        ret = true;
    }while(0);
    return ret;
}

void CFSky::draw(){
    //绘制天空
    float R = this->context->getCurrentLevel()->getPlanetR();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    GLfloat width = size.width;
    GLfloat height = size.height;
    float x = width/2;
    //float top = this->context->getCurrentLevel()->getPlanetTop();
    //float zoom = this->context->getSpaceContext()->getPlanetZoom();
    float y = -R*2;//top-R*zoom/2;
    float z = 0;
    GLfloat radius = sqrtf(powf(width-x,2)+powf(height-y, 2))*1.2;//height;//半径
    //更新sky的角度
    float rot = this->context->getSpaceContext()->getPlanetRot();
    skyrot+= atanf(20/radius);
    if(skyrot > 2*PI_){
        //CCLog("zoom:%f" ,this->rot);
        skyrot -= 2*PI_;
    }else if(skyrot < -2*PI_){
        skyrot += 2*PI_;
    }
    rot+=skyrot;
    //kmGLPushMatrix();
    glEnable(GL_FRONT_FACE);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    CFShader* shader = this->context->getSpaceContext()->getShader();
    float sunrot = this->context->getSpaceContext()->getSunRot();
    shader->setShaderUniforms(CFSHADER_SKY, sunrot, this);
    CFGameLevel* level = this->context->getCurrentLevel();
    ccGLBindTexture2DN(0,level->getSkyTextureDay());
    ccGLBindTexture2DN(1,level->getSkyTextureNight());
    genSkyPoints(x, y, z, rot, radius, this->v,this->n, this->t);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, 0, this->v);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, this->t);
    glVertexAttribPointer(kCCVertexAttrib_Normals, 3, GL_FLOAT, GL_FALSE, 0, this->n);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, stacks*(slices+1)*2);
    glDisable(GL_CULL_FACE);
    glDisable(GL_FRONT_FACE);
    //kmGLPushMatrix();
}

void CFSky::genSkyPoints(GLfloat ox, GLfloat oy, GLfloat oz, GLfloat rot, GLfloat radius,ccVertex3F* v,ccVertex3F* n,ccVertex2F* t)
{
    GLint i, j;
    GLfloat slicestep, stackstep;
    
    stackstep = ((GLfloat)PI_) / stacks;
    slicestep = 2.0f * ((GLfloat)PI_) / slices;
    
    GLint ts = 64;
    for (i = 0; i < stacks; ++i)
    {
        GLfloat a = i * stackstep;
        GLfloat b = a + stackstep;
        
        GLfloat s0 =  (GLfloat)sin(a);
        GLfloat s1 =  (GLfloat)sin(b);
        
        GLfloat c0 =  (GLfloat)cos(a);
        GLfloat c1 =  (GLfloat)cos(b);
        for (j = 0; j <= slices; ++j)
        {
            GLfloat c = j * slicestep + rot;
            GLfloat x = (GLfloat)cos(c);
            GLfloat y = (GLfloat)sin(c);
            
            n->x = x * s0;
            v->x = ox + n->x * radius;
            
            n->y = y * s0;
            v->y = oy + n->y * radius;
            
            n->z = -c0;
            v->z = oz - n->z * radius;
            
            t->x = (GLfloat)(i%(ts))/ts;
            t->y = (GLfloat)(j%(ts+1))/ts;
            
            //CCLog("pos:%f,%f" ,t->x ,t->y);
            n++;
            v++;
            t++;
            
            n->x = x * s1;
            v->x = ox + n->x * radius;
            
            n->y = y * s1;
            v->y = oy + n->y * radius;
            
            n->z = -c1;
            v->z = oz - n->z * radius;
            
            t->x = (GLfloat)(i%ts+1)/ts;
            t->y = (GLfloat)(j%(ts+1))/ts;
            
            //CCLog("pos:%f,%f" ,t->x ,t->y);
            n++;
            v++;
            t++;
        }
    }
}

b2Body* CFSky::getBody(){
    return NULL;
}
