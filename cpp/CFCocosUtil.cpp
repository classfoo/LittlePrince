#include "CFCocosUtil.h"

int CFCocosUtil::getIntFromDict(CCDictionary *dict, const char *key, int def){
    int r;
    const CCString* str = dict->valueForKey(key);
    if(str == NULL){
        return def;
    }
    if(str->length() == 0){
        return def;
    }
    sscanf( str->getCString(), "%d", &r );
    return r;
}

float CFCocosUtil::getFloatFromDict(CCDictionary *dict, const char *key, float def){
    float r;
    const CCString* str = dict->valueForKey(key);
    if(str == NULL){
        return def;
    }
    if(str->length() == 0){
        return def;
    }
    sscanf( str->getCString(), "%f", &r);
    return r;
}

const char* CFCocosUtil::getStringFromDict(cocos2d::CCDictionary *dict, const char *key, const char* def){
    const CCString* str = dict->valueForKey(key);
    if(str == NULL){
        return def;
    }
    if(str->length() == 0){
        return def;
    }
    return str->getCString();
}

int CFCocosUtil::getIntFromArray(CCArray* array, int index, int def){
    int r;
    CCString* str = (CCString*)array->objectAtIndex(index);
    if(str == NULL){
        return def;
    }
    if(str->length() == 0){
        return def;
    }
    sscanf( str->getCString(), "%d", &r );
    return r;

}

const char* CFCocosUtil::getStringFromArray(CCArray* array, int index, const char* def){
    CCString* str = (CCString*)array->objectAtIndex(index);
    if(str == NULL){
        return def;
    }
    if(str->length() == 0){
        return def;
    }
    return str->getCString();
}


GLuint CFCocosUtil::getTexture(const char* name){
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey(name);
    if(texture != NULL){
        return texture->getName();
    }
    GLuint num = CCTextureCache::sharedTextureCache()->addImage(name)->getName();
    return num;
}
