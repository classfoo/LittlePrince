#ifndef __Asteroid__CFGameContext__
#define __Asteroid__CFGameContext__

#include "cocos2d.h"
#include "CFShader.h"
#ifdef __OBJC__
#include "Box2D.h"
#else
#include "Box2D/Box2D.h"
#endif
#include "CFConsts.h"
#include "CFGameLevel.h"
#include "SimpleAudioEngine.h"
#include "CFNode.h"
#include <stddef.h>
using namespace cocos2d;
using namespace CocosDenshion;

class CFGameBoardContext:public CCNode{
public:
    virtual void onStartGame(CCObject* pSender);
    virtual void onResumeGame(CCObject* pSender);
    virtual void onPauseGame(CCObject* pSender);
    virtual void onCloseGame(CCObject* pSender);
    virtual void onPassGame(CCObject* pSender);
    virtual void onChangeToLevel(CCObject* pSender, int level);
    //游戏过关切换效果函数
    virtual void onBeforePassGame();
    virtual void onDoPassGame();
    virtual void onAfterPassGame();

    CREATE_FUNC(CFGameBoardContext);
};

class CFGameSpaceContext:public CCNode,public CFGameLevelListener{
public:
    CFGameSpaceContext(void);
    virtual ~CFGameSpaceContext(void);
    virtual void onStartGame(CCObject* pSender);
    virtual void onResumeGame(CCObject* pSender);
    virtual void onPauseGame(CCObject* pSender);
    virtual void onCloseGame(CCObject* pSender);
    virtual void onPassGame(CCObject* pSender);
    virtual void onChangeToLevel(CCObject* pSender, int level);
    virtual void onBeganTouch(time_t beginTouchTime, CCPoint beginTouchLocation);
    virtual void onEndTouch(time_t beginTouchTime, CCPoint beginTouchLocation, time_t endTouchTime, CCPoint endTouchLocation);
    virtual void onGameTaskStory(CCDictionary* task, int taskindex);
    virtual void onGameTaskStart(CCDictionary* task, int taskindex);
    virtual void onGameTaskOngoing(CCDictionary* task, int taskindex);
    virtual void onGameTaskComplete(CCDictionary* task, int taskindex);
    //游戏过关切换效果函数
    virtual void onBeforePassGame();
    virtual void onDoPassGame();
    virtual void onAfterPassGame();

    virtual bool isActive();
    virtual float getSpeed();
    virtual void setSpeed(float speed);
    virtual void speedRight();
    virtual void speedLeft();
    virtual void jump(float force);
    
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
    //CREATE_FUNC(CFGameSpaceContext);
};

class CFGameContext:public CCNode, public CFGameLevelListener{
private:
    bool started;
    bool english;
    const char* lang;
    CFGameBoardContext* boardContext;
    CFGameSpaceContext* spaceContext;
    CCSprite* gamepassboard;
    CFGameLevel* level;
    CFGameLevel* loadLevel(int level);
public:
    CFGameContext(void);
    virtual ~CFGameContext(void);
    virtual bool init();
    
    void startGame(CCObject* pSender);
    void resumeGame(CCObject* pSender);
    void lockedGame(CCObject* pSender);
    void pauseGame(CCObject* pSender);
    void closeGame(CCObject* pSender);
    void passGame(CCObject* pSender);
    bool isGameStarted();
    bool isEnglish();
    const char* getLanguage();
    CFGameLevel* changeToLevel(int level);
    CFGameLevel* getCurrentLevel();
    
    //播放音乐
    void playEffect(const char* name, bool loop);
    void playMusic(const char* name, bool loop);
    
    void setBoardContext(CFGameBoardContext* boardContext);
    CFGameBoardContext* getBoardContext();
    void setSpaceContext(CFGameSpaceContext* spaceContext);
    CFGameSpaceContext* getSpaceContext();
    virtual void onBeganTouch(time_t beginTouchTime, CCPoint beginTouchLocation);
    virtual void onEndTouch(time_t beginTouchTime, CCPoint beginTouchLocation, time_t endTouchTime, CCPoint endTouchLocation);
    virtual void onGamePass(CCDictionary* pet, int countleft);
    virtual void onGameTaskStory(CCDictionary* task, int taskindex);
    virtual void onGameTaskStart(CCDictionary* task, int taskindex);
    virtual void onGameTaskOngoing(CCDictionary* task, int taskindex);
    virtual void onGameTaskComplete(CCDictionary* task, int taskindex);
    
    //游戏过关切换效果函数
    virtual void onBeforePassGame();
    virtual void onDoPassGame();
    virtual void onAfterPassGame();
    CREATE_FUNC(CFGameContext);
};

#endif
