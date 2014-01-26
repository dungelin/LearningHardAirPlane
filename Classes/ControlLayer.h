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

#include "NoTouchLayer.h"

USING_NS_CC;

const int MAX_SCORE=1000000000;

class ControlLayer :
	public CCLayer
{
public:

	ControlLayer(void);

	~ControlLayer(void);

	virtual bool init();

	CREATE_FUNC(ControlLayer);

	void menuPauseCallback(CCObject* pSender);

	void updateScore(int score);

public:

	CCLabelBMFont* scoreItem;

	CCMenuItemImage* pPauseItem;

	NoTouchLayer* noTouchLayer;
};