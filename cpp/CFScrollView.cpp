#include "CFScrollView.h"

CFScrollView::CFScrollView()
	: m_fAdjustSpeed(ADJUST_ANIM_VELOCITY)
	, m_bSetDirection(false)
	, m_nCurPage(0)
{

}

CFScrollView::~CFScrollView()
{

}

bool CFScrollView::init()
{
	if (!CCScrollView::init())
	{
		return false;
	}

	return true;
}


bool CFScrollView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	m_BeginOffset = getContentOffset();
	return CCScrollView::ccTouchBegan(pTouch, pEvent);
}

void CFScrollView::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCScrollView::ccTouchMoved(pTouch, pEvent);
}

void CFScrollView::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint touchPoint = pTouch->getLocationInView();
	touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );

	CCScrollView::ccTouchEnded(pTouch, pEvent);

	CCPoint m_EndOffset = getContentOffset();

	//点击Page的功能
	if (m_BeginOffset.equals(m_EndOffset))
	{
		int nPage = -1;
		if (m_eDirection == kCCScrollViewDirectionHorizontal)
		{
			nPage = abs(m_EndOffset.x / (int)m_CellSize.width);
		}
		else
		{
			nPage = abs(m_EndOffset.y / (int)m_CellSize.height);
		}
		CFScrollViewDelegate *pDele = (CFScrollViewDelegate *)m_pDelegate;
		CCNode *pPgae = m_pContainer->getChildByTag(nPage);
		CCRect rcContent;
		rcContent.origin = pPgae->getPosition();
		rcContent.size = pPgae->getContentSize();
		rcContent.origin.x -= rcContent.size.width / 2;
		rcContent.origin.y -= rcContent.size.height / 2;

		CCPoint pos = touchPoint;
		if (m_eDirection == kCCScrollViewDirectionHorizontal)
		{
			pos.x += nPage * m_CellSize.width;
		}
		else
		{
			pos.y -= nPage * m_CellSize.height;
		}

		if (rcContent.containsPoint(pos))
		{
			pDele->scrollViewClick(m_EndOffset, touchPoint, pPgae, nPage);
		}
		return ;
	}

	//自动调整
	adjustScrollView(m_BeginOffset, m_EndOffset);
}

void CFScrollView::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	CCScrollView::ccTouchCancelled(pTouch, pEvent);

	CCPoint m_EndOffset = getContentOffset();
	adjustScrollView(m_BeginOffset, m_EndOffset);
}


void CFScrollView::adjustScrollView( const CCPoint &oBegin, const CCPoint &oEnd)
{
	int nPage = 0;
	int nAdjustPage = 0;

	if (m_eDirection == kCCScrollViewDirectionHorizontal)
	{
		nPage = abs(oBegin.x / (int)m_CellSize.width);
		int nDis = oEnd.x - oBegin.x;

		if (nDis < -getViewSize().width / 5)
		{
			nAdjustPage = nPage + 1;
		}
		else if (nDis > getViewSize().width / 5)
		{
			nAdjustPage = nPage - 1;
		}
		else
		{
			nAdjustPage = nPage;
		}
	}
	else
	{
		nPage = abs(oBegin.y / (int)m_CellSize.height);
		int nDis = oEnd.y - oBegin.y;

		if (nDis < -getViewSize().height / 5)
		{
			nAdjustPage = nPage - 1;
		}
		else if (nDis > getViewSize().height / 5)
		{
			nAdjustPage = nPage + 1;
		}
		else
		{
			nAdjustPage = nPage;
		}
	}

	nAdjustPage = MIN(nAdjustPage, m_nPageCount - 1);
	nAdjustPage = MAX(nAdjustPage, 0);

	scrollToPage(nAdjustPage);
}


void CFScrollView::scrollToPage( int nPage )
{
	// 关闭CCScrollView中的自调整
	unscheduleAllSelectors();

	CCPoint oOffset = getContentOffset();
	// 调整位置
	CCPoint adjustPos;
	if (m_eDirection == kCCScrollViewDirectionHorizontal)
	{
		adjustPos = ccp(-m_CellSize.width * nPage, 0);
	}
	else
	{
		adjustPos = ccp(0, m_CellSize.height * nPage);
	}
	// 调整动画时间
	float adjustAnimDelay = ccpDistance(adjustPos, oOffset) / m_fAdjustSpeed;

	// 调整位置
	setContentOffsetInDuration(adjustPos, adjustAnimDelay);

	if (nPage != m_nCurPage)
	{
		m_nCurPage = nPage;
		scheduleOnce(schedule_selector(CFScrollView::onScrollEnd), adjustAnimDelay);
	}
}


void CFScrollView::onScrollEnd(float fDelay)
{
	CFScrollViewDelegate *pDele = (CFScrollViewDelegate *)m_pDelegate;
	pDele->scrollViewScrollEnd(m_pContainer->getChildByTag(m_nCurPage), m_nCurPage);
}



void CFScrollView::scrollToNextPage()
{
	int nCurPage = getCurPage();
	if (nCurPage >= m_nPageCount - 1)
	{
		return ;
	}
	scrollToPage(nCurPage + 1);
}

void CFScrollView::scrollToPrePage()
{
	int nCurPage = getCurPage();
	if (nCurPage <= 0)
	{
		return ;
	}
	scrollToPage(nCurPage - 1);
}


bool CFScrollView::createContainer(CFScrollViewDelegate *pDele, int nCount, const CCSize &oSize)
{
	CCAssert(m_bSetDirection, "must call setDirection first!!!");
	m_nPageCount = nCount;
	m_CellSize = oSize;
	setDelegate(pDele);
	CCLayer *pContainer = CCLayer::create();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	for (int i = 0; i < nCount; ++i)
	{
		CCNode *pNode = CCNode::create();
		pDele->scrollViewInitPage(this, pNode, i);
		CCObject *pObj = NULL;
		if (m_eDirection == kCCScrollViewDirectionHorizontal)
		{
			pNode->setPosition(ccp(winSize.width / 2 + i * oSize.width, winSize.height / 2));
		}
		else
		{
			pNode->setPosition(ccp(winSize.width / 2, winSize.height / 2 - i * oSize.height));
		}
		CCSize oMaxSize;
		CCARRAY_FOREACH(pNode->getChildren(), pObj)
		{
			CCNode *pNode = (CCNode *)pObj;
			oMaxSize.width = MAX(oMaxSize.width, pNode->getContentSize().width);
			oMaxSize.height = MAX(oMaxSize.height, pNode->getContentSize().height);
		}
		pNode->setContentSize(oMaxSize);
		pNode->setTag(i);
		pContainer->addChild(pNode);
	}
	setContainer(pContainer);
	return true;
}

int CFScrollView::getCurPage()
{
	return m_nCurPage;
}

void CFScrollView::setCurPage( int nPage )
{
	CCAssert(m_nCurPage >= 0 && m_nCurPage < m_nPageCount, "");

	if (m_eDirection == kCCScrollViewDirectionHorizontal)
	{
		setContentOffset(ccp(-nPage * m_CellSize.width, 0));
	}
	else
	{
		setContentOffset(ccp(0, nPage * m_CellSize.height));
	}
	m_nCurPage = nPage;
}

int CFScrollView::getPageCount()
{
	return m_nPageCount;
}

CCNode *CFScrollView::getPage( int nPage )
{
	return m_pContainer->getChildByTag(nPage);
}

void CFScrollView::setDirection( CCScrollViewDirection eDirection )
{
	CCAssert(eDirection != kCCScrollViewDirectionBoth, "Does not suppost kCCScrollViewDirectionBoth!!!");
	CCScrollView::setDirection(eDirection);
	m_bSetDirection = true;
}
