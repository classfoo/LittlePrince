#include "CFPlanet.h"


//星球对象
CFPlanet::CFPlanet(void):body(NULL),slices(64),stacks(64),zoom(1),rotSpeed(0),x(0),y(0),sunrot(0){
    this->type = TYPE_PLANET;
    //球顶点
    v = (ccVertex3F*)malloc(stacks*(slices+1)*2*sizeof *v);
    //球法线
    n = (ccVertex3F*)malloc(stacks*(slices+1)*2*sizeof *n);
    //球纹理
    t =  (ccVertex2F*)malloc(stacks*(slices+1)*2*sizeof *t);
}

CFPlanet::~CFPlanet(void){
    if(this->body!= NULL && this->context != NULL){
        this->context->getSpaceContext()->getWorld()->DestroyBody(this->body);
        this->body = NULL;
    }
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

CFPlanet* CFPlanet::create(CFGameContext* context){
    CFPlanet* pPlanet = new CFPlanet();
    pPlanet->zoom = 1;
    pPlanet->context = context;
    pPlanet->init();
    pPlanet->autorelease();
    return pPlanet;
}

bool CFPlanet::init(){
    bool ret = false;
    do{
//        this->planetTexture =CCTextureCache::sharedTextureCache()->addImage("earth.png")->getName();
//        float max = this->context->getCurrentLevel()->getHeroTop()-this->getTop();
//        this->zoom = this->context->getSpaceContext()->getHeroHeight()<max?1:max/this->context->getSpaceContext()->getHeroHeight();
//        float minzoom = this->getTop()/(this->getR()*2);
//        this->zoom = this->zoom < minzoom?minzoom:this->zoom;
        
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        GLfloat width = size.width;
        this->x = width/2;
        this->y = this->getTop()-this->getR()*zoom/2;

        this->scheduleUpdate();
        ret = true;
    }while(0);
    return ret;
}

void CFPlanet::update(float dt){
    this->getBody();
}

void CFPlanet::draw(){
    //更新速度和缩放比例
    float lineSpeed = this->context->getSpaceContext()->getHeroSpeed();
    float height = this->context->getSpaceContext()->getHeroHeight()+this->getR()/2;
    this->rotSpeed = atanf(lineSpeed/height);
    float max = this->context->getCurrentLevel()->getHeroTop()-this->getTop();
    this->zoom = this->context->getSpaceContext()->getHeroHeight()<max?1:max/this->context->getSpaceContext()->getHeroHeight();
    float minzoom = this->getTop()/(this->getR()*2);
    this->zoom = this->zoom < minzoom?minzoom:this->zoom;
    this->rot+=this->rotSpeed;
    if(this->rot > 2*PI_){
        //CCLog("zoom:%f" ,this->rot);
        this->rot -= 2*PI_;
    }else if(this->rot < -2*PI_){
        this->rot += 2*PI_;
    }
    //绘制星球
    GLuint planetTexture = this->context->getCurrentLevel()->getPlanetTexture();
    drawPlanet(this->getR(),this->getTop(), planetTexture);
}

void CFPlanet::drawPlanet(float R, float top, GLuint texture){
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    GLfloat width = size.width;
    GLfloat radius = R*zoom/2;//半径
    this->x = width/2;
    this->y = top-R*zoom/2;
    ccGLBindTexture2D(texture);
    float sunRotSpeed = this->context->getCurrentLevel()->getSunRotSpeed();
    this->sunrot += this->rotSpeed + sunRotSpeed;//atanf(1000/(R*100));
    if(this->sunrot > 2*PI_){
        //CCLog("zoom:%f" ,this->rot);
        this->sunrot -= 2*PI_;
    }else if(this->sunrot < -2*PI_){
        this->sunrot += 2*PI_;
    }
    CFShader* shader = this->context->getSpaceContext()->getShader();
    shader->setShaderUniforms(CFSHADER_PLANET, this->sunrot, this);
    genPlanetPoints(x, y, radius, v, n, t);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, 0, v);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, t);
    glVertexAttribPointer(kCCVertexAttrib_Normals, 3, GL_FLOAT, GL_FALSE, 0, n);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, stacks*(slices+1)*2);
}

void CFPlanet::genPlanetPoints(GLfloat ox, GLfloat oy, GLfloat radius, ccVertex3F* v, ccVertex3F* n, ccVertex2F* t)
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
            GLfloat c = j * slicestep + this->rot;
            GLfloat x = (GLfloat)cos(c);
            GLfloat y = (GLfloat)sin(c);
            
            n->x = x * s0;
            v->x = ox + n->x * radius;
            
            n->y = y * s0;
            v->y = oy + n->y * radius;
            
            n->z = c0;
            v->z = n->z * radius;
            
            n++;
            v++;
            
            n->x = x * s1;
            v->x = ox + n->x * radius;
            
            n->y = y * s1;
            v->y = oy + n->y * radius;
            
            n->z = c1;
            v->z = n->z * radius;
            
            n++;
            v++;
            

            t->x = (GLfloat)(i%(ts))/ts;
            t->y = (GLfloat)(j%(ts+1))/ts;
            //CCLog("pos:%f,%f" ,t->x ,t->y);
            t++;
            t->x = (GLfloat)(i%ts+1)/ts;
            t->y = (GLfloat)(j%(ts+1))/ts;
            //CCLog("pos:%f,%f" ,t->x ,t->y);
            t++;
        }
    } 
}

b2Body* CFPlanet::getBody(){
    if(this->body != NULL){
        return this->body;
    }
    this->body = CFUtil::createBody("planet", this, this->context->getSpaceContext()->getWorld());
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    this->body->SetTransform(b2Vec2(size.width/(2*PTM_RATIO),0), 0);
    this->body->SetType(b2_staticBody);
    return this->body;
}

float CFPlanet::getR(){
    return this->context->getCurrentLevel()->getPlanetR();
}

float CFPlanet::getX(){
    return this->x;
}

float CFPlanet::getY(){
    return this->y;
}

float CFPlanet::getTop(){
    return this->context->getCurrentLevel()->getPlanetTop();
}

float CFPlanet::getZoom(){
    return this->zoom;
}

float CFPlanet::getRotSpeed(){
    return this->rotSpeed;
}

float CFPlanet::getSunRot(){
    return this->sunrot;
}
