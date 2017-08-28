#ifndef __LePetitPrince__CFLabel__
#define __LePetitPrince__CFLabel__

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class CFLabel:public CCNode{
private:
    const char* text;
    const char* font;
    float size;
    float width;
    float height;
    ccColor3B color;
    CCLabelTTF* ttf;
    CCLabelBMFont* bmfnt;
public:
    CFLabel(void);
    virtual ~CFLabel(void);
    static CFLabel* create(const char* text, const char* font, float size,const ccColor3B);
    static CFLabel* create(const char* text, const char* font, float size, const ccColor3B,float width, float height);
    virtual bool init();
    virtual void setString(const char* text);
    virtual const char* getFont();
};
#endif
