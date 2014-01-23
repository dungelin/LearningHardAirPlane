/****************************** Module Header ******************************\ 
 * Author:  LearningHard 
 * Email:   794170314@qq.com
 * QQ:		794170314
 * Blog:	http://www.cnblogs.com/zhili/
 * Copyright (c) LearningHard. 
 *  
 * This sample demonstrates how to create master detail ListBox in Windows Store app 
 *    
 * This piece of code does not have any registered copyright and is free to be 
 * used as necessary. The user is free to modify as per the requirements. As a
 * fellow developer, I expect is not to remove the name of Author.
\***************************************************************************/

#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "PlaneLayer.h"

USING_NS_CC;

class GameLayer:public CCLayer
{
public:
	GameLayer(void);
	~GameLayer(void);
	CREATE_FUNC(GameLayer);
    virtual bool init();
	void backgroundMove(float dt);

	bool ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent);
	
	void ccTouchMoved(CCTouch *pTouch,CCEvent *pEvent);

	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void registerWithTouchDispatcher();
	void update(float delta);

	void menuBigBoomCallback(CCObject* pSender);

	void updateBigBoomItem(int bigBoomCount);
	virtual void keyBackClicked();
	
private:
	CCSprite *background1;
	CCSprite *background2;

	// 游戏层中的其他层
	PlaneLayer  *planeLayer;

	CCMenu *menuBigBoom;
	CCLabelBMFont *bigBoomCountItem;

	int score;
	int bigBoomCount;
};
