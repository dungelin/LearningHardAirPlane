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
#include "Enemy.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

const int ENEMY1_MAXLIFE=1;
const int ENEMY2_MAXLIFE=2;
const int ENEMY3_MAXLIFE=5;

enum Level
{
	EASY,
	MIDDLE,
	HARD,
};

class EnemyLayer :public CCLayer
{
public:
	EnemyLayer(void);
	~EnemyLayer(void);

	CREATE_FUNC(EnemyLayer);
	virtual bool init();

	void addEnemy1(float dt);
	void enemy1MoveFinished(CCNode* pSender);
	void enemy1Blowup(Enemy* enemy1);
	void removeEnemy1(CCNode* pTarget, void* data);
	void removeAllEnemy1();

	void addEnemy2(float dt);
	void enemy2MoveFinished(CCNode* pSender);
	void enemy2Blowup(Enemy* enemy2);
	void removeEnemy2(CCNode* pTarget, void* data);
	void removeAllEnemy2();

	void addEnemy3(float dt);
	void enemy3MoveFinished(CCNode* pSender);
	void enemy3Blowup(Enemy* enemy3);
	void removeEnemy3(CCNode* pTarget, void* data);
	void removeAllEnemy3();

	void removeAllEnemy();

	CCArray* enemy1Array;
	CCArray* enemy2Array;
	CCArray* enemy3Array;

private:

	CCSpriteFrame* enemy1SpriteFrame;
	CCSpriteFrame* enemy2SpriteFrame;
	CCSpriteFrame* enemy3SpriteFrame_1;
	CCSpriteFrame* enemy3SpriteFrame_2;
};