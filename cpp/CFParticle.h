#ifndef __Asteroid__CFParticle__
#define __Asteroid__CFParticle__
#include "CFNpc.h"
#include <iostream>

class CFParticle:public CFNpc{
public:
    CFParticle(void);
    virtual ~CFParticle(void);
    static CFParticle* create(string name, float initHeight, float initRot, float initSpeed,CFGameContext* context);
    virtual bool init();
    virtual void update(float dt);
    virtual b2Body* getBody();
};
#endif
