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
 * fellow developer, all that I expect and request for is to be given the 
 * credit for initially developing this reusable code by not removing my name as 
 * the author.
\***************************************************************************/ 

#pragma once
#include "cocos2d.h"
#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"

// ����cocos2d�����ռ�
USING_NS_CC;

class WelcomeScene: public CCScene
{
public:
	WelcomeScene(void);
	~WelcomeScene(void);
	virtual bool init();
	CREATE_FUNC(WelcomeScene);
	void PreloadMusic();
	WelcomeLayer* welcomeLayer;
};