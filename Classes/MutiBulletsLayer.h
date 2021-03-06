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
 * fellow developer, I expect is not to remove the name of Author
\***************************************************************************/ 

#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class MutiBulletsLayer:public CCLayer
{
public:
	MutiBulletsLayer(void);
	~MutiBulletsLayer(void);

	CREATE_FUNC(MutiBulletsLayer);

	virtual bool init();

	void AddMutiBullets(float dt);
	void mutibulletsMoveFinished(CCNode *pSender);
	void RemoveMutiBullets(CCSprite *mutiBullets);
	void StartShoot(float delay=0.0f);
	void StopShoot();
	CCArray *mutiBulletsArray;
	
	CCSpriteBatchNode *mutiBulletsBatchNode;
};