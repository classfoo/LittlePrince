#ifndef _H_CCGAMESCROLLVIEW_H_
#define _H_CCGAMESCROLLVIEW_H_

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

// 校正滑动动画速度
#define ADJUST_ANIM_VELOCITY 2000

class CFScrollViewDelegate
	: public CCScrollViewDelegate
{
public:
	virtual bool scrollViewInitPage(CCNode *pScroll, CCNode *pPage, int nPage) = 0;
	virtual void scrollViewClick(const CCPoint &oOffset, const CCPoint &oPoint , CCNode *pPage, int nPage ) = 0;
	virtual void scrollViewScrollEnd(CCNode *pPage, int nPage) = 0;
};

class CFScrollView
	: public CCScrollView
{
protected:
	void adjustScrollView(const CCPoint &oBegin, const CCPoint &oEnd);
	virtual void onScrollEnd(float fDelay);
	int m_nPageCount;
	int m_nPrePage;
	CCPoint m_BeginOffset;
	CCSize m_CellSize;
	float m_fAdjustSpeed;
	bool m_bSetDirection;
	int m_nCurPage;
public:
	CFScrollView(void);
	virtual ~CFScrollView(void);
	CREATE_FUNC(CFScrollView);
	bool init();
	bool createContainer(CFScrollViewDelegate *pDele, int nCount, const CCSize &oSize );
	virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
	virtual void ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent );
	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );
	virtual void ccTouchCancelled( CCTouch *pTouch, cocos2d::CCEvent *pEvent );
	virtual void setDirection(CCScrollViewDirection eDirection);
	void setCurPage(int nPage);
	void scrollToPage(int nPage);
	void scrollToNextPage();
	void scrollToPrePage();
	int getPageCount();
	int getCurPage();
	CCNode *getPage(int nPage);
};

#endif

