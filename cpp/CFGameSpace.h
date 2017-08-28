#ifndef __Asteroid__CFGameSpace__
#define __Asteroid__CFGameSpace__

#include <iostream>
#include "cocos2d.h"
#ifdef __OBJC__
#include "Box2D.h"
#else
#include "Box2D/Box2D.h"
#endif
#include "CFContactListener.h"
#include "CFPlanetItem.h"
#include "CFSky.h"
#include "CFPrince.h"
#include "CFGameContext.h"
#include "CFGameStatusBoard.h"
#include "CFGameStoryBoard.h"
#include "CFGameTipsBoard.h"

using namespace cocos2d;

class CFGameSpace: public CFGameSpaceContext,CFGameStatusListener{
private:
    CFGameContext* context;
    CFSky* sky;
    CFPlanet* planet;
    CCNode* planetItems;
    CCNode* petItems;
    CFPet* pet;
    CCNode* princeItems;
    CFPrince* prince;
    CCNode* boardItems;
    CCNode* clouds;
    CCNode* enemies;
    CCNode* gifts;
    CCNode* woohoo;
    int energy;
    CFGameStatusBoard* statusboard;
    CFGameStoryBoard* storyboard;
    CFGameTipsBoard* tipsboard;
    CFContactListener* listener;
    gbox2d::GB2ShapeCache* gbcache;
    CFShader* shader;
    b2World* world;
    void reloadSky();
    void reloadPlanet();
    void reloadPlanetItems();
    void reloadBoards();
    void reloadPet();
    void reloadPrince();
    void reloadClouds();
    void reloadEnemies();
    void reloadGifts();
    void showWoohoo(const char* awardname);
    void hideWoohoo();
    bool inited;
public:
    CFGameSpace(void);
    virtual ~CFGameSpace(void);
    static CFGameSpace* create(CFGameContext* context);
    virtual bool init();
    virtual void update(float dt);
    
    virtual bool isActive();
    virtual void onStartGame(CCObject* pSender);
    virtual void onResumeGame(CCObject* pSender);
    virtual void onPauseGame(CCObject* pSender);
    virtual void onCloseGame(CCObject* pSender);
    virtual void onPassGame(CCObject* pSender);
    virtual void onChangeToLevel(CCObject* pSender, int level);
    virtual void onGameTaskAward(int gifttype, const char* awardname, int seconds);
    virtual void onGameTaskStory(CCDictionary* task, int taskindex);
    virtual void onGameTaskStart(CCDictionary* task ,int taskindex);
    virtual void onGameTaskOngoing(CCDictionary* task ,int taskindex);
    virtual void onGameTaskComplete(CCDictionary* task ,int taskindex);
    //游戏过关切换效果函数
    virtual void onBeforePassGame();
    virtual void onDoPassGame();
    virtual void onAfterPassGame();

    void loadMenus();
    virtual void onBeganTouch(time_t beginTouchTime, CCPoint beginTouchLocation);
    virtual void onEndTouch(time_t beginTouchTime, CCPoint beginTouchLocation, time_t endTouchTime, CCPoint endTouchLocation);
    float getSpeed();
    void setSpeed(float speed);
    void speedRight();
    void speedLeft();
    void jump(float force);

    //显示消息信息
    virtual void showTips(CCArray* tips);
    virtual void showStories();

    //记录游戏的gift，energy等状态
    virtual void recordEnergy(int energy);
    virtual void recordGift(int gifttype);
    virtual void setEnergy(int energy);
    virtual int getEnergy();
    
    //添加游戏动态元素，例如cloud，enemy，gift
    virtual void addCloud(const char* name, int initHeight, float initRot);
    virtual void addEnemy(const char* filename, int enemyType, float initHeight,float initRot, float initSpeed);
    virtual void addGift(int type, float initHeight, float initRot, float initSpeed);
    
    virtual CFNode* getPrince();
    virtual CFShader* getShader();
    virtual b2World* getWorld();
    virtual float getPlanetX();
    virtual float getPlanetY();
    virtual float getPlanetZoom();
    virtual float getPlanetRotSpeed();
    virtual float getPlanetRot();
    virtual float getSunRot();    
    virtual float getHeroHeight();
    virtual float getHeroSpeed();
    virtual b2Body* getHeroBody();
};

#endif
