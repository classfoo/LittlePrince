#ifndef __Asteroid__CFGameLevel__
#define __Asteroid__CFGameLevel__

#include "CFCocosUtil.h"
#include "cocos2d.h"
USING_NS_CC;

class CFGameLevelListener{
public:
    virtual void onGameTaskStory(CCDictionary* task, int taskindex);
    virtual void onGameTaskStart(CCDictionary* task, int taskindex);
    virtual void onGameTaskOngoing(CCDictionary* task, int taskindex);
    virtual void onGameTaskComplete(CCDictionary* task, int taskindex);
    virtual void onGamePass(CCDictionary* pet, int countleft);
};

class CFGameLevel{
private:
    int level;
    const char* levelName;
    const char* levelDesc;
    ccColor3B levelColor;
    const char* gamepassinfo;
    const char* gamestartinfo;
    int planetR;
    int planetWeight;
    int planetTop;
    float sunRotSpeed;
    int heroHeight;
    int heroWeight;
    int heroTop;
    GLuint planetTexture;
    GLuint skyTextureDay;
    GLuint skyTextureNight;
    int enemyCount;

    CCArray* planetItems;
    CCArray* enemies;
    CCArray* gifts;
    CCArray* tasks;
    int currentTask;
    CCDictionary* properties;
    CCDictionary* pet;
    CCDictionary* getEnemyDictionary(int type, int stage);
    CCDictionary* getGiftDictionary(int type);
    void updatePetWordsIndex();
    void updatePlanetItemWordIndex();
public:
    CFGameLevel(void);
    virtual ~CFGameLevel(void);
    static CFGameLevel* create(int level, CCDictionary* dict);
    bool init(CCDictionary* dict);
    int getLevel();
    const char* getLevelName();
    const char* getLevelDesc();
    ccColor3B getLevelColor();
    const char* getGamePassInfo();
    const char* getGameStartInfo();
    
    //获取关卡基本信息
    virtual GLuint getPlanetTexture();
    virtual int getPlanetWeight();
    virtual int getPlanetR();
    virtual int getPlanetTop();
    virtual float getSunRotSpeed();
    virtual int getHeroWeight();
    virtual int getHeroTop();
    virtual GLuint getSkyTextureDay();
    virtual GLuint getSkyTextureNight();
    
    //获取星球中NPC信息
    virtual CCArray* getPlanetItems();
    virtual CCDictionary* checkPlanetItemWords(int index, CFGameLevelListener* listener);

    //获取星球中的敌人信息
    virtual int getEnemyTypeCount();
    virtual int getEnemyStageCount(int type);
    virtual const char* getEnemyName(int type, int stage);
    virtual int getEnemyGiftType(int type, int stage);
    virtual bool getEnemyCanDestroy(int type, int stage, int pstatus);
    virtual void recordEnemyCount(int count);
    virtual bool checkEnemyCountLimit();
    
    //获取星球中的奖励信息
    virtual int getGiftTypeCount();
    virtual const char* getGiftName(int type);
    virtual const char* getGiftAward(int type);
    virtual int getGiftAwardCount(int type);
    virtual int getGiftEnergy(int type);
    virtual int getGiftAction(int type);
    virtual int getGiftSeconds(int type);
    virtual int getGiftAwardSeconds(int type);
    
    //获取星球中的宠物信息
    virtual const char* getPetName();
    virtual const char* getPetProduct();
    virtual int getPetInitHeight();
    virtual float getPetInitRot();
    virtual int getPetInitSpeed();
    virtual int getPetFeedStatus();
    virtual CCDictionary* checkPetWords(CFGameLevelListener* listener);

    //获取关卡内任务信息
    virtual const char* checkTaskStories(CFGameLevelListener* listener);
    virtual bool checkTaskComplete(int princeStatus, CFGameLevelListener* listener);
    virtual int getCurrentTask();
    virtual int getCurrentTaskStatus();
};
#endif
