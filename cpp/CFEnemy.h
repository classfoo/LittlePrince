#ifndef __Asteroid__CFEnemy__
#define __Asteroid__CFEnemy__
#include "cocos2d.h"
#include "CFPlanet.h"
#include "CFNode.h"
#include "CFNpc.h"
#include "CFUtil.h"
#include "CFGift.h"
#include "CFPlanetItem.h"
#include "CFParticle.h"

using namespace cocos2d;

class CFEnemy: public CFGLNpc {
private:
    float initSpeed;
    int enemyType;
    int enemyStage;
    int maxEnemyStage;
    int getEnemyStage();
    CCSize size;
    bool conflicted;
public:
    CFEnemy(void);
    virtual ~CFEnemy(void);
    static CFEnemy* create(const char* filename, int enemyType, float initHeight, float initRot, float initSpeed, CFGameContext* context);
    virtual bool init();
    void update(float dt);
    virtual void onCircle(int circle);
    virtual void onConflict(b2Contact* contact,CFNode* other);
    virtual void onEndConflict(b2Contact* contact,CFNode* other);
    virtual b2Body* getBody();
    virtual CCSize getContentSize();
};

#endif
