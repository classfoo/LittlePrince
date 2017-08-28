#include "CFShader.h"

CFShaderLight::CFShaderLight(){

}

CFShaderLight::~CFShaderLight(){
    
}

CFShaderLight* CFShaderLight::create(ccColor4F ambientColor, ccColor4F diffuseColor, ccColor4F specularColor){
    CFShaderLight* light = new CFShaderLight();
    light->autorelease();
    light->ambientColor = ambientColor;
    light->diffuseColor = diffuseColor;
    light->specularColor = specularColor;
    return light;
}

CFShader::CFShader(){
    //初始化光照设置缓存
    this->lights = CCDictionary::create();
    this->lights->retain();

    //加载planet的shader
    CCShaderCache* cache = CCShaderCache::sharedShaderCache();
    CCGLProgram* shader1 = new CCGLProgram();
    shader1->initWithVertexShaderByteArray(CFVSHADER_PLANET,CFFSHADER_PLANET);
    shader1->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    shader1->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    shader1->addAttribute(kCCAttributeNameNormal, kCCVertexAttrib_Normals);
    shader1->link();
    cache->addProgram(shader1,CFSHADER_PLANET);
    //加载planet的light
    ccColor4F ambientColor1 = ccc4f(0.2, 0.2, 0.2,1);
    ccColor4F diffuseColor1 = ccc4f(0.5, 0.5, 0.5,1);
    ccColor4F specularColor1 = ccc4f(2, 2, 2,1);
    CFShaderLight* light1 = CFShaderLight::create(ambientColor1, diffuseColor1,specularColor1);
    this->lights->setObject(light1, CFSHADER_PLANET);
    
    //加载sky的shader
    CCGLProgram* shader2 = new CCGLProgram();
    shader2->initWithVertexShaderByteArray(CFVSHADER_SKY,CFFSHADER_SKY);
    shader2->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    shader2->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    shader2->addAttribute(kCCAttributeNameNormal, kCCVertexAttrib_Normals);
    shader2->link();
    cache->addProgram(shader2,CFSHADER_SKY);
    //加载sky的light
    ccColor4F ambientColor2 = ccc4f(0.2, 0.2, 0.2,1);
    ccColor4F diffuseColor2 = ccc4f(0.5, 0.5, 0.5,1);
    ccColor4F specularColor2 = ccc4f(2, 2, 2,1);
    CFShaderLight* light2 = CFShaderLight::create(ambientColor2, diffuseColor2,specularColor2);
    this->lights->setObject(light2, CFSHADER_SKY);
    
    //加载npc的shader
    CCGLProgram* shader3 = new CCGLProgram();
    shader3->initWithVertexShaderByteArray(CFVSHADER_NPC,CFFSHADER_NPC);
    shader3->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    shader3->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    shader3->addAttribute(kCCAttributeNameNormal, kCCVertexAttrib_Normals);
    shader3->link();
    cache->addProgram(shader3,CFSHADER_NPC);
    //加载npc的light
    ccColor4F ambientColor3 = ccc4f(0.2, 0.2, 0.2,1);
    ccColor4F diffuseColor3 = ccc4f(0.5, 0.5, 0.5,1);
    ccColor4F specularColor3 = ccc4f(2, 2, 2,1);
    CFShaderLight* light3 = CFShaderLight::create(ambientColor3, diffuseColor3,specularColor3);
    this->lights->setObject(light3, CFSHADER_NPC);
}

CFShader::~CFShader(){
    if(this->lights != NULL){
        this->lights->release();
        this->lights=NULL;
    }
}

void CFShader::setShaderUniforms(const char* shaderkey, float sunrot, CCNode* node){
    CCShaderCache* cache = CCShaderCache::sharedShaderCache();
    CCGLProgram* shader = cache->programForKey(shaderkey);
    shader->updateUniforms();
    CFShaderLight* light = (CFShaderLight*)this->lights->objectForKey(shaderkey);
    shader->setUniformLocationWith3f(shader->getUniformLocationForName("u_directionalLight.direction"), 0, 0, -1);
    shader->setUniformLocationWith3f(shader->getUniformLocationForName("u_directionalLight.halfplane"), sinf(-sunrot), cosf(-sunrot), 0);
    shader->setUniformLocationWith4f(shader->getUniformLocationForName("u_directionalLight.ambientColor"), light->ambientColor.r, light->ambientColor.g, light->ambientColor.b,light->ambientColor.a);
    shader->setUniformLocationWith4f(shader->getUniformLocationForName("u_directionalLight.diffuseColor"),light->diffuseColor.r, light->diffuseColor.g, light->diffuseColor.b,light->diffuseColor.a);
    shader->setUniformLocationWith4f(shader->getUniformLocationForName("u_directionalLight.specularColor"), light->specularColor.r, light->specularColor.g, light->specularColor.b,light->specularColor.a);
    shader->setUniformLocationWith4f(shader->getUniformLocationForName("u_material.ambientFactor"), 1, 1, 1,1);
    shader->setUniformLocationWith4f(shader->getUniformLocationForName("u_material.diffuseFactor"), 1, 1, 1,1);
    shader->setUniformLocationWith4f(shader->getUniformLocationForName("u_material.specularFactor"), 1, 1, 1,1);
    shader->setUniformLocationWith1f(shader->getUniformLocationForName("u_material.shininess"), 1);

    //XXX cocos2d-x设置了一个很小的景深，因此需要修改
    kmMat4 matrixPerspective;
    kmGLMatrixMode(KM_GL_PROJECTION);
    kmGLLoadIdentity();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    kmMat4PerspectiveProjection( &matrixPerspective, 60, (GLfloat)size.width/size.height, 0.1f, 50000);
    kmGLMultMatrix(&matrixPerspective);
    kmGLMatrixMode(KM_GL_MODELVIEW);
    shader->setUniformsForBuiltins();
    node->setShaderProgram(shader);
    CCDirector::sharedDirector()->setDepthTest(true);
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords|kCCVertexAttribFlag_Normals);
}
