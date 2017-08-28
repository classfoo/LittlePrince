#ifndef __Asteroid__CFShaderSprite__
#define __Asteroid__CFShaderSprite__

#include "cocos2d.h"
#ifdef __OBJC__
#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#endif

#define PI_ 3.14159265358979323846

#define CFSHADER_PLANET "cfshader_planet"
#define CFVSHADER_PLANET "precision lowp float;\n\
attribute vec4 a_position;\n\
attribute vec2 a_texCoord;\n\
attribute vec3 a_normal;\n\
varying vec2 v_texCoord;\n\
varying vec3 v_normal;\n\
varying vec3 v_ecNormal;\n\
void main()\n\
{\n\
v_texCoord = a_texCoord;\n\
v_normal = a_normal;\n\
vec4 mcPosition = a_position;\n\
vec3 mcNormal = a_normal;\n\
vec3 ecNormal = vec3(CC_MVMatrix * vec4(mcNormal, 0.0));\n\
ecNormal = ecNormal / length(ecNormal);\n\
v_ecNormal = ecNormal;\n\
gl_Position = CC_MVPMatrix*a_position;\n\
}\n\
"

#define CFFSHADER_PLANET "precision lowp float;\n\
struct DirectionalLight {\n\
vec3 direction;\n\
vec3 halfplane;\n\
vec4 ambientColor;\n\
vec4 diffuseColor;\n\
vec4 specularColor;\n\
};\n\
struct Material {\n\
vec4 ambientFactor;\n\
vec4 diffuseFactor;\n\
vec4 specularFactor;\n\
float shininess;\n\
};\n\
uniform sampler2D CC_Texture0;\n\
uniform DirectionalLight u_directionalLight;\n\
uniform Material u_material;\n\
varying vec2 v_texCoord;\n\
varying vec3 v_ecNormal;\n\
void main()\n\
{\n\
vec4 baseColor = texture2D(CC_Texture0, v_texCoord);\n\
vec3 ecNormal = v_ecNormal / length(v_ecNormal);\n\
float ecNormalDotLightDirection = max(0.0, dot(ecNormal, u_directionalLight.direction));\n\
float ecNormalDotLightHalfplane = max(0.0, dot(ecNormal, u_directionalLight.halfplane));\n\
vec4 ambientLight = u_directionalLight.ambientColor * u_material.ambientFactor;\n\
vec4 diffuseLight = ecNormalDotLightDirection * u_directionalLight.diffuseColor * u_material.diffuseFactor;\n\
vec4 specularLight = vec4(0.0);\n\
if (ecNormalDotLightHalfplane > 0.0) {\n\
specularLight = pow(ecNormalDotLightHalfplane, u_material.shininess) * u_directionalLight.specularColor * u_material.specularFactor;\n\
}\n\
vec4 light = baseColor*(ambientLight + diffuseLight + specularLight);\n\
gl_FragColor = light;\n\
}\n\
"


#define CFSHADER_SKY "cfshader_sky"
#define CFVSHADER_SKY "precision lowp float;\n\
attribute vec4 a_position;\n\
attribute vec2 a_texCoord;\n\
attribute vec3 a_normal;\n\
varying vec2 v_texCoord;\n\
varying vec3 v_normal;\n\
varying vec3 v_ecNormal;\n\
void main()\n\
{\n\
v_texCoord = a_texCoord;\n\
v_normal = a_normal;\n\
vec4 mcPosition = a_position;\n\
vec3 mcNormal = a_normal;\n\
vec3 ecNormal = vec3(CC_MVMatrix * vec4(mcNormal, 0.0));\n\
ecNormal = ecNormal / length(ecNormal);\n\
v_ecNormal = ecNormal;\n\
gl_Position = CC_MVPMatrix*a_position;\n\
}\n\
"

#define CFFSHADER_SKY "precision lowp float;\n\
struct DirectionalLight {\n\
vec3 direction;\n\
vec3 halfplane;\n\
vec4 ambientColor;\n\
vec4 diffuseColor;\n\
vec4 specularColor;\n\
};\n\
struct Material {\n\
vec4 ambientFactor;\n\
vec4 diffuseFactor;\n\
vec4 specularFactor;\n\
float shininess;\n\
};\n\
uniform sampler2D CC_Texture0,CC_Texture1;\n\
uniform DirectionalLight u_directionalLight;\n\
uniform Material u_material;\n\
varying vec2 v_texCoord;\n\
varying vec3 v_ecNormal;\n\
void main()\n\
{\n\
vec4 baseColor0 = texture2D(CC_Texture0, v_texCoord);\n\
vec4 baseColor1 = texture2D(CC_Texture1, v_texCoord);\n\
vec3 ecNormal = v_ecNormal / length(v_ecNormal);\n\
float ecNormalDotLightDirection = max(0.0, dot(ecNormal, u_directionalLight.direction));\n\
float ecNormalDotLightHalfplane = max(0.0, dot(ecNormal, u_directionalLight.halfplane));\n\
vec4 ambientLight = u_directionalLight.ambientColor * u_material.ambientFactor;\n\
vec4 diffuseLight = ecNormalDotLightDirection * u_directionalLight.diffuseColor * u_material.diffuseFactor;\n\
vec4 specularLight = vec4(0.0);\n\
if (ecNormalDotLightHalfplane > 0.0) {\n\
    specularLight = pow(ecNormalDotLightHalfplane, u_material.shininess) * u_directionalLight.specularColor * u_material.specularFactor;\n\
    vec4 light = baseColor1*vec4(0.1)+baseColor0*(ambientLight + diffuseLight + specularLight);\n\
    gl_FragColor = light;\n\
}else{\n\
    vec4 light = (baseColor1*vec4(3) + baseColor0)*(ambientLight + diffuseLight + specularLight);\n\
    gl_FragColor = light;\n\
}\n\
}\n\
"

#define CFSHADER_NPC "cfshader_npc"
#define CFVSHADER_NPC "precision lowp float;\n\
attribute vec4 a_position;\n\
attribute vec2 a_texCoord;\n\
attribute vec3 a_normal;\n\
varying vec2 v_texCoord;\n\
varying vec3 v_normal;\n\
varying vec3 v_ecNormal;\n\
void main()\n\
{\n\
v_texCoord = a_texCoord;\n\
v_normal = a_normal;\n\
vec4 mcPosition = a_position;\n\
vec3 mcNormal = a_normal;\n\
vec3 ecNormal = vec3(CC_MVMatrix * vec4(mcNormal, 0.0));\n\
ecNormal = ecNormal / length(ecNormal);\n\
v_ecNormal = ecNormal;\n\
gl_Position = CC_MVPMatrix*a_position;\n\
}\n\
"

#define CFFSHADER_NPC "precision lowp float;\n\
struct DirectionalLight {\n\
vec3 direction;\n\
vec3 halfplane;\n\
vec4 ambientColor;\n\
vec4 diffuseColor;\n\
vec4 specularColor;\n\
};\n\
struct Material {\n\
vec4 ambientFactor;\n\
vec4 diffuseFactor;\n\
vec4 specularFactor;\n\
float shininess;\n\
};\n\
uniform sampler2D CC_Texture0,CC_Texture1;\n\
uniform DirectionalLight u_directionalLight;\n\
uniform Material u_material;\n\
varying vec2 v_texCoord;\n\
varying vec3 v_ecNormal;\n\
void main()\n\
{\n\
vec4 baseColor0 = texture2D(CC_Texture0, v_texCoord);\n\
vec4 baseColor1 = texture2D(CC_Texture1, v_texCoord);\n\
vec3 ecNormal = v_ecNormal / length(v_ecNormal);\n\
float ecNormalDotLightDirection = max(0.0, dot(ecNormal, u_directionalLight.direction));\n\
float ecNormalDotLightHalfplane = max(0.0, dot(ecNormal, u_directionalLight.halfplane));\n\
vec4 ambientLight = u_directionalLight.ambientColor * u_material.ambientFactor;\n\
vec4 diffuseLight = ecNormalDotLightDirection * u_directionalLight.diffuseColor * u_material.diffuseFactor;\n\
vec4 specularLight = vec4(0.0);\n\
if (ecNormalDotLightHalfplane > 0.0) {\n\
    specularLight = pow(ecNormalDotLightHalfplane, u_material.shininess) * u_directionalLight.specularColor * u_material.specularFactor;\n\
    vec4 light = baseColor0*(ambientLight + diffuseLight + specularLight);\n\
    gl_FragColor = light;\n\
}\n\
    vec4 light = baseColor1 + baseColor0*(ambientLight + diffuseLight + specularLight);\n\
    gl_FragColor = light;\n\
}\n\
"

using namespace cocos2d;

class CFShaderLight:public CCObject{
public:
    CFShaderLight(void);
    ~CFShaderLight(void);
    ccColor4F ambientColor;
    ccColor4F diffuseColor;
    ccColor4F specularColor;
    static CFShaderLight* create(ccColor4F ambientColor, ccColor4F diffuseColor,ccColor4F specularColor);
};


class CFShader{
private:
    CCDictionary* lights;
public:
    CFShader(void);
    virtual ~CFShader(void);
    void setShaderUniforms(const char* shaderkey, float sunrot, CCNode* node);
};
#endif
