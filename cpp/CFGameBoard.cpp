#include "CFGameBoard.h"

CFGameBoard::CFGameBoard(){

}

CFGameBoard::~CFGameBoard(){

}

CFGameBoard* CFGameBoard::create(CFGameContext* context){
    CFGameBoard* board = new CFGameBoard();
    board->context = context;
    board->autorelease();
    return board;
}

bool CFGameBoard::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(! CCNode::init());
        this->loadMenus();
        bRet = true;
    } while (0);
    
    return bRet;
}

void CFGameBoard::loadMenus(){
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //scroll selector
    m_ScrollView = CFScrollView::create();
	m_ScrollView->setDirection(kCCScrollViewDirectionHorizontal);
	m_ScrollView->createContainer(this, 12, CCSizeMake(size.width , size.height));
	m_ScrollView->setPosition(ccp(0,0));
	m_ScrollView->setViewSize(CCDirector::sharedDirector()->getWinSize());
	this->addChild(m_ScrollView);

    //close menu
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png","CloseSelected.png",this->context,SEL_MenuHandler(&CFGameContext::closeGame));
    pCloseItem->setPosition(ccp(origin.x  + pCloseItem->getContentSize().width/2 ,origin.y + size.height - pCloseItem->getContentSize().height/2));
    CCMenu* closeMenu = CCMenu::create(pCloseItem, NULL);
    closeMenu->setPosition(CCPointZero);
    this->addChild(closeMenu, 1);
}

void CFGameBoard::onStartGame(CCObject* pSender){
    this->setVisible(false);
    this->m_ScrollView->setTouchEnabled(false);
}

void CFGameBoard::onPauseGame(cocos2d::CCObject *pSender){
    this->setVisible(true);
    this->m_ScrollView->setTouchEnabled(true);
    int nPage = this->m_ScrollView->getCurPage();
    cocos2d::CCNode* page = this->m_ScrollView->getPage(nPage);
    page->removeAllChildrenWithCleanup(true);
    ccLanguageType lang = CCApplication::sharedApplication()->getCurrentLanguage();
    switch (lang) {
        case cocos2d::kLanguageChinese:{
            CCSprite* menu = this->createScrollViewPage(nPage+1, this->context->getCurrentLevel(), "游戏暂停中", true);
            page->addChild(menu);
            break;
        }
        case cocos2d::kLanguageFrench:{
            CCSprite* menu = this->createScrollViewPage(nPage+1, this->context->getCurrentLevel(), "jeu pause", true);
            page->addChild(menu);
            break;
        }
        case cocos2d::kLanguageKorean:{
            CCSprite* menu = this->createScrollViewPage(nPage+1, this->context->getCurrentLevel(), "게임 일시 중지", true);
            page->addChild(menu);
            break;
        }
        case cocos2d::kLanguageJapanese:{
            CCSprite* menu = this->createScrollViewPage(nPage+1, this->context->getCurrentLevel(), "ゲームの一時停止", true);
            page->addChild(menu);
            break;
        }
        default:{
            CCSprite* menu = this->createScrollViewPage(nPage+1, this->context->getCurrentLevel(), "Game Paused", true);
            page->addChild(menu);
            break;
        }
    }
}

void CFGameBoard::onResumeGame(cocos2d::CCObject *pSender){
    this->setVisible(false);
    this->m_ScrollView->setTouchEnabled(false);
}

void CFGameBoard::onCloseGame(CCObject* pSender){
}

void CFGameBoard::onPassGame(cocos2d::CCObject *pSender){
}

void CFGameBoard::onChangeToLevel(cocos2d::CCObject *pSender, int level){
    if(m_ScrollView == NULL){
        return;
    }
    CCNode* pPage = m_ScrollView->getPage(level-1);
    if(pPage == NULL){
        return;
    }
    pPage->removeAllChildrenWithCleanup(true);
    CCSprite* sprite = this->createScrollViewPage(level, this->context->getCurrentLevel(), NULL, false);
    pPage->addChild(sprite);

    m_ScrollView->setCurPage(level-1);
    m_ScrollView->setVisible(true);
    this->context->playEffect("hit.mp3", false);
}

void CFGameBoard::onBeforePassGame(){

}

void CFGameBoard::onDoPassGame(){

}

void CFGameBoard::onAfterPassGame(){
}

void CFGameBoard::scrollViewDidScroll( CCScrollView *view ){
    this->context->getSpaceContext()->jump(700000);
}

void CFGameBoard::scrollViewDidZoom( CCScrollView *view ){
    this->context->getSpaceContext()->jump(-700000);
}

//初始化每个单独页面,pPage为这个页面的容器,nPage是这个页面的ID
bool CFGameBoard::scrollViewInitPage( cocos2d::CCNode *pScroll, cocos2d::CCNode *pPage, int nPage )
{
    if(nPage < 0 || nPage>11){
        return false;
    }
    //CCSprite* sprite = this->createScrollViewPage(nPage + 1, this->context->getCurrentLevel(), NULL, false);
	//pPage->addChild(sprite);
	return false;
}

//点击某个页面的处理
void CFGameBoard::scrollViewClick( const cocos2d::CCPoint &oOffset, const cocos2d::CCPoint &oPoint , cocos2d::CCNode *pPage, int nPage )
{

}

//每一次滑动后结束的回调,可以在这里处理一些事情
void CFGameBoard::scrollViewScrollEnd( cocos2d::CCNode *pPage, int nPage )
{
    if(nPage+1>12||nPage<0){
        return;
    }
    this->context->changeToLevel(nPage+1);

}

//创建关卡选择菜单sprite
CCSprite* CFGameBoard::createScrollViewPage(int level, CFGameLevel* gamelevel, const char* text, bool pause){
	CCSprite *sprite = CCSprite::create("level.png");
    ccColor3B color = gamelevel->getLevelColor();
    sprite->setColor(color);
    if(text == NULL){
        ccColor3B fontColor = ccc3(255, 255, 255);
        CFLabel* levelName = CFLabel::create(gamelevel->getLevelName(), "LevelBig.fnt", 64, fontColor);
        levelName->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(2, 1.2), CCScaleTo::create(2,1), NULL)));
        levelName->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height*8/9));
        sprite->addChild(levelName);
        CFLabel* levelDesc = CFLabel::create(gamelevel->getLevelDesc(), "LevelSmall.fnt", 32, fontColor);
        levelDesc->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(1, 1.2), CCScaleTo::create(1,1), NULL)));
        levelDesc->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height*6/9));
        sprite->addChild(levelDesc);
    }else{
        ccColor3B fontColor = ccc3(255, 255, 255);
        CFLabel* levelText = CFLabel::create(text, "LevelBig.fnt", 64, fontColor);
        levelText->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height*8/9));
        sprite->addChild(levelText);
    }
    CCMenuItemImage* item = CCMenuItemImage::create();
    item->runAction(CCRepeatForever::create(CCSequence::create(CCScaleTo::create(3, 1.1), CCScaleTo::create(3,1), NULL)));
    int currentlevel = CCUserDefault::sharedUserDefault()->getIntegerForKey("currentProgress", 1);
    if(level > currentlevel){
        item->initWithNormalImage("locked.png","locked_ontouch.png",NULL,this->context,SEL_MenuHandler(&CFGameContext::lockedGame));
    }else{
        if(pause){
            item->initWithNormalImage("pause.png","pause_ontouch.png",NULL,this->context,SEL_MenuHandler(&CFGameContext::resumeGame));
        }else{
            item->initWithNormalImage("start.png","start_ontouch.png",NULL,this->context,SEL_MenuHandler(&CFGameContext::startGame));
        }
    }
    CCMenu* menu = CCMenu::createWithItem(item);
    menu->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
    sprite->addChild(menu);
    return sprite;
}