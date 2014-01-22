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
 * credit for intially developing this reusable code by not removing my name as 
 * the author.
\***************************************************************************/ 
#pragma  once
#include "cocos2d.h"
USING_NS_CC;
class WelcomeLayer:public CCLayer
{
public:
	WelcomeLayer(void);
	~WelcomeLayer(void);
	virtual bool init();
	CREATE_FUNC(WelcomeLayer);

	void loadingDone(CCNode* pNode);

	// Android返回键被按下时调用的方法
	virtual void keyBackClicked();
	bool isHaveHistoryScore();
	void getHighestHistoryScore();
};