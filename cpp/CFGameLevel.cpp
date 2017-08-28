#include "CFGameLevel.h"

//CFGameLevelListener抽象实现
void CFGameLevelListener::onGameTaskStory(cocos2d::CCDictionary *task, int taskindex){

}

void CFGameLevelListener::onGamePass(CCDictionary* pet, int countleft){

}

void CFGameLevelListener::onGameTaskStart(CCDictionary *task, int taskindex){

}

void CFGameLevelListener::onGameTaskComplete(CCDictionary *task, int taskindex){

}

void CFGameLevelListener::onGameTaskOngoing(CCDictionary *task, int taskindex){

}

//CFGameLevel实现
CFGameLevel::CFGameLevel():gamepassinfo(NULL), gamestartinfo(NULL),levelName(NULL),levelDesc(NULL),gifts(NULL),planetItems(NULL),enemies(NULL),pet(NULL),tasks(NULL),currentTask(0), properties(NULL){

}

CFGameLevel::~CFGameLevel(){
    if(this->properties != NULL){
        this->properties->release();
        this->properties = NULL;
    }
    if(this->gifts != NULL){
        this->gifts->release();
        this->gifts = NULL;
    }
    if(this->enemies != NULL){
        this->enemies->release();
        this->enemies = NULL;
    }
    if(this->planetItems != NULL){
        this->planetItems->release();
        this->planetItems = NULL;
    }
    if(this->pet != NULL){
        this->pet->release();
        this->pet = NULL;
    }
    if(this->tasks != NULL){
        this->tasks->release();
        this->tasks = NULL;
    }
}

CFGameLevel* CFGameLevel::create(int level, cocos2d::CCDictionary* dict){
    CFGameLevel* pLevel = new CFGameLevel();
    pLevel->level = level;
    pLevel->init(dict);
    return pLevel;
}

bool CFGameLevel::init(CCDictionary* dict){
    bool ret = false;
    do{
        this->properties = (CCDictionary*)dict->objectForKey("properties");
        if(this->properties != NULL){
            this->properties->retain();
        }
        this->levelName = CFCocosUtil::getStringFromDict(properties, "name", "Level N");
        this->levelDesc = CFCocosUtil::getStringFromDict(properties, "desc", "Level N");
        int R  = CFCocosUtil::getIntFromDict(properties, "R", 0);
        int G = CFCocosUtil::getIntFromDict(properties, "G", 0);
        int B = CFCocosUtil::getIntFromDict(properties, "B", 0);
        this->levelColor = ccc3(R,G,B);
        this->gamepassinfo = CFCocosUtil::getStringFromDict(properties, "gamepass", "Game Passed!");
        this->gamestartinfo = CFCocosUtil::getStringFromDict(properties, "gamestart", "Game Started!");
        this->planetR = CFCocosUtil::getIntFromDict(properties, "planetR", 1000);
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        this->planetTop = size.height/5;
        this->planetWeight = CFCocosUtil::getIntFromDict(properties, "planetWeight", 1000);
        CCString* planetTextureName = CCString::createWithFormat("planet%d.png", this->level);
        this->planetTexture = CFCocosUtil::getTexture(planetTextureName->getCString());
        CCString* skyTextureDayName = CCString::createWithFormat("sky_day%d.png", this->level);
        this->skyTextureDay = CFCocosUtil::getTexture(skyTextureDayName->getCString());
        CCString* skyTextureNightName = CCString::createWithFormat("sky_night%d.png", this->level);
        this->skyTextureNight = CFCocosUtil::getTexture(skyTextureNightName->getCString());
        this->heroTop = size.height-300;
        this->heroWeight = CFCocosUtil::getIntFromDict(properties, "heroWeight", 1000);
        this->sunRotSpeed = CFCocosUtil::getFloatFromDict(properties, "sunRotSpeed", 0.01f);
        this->planetItems = (CCArray*)dict->objectForKey("items");
        if(this->planetItems != NULL){
            this->planetItems->retain();
        }
        this->enemies = (CCArray*)dict->objectForKey("enemies");
        if(this->enemies != NULL){
            this->enemies->retain();
        }
        this->gifts = (CCArray*)dict->objectForKey("gifts");
        if(this->gifts != NULL){
            this->gifts->retain();
        }
        this->pet = (CCDictionary*)dict->objectForKey("pet");
        if(this->pet != NULL){
            this->pet->retain();
        }
        this->tasks = (CCArray*)dict->objectForKey("tasks");
        if(this->tasks != NULL){
            this->tasks->retain();
        }
        ret = true;
    }while (0);
    return ret;
}

int CFGameLevel::getLevel(){
    return this->level;
}

const char* CFGameLevel::getLevelName(){
    return this->levelName;
}

const char* CFGameLevel::getLevelDesc(){
    return this->levelDesc;
}

ccColor3B CFGameLevel::getLevelColor(){
    return this->levelColor;
}

const char* CFGameLevel::getGamePassInfo(){
    return this->gamepassinfo;
}

const char* CFGameLevel::getGameStartInfo(){
    return this->gamestartinfo;
}

int CFGameLevel::getPlanetR(){
    return this->planetR;
}

int CFGameLevel::getPlanetTop(){
    return  this->planetTop;
}

int CFGameLevel::getPlanetWeight(){
    return this->planetWeight;
}

GLuint CFGameLevel::getPlanetTexture(){
    return this->planetTexture;
}

GLuint CFGameLevel::getSkyTextureDay(){
    return this->skyTextureDay;
}

GLuint CFGameLevel::getSkyTextureNight(){
    return this->skyTextureNight;
}

int CFGameLevel::getHeroTop(){
    return this->heroTop;
}

int CFGameLevel::getHeroWeight(){
    return this->heroWeight;
}

float CFGameLevel::getSunRotSpeed(){
    return this->sunRotSpeed;
}

CCArray* CFGameLevel::getPlanetItems(){
    return this->planetItems;
}

CCDictionary* CFGameLevel::checkPlanetItemWords(int itemIndex, CFGameLevelListener* listener){
    if(this->planetItems == NULL){
        return NULL;
    }
    if(itemIndex <0 || itemIndex >this->planetItems->count()){
        return NULL;
    }
    CCDictionary* item = (CCDictionary*)this->planetItems->objectAtIndex(itemIndex);
    if(item == NULL){
        return NULL;
    }
    CCArray* array = (CCArray*)item->objectForKey("words");
    if(array == NULL){
        return NULL;
    }
    int index = CFCocosUtil::getIntFromDict(item, "currentWordIndex", 0);
    if(index >= array->count()){
        return NULL;
    }
    CCDictionary* words = (CCDictionary*)array->objectAtIndex(index);
    if(words == NULL){
        return NULL;
    }
    int itemTask = CFCocosUtil::getIntFromDict(item, "currentItemTask", -1);
    int task = CFCocosUtil::getIntFromDict(words, "task", itemTask);
    if(task >= this->getCurrentTask()){
        return NULL;
    }
    item->setObject(CCString::createWithFormat("%i", ++index), "currentWordIndex");
    return words;
}

void CFGameLevel::updatePlanetItemWordIndex(){
    if(this->planetItems == NULL){
        return;
    }
    int count = this->planetItems->count();
    if(this->planetItems->count()){
        return;
    }
    for (int i = 0; i< count; i++) {
        CCDictionary* item = (CCDictionary*)this->planetItems->objectAtIndex(i);
        if(item == NULL){
            continue;
        }
        CCArray* array = (CCArray*)item->objectForKey("words");
        if(array == NULL){
            continue;
        }
        int index = CFCocosUtil::getIntFromDict(item, "currentWordIndex", 0);
        if(index >= array->count()){
            continue;
        }
        item->setObject(CCString::createWithFormat("%i", ++index), "currentWordIndex");
    }
}

int CFGameLevel::getEnemyTypeCount(){
    return this->enemies == NULL?0:this->enemies->count();
}

int CFGameLevel::getEnemyStageCount(int type){
    if(this->enemies == NULL){
        return 0;
    }
    if(type >= this->enemies->count()){
        return 0;
    }
    CCArray* stages = (CCArray*)this->enemies->objectAtIndex(type);
    return stages == NULL?0: stages->count();
}

const char* CFGameLevel::getEnemyName(int type, int stage){
    CCDictionary* enemy = this->getEnemyDictionary(type, stage);
    if(enemy == NULL){
        return NULL;
    }
    return CFCocosUtil::getStringFromDict(enemy, "name", NULL);
}

int CFGameLevel::getEnemyGiftType(int type, int stage){
    CCDictionary* enemy = this->getEnemyDictionary(type, stage);
    if(enemy == NULL){
        return NULL;
    }
    return CFCocosUtil::getIntFromDict(enemy, "gift", -1);
}

bool CFGameLevel::getEnemyCanDestroy(int type, int stage, int pstatus){
    CCDictionary* enemy = this->getEnemyDictionary(type, stage);
    if(enemy == NULL){
        return false;
    }
    CCArray* array = (CCArray*)enemy->objectForKey("destroy");
    if(array == NULL){
        return false;
    }
    for(int i = 0; i < array->count();i++){
        int value = CFCocosUtil::getIntFromArray(array, i, -1);
        if(value != pstatus){
            continue;
        }
        return true;
    }
    return false;
}

CCDictionary* CFGameLevel::getEnemyDictionary(int type, int stage){
    if(this->enemies == NULL){
        return NULL;
    }
    if(type >= this->enemies->count()){
        return NULL;
    }
    CCArray* stages = (CCArray*)this->enemies->objectAtIndex(type);
    if(stages == NULL){
        return NULL;
    }
    if(stage>=stages->count()){
        return NULL;
    }
    CCDictionary* enemy = (CCDictionary*)stages->objectAtIndex(stage);
    return enemy;
}

void CFGameLevel::recordEnemyCount(int count){
    enemyCount+=count;
}

bool CFGameLevel::checkEnemyCountLimit(){
    if(enemyCount>50){
        return false;
    }
    return true;
}

int CFGameLevel::getGiftTypeCount(){
    if(this->gifts == NULL){
        return 0;
    }
    return this->gifts->count();
}

const char* CFGameLevel::getGiftName(int type){
    CCDictionary* dict = this->getGiftDictionary(type);
    if(dict == NULL){
        return NULL;
    }
    return CFCocosUtil::getStringFromDict(dict, "name", NULL);
}

int CFGameLevel::getGiftAwardCount(int type){
    CCDictionary* dict = this->getGiftDictionary(type);
    if(dict == NULL){
        return NULL;
    }
    return CFCocosUtil::getIntFromDict(dict, "awardcount", 5);
}

int CFGameLevel::getGiftEnergy(int type){
    CCDictionary* dict = this->getGiftDictionary(type);
    if(dict == NULL){
        return NULL;
    }
    return CFCocosUtil::getIntFromDict(dict, "energy", 5);
}

int CFGameLevel::getGiftAction(int type){
    CCDictionary* dict = this->getGiftDictionary(type);
    if(dict == NULL){
        return NULL;
    }
    return CFCocosUtil::getIntFromDict(dict, "action", 0);
}

const char* CFGameLevel::getGiftAward(int type){
    CCDictionary* dict = this->getGiftDictionary(type);
    if(dict == NULL){
        return NULL;
    }
    return CFCocosUtil::getStringFromDict(dict, "award", "watering");
}

int CFGameLevel::getGiftSeconds(int type){
    CCDictionary* dict = this->getGiftDictionary(type);
    if(dict == NULL){
        return NULL;
    }
    return CFCocosUtil::getIntFromDict(dict, "seconds", 10);
}

int CFGameLevel::getGiftAwardSeconds(int type){
    CCDictionary* dict = this->getGiftDictionary(type);
    if(dict == NULL){
        return NULL;
    }
    return CFCocosUtil::getIntFromDict(dict, "awardseconds", 30);
}

CCDictionary* CFGameLevel::getGiftDictionary(int type){
    if(this->gifts == NULL){
        return NULL;
    }
    if(type >= this->gifts->count()){
        return NULL;
    }
    CCDictionary* dict = (CCDictionary*)this->gifts->objectAtIndex(type);
    return dict;
}

const char* CFGameLevel::getPetName(){
    if(pet == NULL){
        return NULL;
    }
    return CFCocosUtil::getStringFromDict(pet, "name", "rose");
}

const char* CFGameLevel::getPetProduct(){
    if(pet == NULL){
        return NULL;
    }
    return CFCocosUtil::getStringFromDict(pet, "product", NULL);

}

int CFGameLevel::getPetInitHeight(){
    if(pet == NULL){
        return 0;
    }
    return CFCocosUtil::getIntFromDict(pet, "initHeight", 0);
}

float CFGameLevel::getPetInitRot(){
    if(pet == NULL){
        return 0;
    }
    return CFCocosUtil::getFloatFromDict(pet, "initRot", 0);
}

int CFGameLevel::getPetInitSpeed(){
    if(pet == NULL){
        return 0;
    }
    return CFCocosUtil::getIntFromDict(pet, "initSpeed", 0);
}

int CFGameLevel::getPetFeedStatus(){
    if(pet == NULL){
        return NULL;
    }
    return CFCocosUtil::getIntFromDict(pet, "feedStatus", -1);
}

CCDictionary* CFGameLevel::checkPetWords(CFGameLevelListener* listener){
    if(pet == NULL){
        return NULL;
    }
    CCArray* array = (CCArray*)pet->objectForKey("words");
    if(array == NULL){
        return NULL;
    }
    int index = CFCocosUtil::getIntFromDict(pet, "currentWordIndex", 0);
    if(index >= array->count()){
        return NULL;
    }
    CCDictionary* words = (CCDictionary*)array->objectAtIndex(index);
    if(words == NULL){
        return NULL;
    }
    int petTask = CFCocosUtil::getIntFromDict(pet, "currentPetTask", 0);
    int task = CFCocosUtil::getIntFromDict(words, "task", petTask);
    if(task>petTask){
        pet->setObject(CCString::createWithFormat("%i", task), "currentPetTask");
        petTask = task;
    }
    //CCLog("index:%i, petTask:%i, task：%i,currentTask:%i", index,petTask, task, this->getCurrentTask());
    if(task > this->getCurrentTask()){
        return NULL;
    }
    pet->setObject(CCString::createWithFormat("%i", index+1), "currentWordIndex");
    return words;
}

void CFGameLevel::updatePetWordsIndex(){
    if(pet == NULL){
        return;
    }
    CCObject* words = pet->objectForKey("words");
    if(words == NULL){
        return;
    }
    CCArray* array = (CCArray*) words;
    if(array == NULL){
        return;
    }
    int index = CFCocosUtil::getIntFromDict(pet, "currentWordIndex", 0);
    if(index >= array->count()){
        return;
    }
    pet->setObject(CCString::createWithFormat("%i", ++index), "currentWordIndex");

}

const char* CFGameLevel::checkTaskStories(CFGameLevelListener *listener){
    if(this->tasks == NULL){
        return NULL;
    }
    if(currentTask >= this->tasks->count()){
        return NULL;
    }
    CCDictionary* task = (CCDictionary*)this->tasks->objectAtIndex(currentTask);
    if(task == NULL){
        return NULL;
    }
    CCArray* stories = (CCArray*)task->objectForKey("stories");
    if(stories == NULL){
        return NULL;
    }
    int index = CFCocosUtil::getIntFromDict(task, "currentStoryIndex", 0);
    if(index > stories->count()){
        listener->onGameTaskOngoing(task, currentTask);
        return NULL;
    }
    if(index == stories->count()){
        task->setObject(CCString::createWithFormat("%i", ++index), "currentStoryIndex");
        listener->onGameTaskStart(task, currentTask);
        listener->onGameTaskOngoing(task, currentTask);
        return NULL;
    }
    const char* story = CFCocosUtil::getStringFromArray(stories, index, NULL);
    task->setObject(CCString::createWithFormat("%i", ++index), "currentStoryIndex");
    if(story == NULL){
        return NULL;
    }
    listener->onGameTaskStory(task, currentTask);
    return story;
}

bool CFGameLevel::checkTaskComplete(int princeStatus,CFGameLevelListener* listener){
    if(this->tasks == NULL){
        return false;
    }
    if(currentTask >= this->tasks->count()){
        return false;
    }
    CCDictionary* task = (CCDictionary*)this->tasks->objectAtIndex(currentTask);
    if(task == NULL){
        return false;
    }
    int completeStatus = CFCocosUtil::getIntFromDict(task, "status", -1);
    //CCLog("%i:%i", princeStatus, completeStatus);
    if(princeStatus == completeStatus){
        listener->onGameTaskComplete(task, currentTask);
        //this->updatePetWordsIndex();
        //this->updatePlanetItemWordIndex();
        currentTask += 1;
        if(currentTask == this->tasks->count()){
            listener->onGamePass(this->pet, 0);
        }
        return true;
    }else{
        return false;
    }
    return false;
}

int CFGameLevel::getCurrentTask(){
    return currentTask;
}

int CFGameLevel::getCurrentTaskStatus(){
    if(this->tasks == NULL){
        return -1;
    }
    if(currentTask >= this->tasks->count()){
        return -1;
    }
    CCDictionary* task = (CCDictionary*)this->tasks->objectAtIndex(currentTask);
    if(task == NULL){
        return false;
    }
    return CFCocosUtil::getIntFromDict(task, "status", -1);
}