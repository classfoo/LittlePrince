#ifndef __Asteroid__CFGameBoard__
#define __Asteroid__CFGameBoard__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "CFGameContext.h"
#include "CFScrollView.h"
#include "CFLabel.h"
#include <stddef.h>
USING_NS_CC;

class CFGameBoard : public CFGameBoardContext,public CFScrollViewDelegate
{
private:
    CFGameContext* context;
    CFScrollView* m_ScrollView;
    CCSprite* createScrollViewPage(int level, CFGameLevel* gamelevel, const char* image, bool pause);
public:
    CFGameBoard(void);
    virtual ~CFGameBoard(void);
    static CFGameBoard* create(CFGameContext* context);
    virtual bool init();
    void loadMenus();
    
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

	virtual void scrollViewDidScroll( CCScrollView *view );
	virtual void scrollViewDidZoom( CCScrollView *view );
	virtual bool scrollViewInitPage( CCNode *pScroll, CCNode *pPage, int nPage );
	virtual void scrollViewClick( const CCPoint &oOffset, const CCPoint &oPoint , CCNode *pPage, int nPage );
	virtual void scrollViewScrollEnd( CCNode *pPage, int nPage );
    CREATE_FUNC(CFGameBoard);
};

#endif
