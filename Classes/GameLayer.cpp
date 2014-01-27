#include "GameLayer.h"
#include "Enemy.h"

Level GameLayer::level=EASY;

GameLayer::GameLayer(void)
{
	background1=NULL;
	background2=NULL;

	planeLayer=NULL;
	bulletLayer=NULL;
	mutiBulletsLayer=NULL;
	controlLayer=NULL;
	enemyLayer=NULL;

	score=0;
	bigBoomCount=0;
}
GameLayer::~GameLayer(void)
{

}

bool GameLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
		// 加载背景音乐
		if (!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3",true);
		}

		// 加载背景图片1
		background1=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background1->setAnchorPoint(ccp(0,0));
		background1->setPosition(ccp(0,0));
		this->addChild(background1);

		//加载background2
		background2=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background2->setAnchorPoint(ccp(0,0));
		background2->setPosition(ccp(0,background2->getContentSize().height-2));
		this->addChild(background2);

		//加入planeLayer
		this->planeLayer=PlaneLayer::create();
		this->addChild(planeLayer);

		//加入bulletLayer
		this->bulletLayer=BulletLayer::create();
		this->addChild(bulletLayer);
		this->bulletLayer->StartShoot();


		// 加入mutiBulletsLayer层
		this->mutiBulletsLayer =MutiBulletsLayer::create();
		this->addChild(mutiBulletsLayer);

		// 加入enemyLayer
		this->enemyLayer=EnemyLayer::create();
		this->addChild(enemyLayer);

		// 加入controlLayer
		this->controlLayer=ControlLayer::create();
		this->addChild(controlLayer);
		
		// 加入SkillLayer
		this->skillLayer=SkillLayer::create();
		this->addChild(skillLayer);

		//设置可触摸
		this->setTouchEnabled(true);

		//执行任务计划
		this->schedule(schedule_selector(GameLayer::backgroundMove),0.01f);

		//碰撞检测
		this->scheduleUpdate();

		//设置按键有效
		this->setKeypadEnabled(true);

		return true;
}

// 背景滚动
void GameLayer::backgroundMove(float dt)
{
	background1->setPositionY(background1->getPositionY()-2);
	background2->setPositionY(background1->getPositionY()+background1->getContentSize().height-2);
	if (background2->getPositionY()==0)
	{
		background1->setPositionY(0);
	}
}

bool GameLayer::ccTouchBegan( CCTouch *pTouch,CCEvent *pEvent )
{
	return true;
}

void GameLayer::ccTouchMoved( CCTouch *pTouch,CCEvent *pEvent )
{
	if (this->planeLayer->isAlive)
	{
		CCPoint endPoint =pTouch->getLocationInView();
		endPoint =CCDirector::sharedDirector()->convertToGL(endPoint);
		CCSize winSize =CCDirector::sharedDirector()->getWinSize();
		// 判断拖动区域
		CCRect dragRect =CCRectMake(0.0f,0.0f,winSize.width,winSize.height);
		if (dragRect.containsPoint(this->getParent()->convertTouchToNodeSpace(pTouch)))
		{
			CCPoint beginPoint =pTouch->getPreviousLocationInView();
			beginPoint =CCDirector::sharedDirector()->convertToGL(beginPoint);

			CCPoint offset =ccpSub(endPoint,beginPoint);
			CCPoint toPoint =ccpAdd(this->planeLayer->getChildByTag(AIRPLANE)->getPosition(),offset);
			this->planeLayer->MoveTo(toPoint);
		}
	}
}

void GameLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void GameLayer::registerWithTouchDispatcher()
{
	CCDirector *pDirector =CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

void GameLayer::update( float delta )
{
	// 更新难度
	// 分数越高难道越大，难度指的飞机降落速度变快
	if (level==EASY && score>=1000000)
	{
		level=MIDDLE;
	}
	else if (level==MIDDLE && score>=2000000)
	{
		level=HARD;
	}

	CCArray *bulletsToDelete =CCArray::create();
	bulletsToDelete->retain();
	CCObject *bult;
	CCObject *enemy;
	CCObject *ut;

	// 针对敌机1来迭代子弹数组
	CCARRAY_FOREACH(this->bulletLayer->bulletArray,bult)
	{
		CCSprite *bullet =(CCSprite*)bult;

		CCArray *enemy1ToDeleteArray =CCArray::create();
		enemy1ToDeleteArray->retain();
		int a=this->enemyLayer->enemy1Array->capacity();
		CCARRAY_FOREACH(this->enemyLayer->enemy1Array,enemy)
		{
			Enemy *enemy1=(Enemy*)enemy;
			// 子弹碰撞到敌机1
			if (bullet->boundingBox().intersectsRect(enemy1->getBoundingBox()))
			{
				enemy1->loseLife();
				bulletsToDelete->addObject(bullet);
				enemy1ToDeleteArray->addObject(enemy1);
				score+=ENEMY1_SCORE;
				// 更新分数
				this->controlLayer->updateScore(score);
			}
		}
		CCARRAY_FOREACH(enemy1ToDeleteArray,enemy)
		{
			Enemy* enemy1=(Enemy*)enemy;
			this->enemyLayer->enemy1Blowup(enemy1);
		}
		enemy1ToDeleteArray->release();
	}
	CCARRAY_FOREACH(bulletsToDelete,bult)
	{
		CCSprite* bullet=(CCSprite*)bult;
		this->bulletLayer->RemoveBullet(bullet);
	}
	bulletsToDelete->removeAllObjects();
		
	// 针对敌机2的情况来的迭代子弹数组
	CCARRAY_FOREACH(this->bulletLayer->bulletArray,bult)
	{
		CCSprite* bullet=(CCSprite*)bult;

		CCArray* enemy2ToDeleteArray=CCArray::create();
		enemy2ToDeleteArray->retain();
		CCARRAY_FOREACH(this->enemyLayer->enemy2Array,enemy)
		{
			Enemy* enemy2=(Enemy*)enemy;
			if (bullet->boundingBox().intersectsRect(enemy2->getBoundingBox()))
			{
				if (enemy2->getLife()>1)
				{
					enemy2->loseLife();
					bulletsToDelete->addObject(bullet);
				}
				else if(enemy2->getLife()==1)
				{
					enemy2->loseLife();
					bulletsToDelete->addObject(bullet);
					enemy2ToDeleteArray->addObject(enemy2);
					score+=ENEMY2_SCORE;
					this->controlLayer->updateScore(score);
				}
			}
		}
		CCARRAY_FOREACH(enemy2ToDeleteArray,enemy)
		{
			Enemy* enemy2=(Enemy*)enemy;
			this->enemyLayer->enemy2Blowup(enemy2);
		}
		enemy2ToDeleteArray->release();
	}

	CCARRAY_FOREACH(bulletsToDelete,bult)
	{
		CCSprite* bullet=(CCSprite*)bult;
		this->bulletLayer->RemoveBullet(bullet);
	}
	bulletsToDelete->removeAllObjects();

	//针对敌机3的情况来的迭代子弹数组
	CCARRAY_FOREACH(this->bulletLayer->bulletArray,bult)
	{
		CCSprite* bullet=(CCSprite*)bult;

		CCArray* enemy3sToDelete=CCArray::create();
		enemy3sToDelete->retain();
		CCARRAY_FOREACH(this->enemyLayer->enemy3Array,enemy)
		{
			Enemy* enemy3=(Enemy*)enemy;
			if (bullet->boundingBox().intersectsRect(enemy3->getBoundingBox()))
			{
				//如果life>1,移除bullet
				if (enemy3->getLife()>1)
				{
					enemy3->loseLife();
					bulletsToDelete->addObject(bullet);
				}
				//如果life==1,移除enemy3
				else if(enemy3->getLife()==1)
				{
					enemy3->loseLife();
					bulletsToDelete->addObject(bullet);
					enemy3sToDelete->addObject(enemy3);
					score+=ENEMY3_SCORE;
					this->controlLayer->updateScore(score);
				}
				//此时处在animate阶段,不做处理
				//else ;
			}
		}
		CCARRAY_FOREACH(enemy3sToDelete,enemy)
		{
			Enemy* enemy3=(Enemy*)enemy;
			this->enemyLayer->enemy3Blowup(enemy3);
		}
		enemy3sToDelete->release();
	}
	CCARRAY_FOREACH(bulletsToDelete,bult)
	{
		CCSprite* bullet=(CCSprite*)bult;
		this->bulletLayer->RemoveBullet(bullet);
	}
	bulletsToDelete->removeAllObjects();

	bulletsToDelete->release();

	CCArray* mutiBulletsToDelete=CCArray::create();
	mutiBulletsToDelete->retain();
	CCObject* mutibt;

	// 针对敌机1迭代双排子弹数组
	CCARRAY_FOREACH(this->mutiBulletsLayer->mutiBulletsArray,mutibt)
	{
		CCSprite *mutiBullets=(CCSprite*)mutibt;

		CCArray *enemy1ToDeleteArray =CCArray::create();
		enemy1ToDeleteArray->retain();
		CCARRAY_FOREACH(this->enemyLayer->enemy1Array,enemy)
		{
			Enemy *enemy1 =(Enemy*)enemy;

			if (mutiBullets->boundingBox().intersectsRect(enemy1->getBoundingBox()))
			{
				if (enemy1->getLife()==1)
				{
					enemy1->loseLife();
					mutiBulletsToDelete->addObject(mutiBullets);
					enemy1ToDeleteArray->addObject(enemy1);
					score+=ENEMY1_SCORE;
					this->controlLayer->updateScore(score);
				}
			}
		}
		CCARRAY_FOREACH(enemy1ToDeleteArray,enemy)
		{
			Enemy* enemy1=(Enemy*)enemy;
			this->enemyLayer->enemy1Blowup(enemy1);
		}
		enemy1ToDeleteArray->release();
	}
	CCARRAY_FOREACH(mutiBulletsToDelete,mutibt)
	{
		CCSprite* mutiBullets=(CCSprite*)mutibt;
		this->mutiBulletsLayer->RemoveMutiBullets(mutiBullets);
	}
	mutiBulletsToDelete->removeAllObjects();

	// 针对敌机2迭代双排子弹数组
	CCARRAY_FOREACH(this->mutiBulletsLayer->mutiBulletsArray,mutibt)
	{
		CCSprite* mutiBullets=(CCSprite*)mutibt;

		CCArray* enemy2ToDeleteArray=CCArray::create();
		enemy2ToDeleteArray->retain();
		CCARRAY_FOREACH(this->enemyLayer->enemy2Array,enemy)
		{
			Enemy* enemy2=(Enemy*)enemy;
			if (mutiBullets->boundingBox().intersectsRect(enemy2->getBoundingBox()))
			{
				if (enemy2->getLife()>1)
				{
					enemy2->loseLife();
					mutiBulletsToDelete->addObject(mutiBullets);
				}
				else if(enemy2->getLife()==1)
				{
					enemy2->loseLife();
					mutiBulletsToDelete->addObject(mutiBullets);
					enemy2ToDeleteArray->addObject(enemy2);
					score+=ENEMY2_SCORE;
					this->controlLayer->updateScore(score);
				}
			}
		}
		CCARRAY_FOREACH(enemy2ToDeleteArray,enemy)
		{
			Enemy* enemy2=(Enemy*)enemy;
			this->enemyLayer->enemy2Blowup(enemy2);
		}
		enemy2ToDeleteArray->release();
	}
	CCARRAY_FOREACH(mutiBulletsToDelete,mutibt)
	{
		CCSprite* mutiBullets=(CCSprite*)mutibt;
		this->mutiBulletsLayer->RemoveMutiBullets(mutiBullets);
	}
	mutiBulletsToDelete->removeAllObjects();

	//针对敌机3迭代双排子弹数组
	CCARRAY_FOREACH(this->mutiBulletsLayer->mutiBulletsArray,mutibt)
	{
		CCSprite* mutiBullets=(CCSprite*)mutibt;

		CCArray* enemy3ToDeleteArray=CCArray::create();
		enemy3ToDeleteArray->retain();
		CCARRAY_FOREACH(this->enemyLayer->enemy3Array,enemy)
		{
			Enemy* enemy3=(Enemy*)enemy;
			if (mutiBullets->boundingBox().intersectsRect(enemy3->getBoundingBox()))
			{
				//如果life>1,移除bullet
				if (enemy3->getLife()>1)
				{
					enemy3->loseLife();
					mutiBulletsToDelete->addObject(mutiBullets);
				}
				//如果life==1,移除enemy3
				else if(enemy3->getLife()==1)
				{
					enemy3->loseLife();
					mutiBulletsToDelete->addObject(mutiBullets);
					enemy3ToDeleteArray->addObject(enemy3);
					score+=ENEMY3_SCORE;
					this->controlLayer->updateScore(score);
				}
				//此时处在animate阶段,不做处理
				//else ;
			}
		}
		CCARRAY_FOREACH(enemy3ToDeleteArray,enemy)
		{
			Enemy* enemy3=(Enemy*)enemy;
			this->enemyLayer->enemy3Blowup(enemy3);
		}
		enemy3ToDeleteArray->release();
	}
	CCARRAY_FOREACH(mutiBulletsToDelete,mutibt)
	{
		CCSprite* mutiBullets=(CCSprite*)mutibt;
		this->mutiBulletsLayer->RemoveMutiBullets(mutiBullets);
	}
	mutiBulletsToDelete->removeAllObjects();
	mutiBulletsToDelete->release();

	CCRect airPlaneRect =this->planeLayer->getChildByTag(AIRPLANE)->boundingBox();
	airPlaneRect.origin.x+=30;
	airPlaneRect.size.width-=60;

	// 如果飞机碰到敌机1的情况
	CCARRAY_FOREACH(this->enemyLayer->enemy1Array,enemy)
	{
		Enemy *enemy1 =(Enemy*)enemy;
		if (enemy1->getLife()>0)
		{
			if (airPlaneRect.intersectsRect(enemy1->getBoundingBox()))
			{
				// 卸载所有任务计划
				this->unscheduleAllSelectors();
				this->bulletLayer->StopShoot();
				this->mutiBulletsLayer->StopShoot();

				// 飞机死亡，即游戏结束了
				this->planeLayer->Blowup(score);
				return;
			}
		}
	}

	// 如果飞机碰到敌机2的情况
	CCARRAY_FOREACH(this->enemyLayer->enemy2Array,enemy)
	{
		Enemy* enemy2=(Enemy*)enemy;
		if (enemy2->getLife()>0)
		{
			if (airPlaneRect.intersectsRect(enemy2->getBoundingBox()))
			{
				//卸载所有任务计划
				this->unscheduleAllSelectors();
				this->bulletLayer->StopShoot();
				this->mutiBulletsLayer->StopShoot();
				this->planeLayer->Blowup(score);
				return;
			}
		}
	}

	// 如果飞机碰到敌机3的情况
	CCARRAY_FOREACH(this->enemyLayer->enemy3Array,enemy)
	{
		Enemy* enemy3=(Enemy*)enemy;
		if (enemy3->getLife()>0)
		{
			if (airPlaneRect.intersectsRect(enemy3->getBoundingBox()))
			{
				//卸载所有任务计划
				this->unscheduleAllSelectors();
				this->bulletLayer->StopShoot();
				this->mutiBulletsLayer->StopShoot();
				this->planeLayer->Blowup(score);
				return;
			}
		}
	}

	// 接到双排子弹技能包
	CCARRAY_FOREACH(this->skillLayer->mutiBulletsArray,ut)
	{
		CCSprite* mutiBullets=(CCSprite*)ut;
		if (this->planeLayer->getChildByTag(AIRPLANE)->boundingBox().intersectsRect(mutiBullets->boundingBox()))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/get_double_laser.mp3");
			this->skillLayer->RemoveMutiBullets(mutiBullets);
			this->bulletLayer->StopShoot();
			this->mutiBulletsLayer->StartShoot();
			this->bulletLayer->StartShoot(6.2f);
		}
	}

	// 全屏爆炸情况
	CCARRAY_FOREACH(this->skillLayer->bigBoomArray,ut)
	{
		CCSprite* bigBoom=(CCSprite*)ut;
		if (this->planeLayer->getChildByTag(AIRPLANE)->boundingBox().intersectsRect(bigBoom->boundingBox()))
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/get_bomb.mp3");
			this->skillLayer->RemoveBigBoom(bigBoom);
			bigBoomCount++;
			updateBigBoomItem(bigBoomCount);
		}
	}
}

// 更新炸弹菜单
void GameLayer::updateBigBoomItem( int bigBoomCount )
{
	CCSprite* normalBomb=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bomb.png"));
	CCSprite* pressedBomb=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bomb.png"));
	if (bigBoomCount<0)
	{
		return;
	}
	else if (bigBoomCount==0)
	{
		if (this->getChildByTag(TAG_BIGBOOM_MENUITEM))
		{
			this->removeChildByTag(TAG_BIGBOOM_MENUITEM,true);
		}
		if (this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL))
		{
			this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL,true);
		}
	}
	else if (bigBoomCount==1)
	{
		if (!this->getActionByTag(TAG_BIGBOOM_MENUITEM))
		{
			// 添加bigBoomItem菜单
			CCMenuItemImage *pBigBoomItem =CCMenuItemImage::create();
			pBigBoomItem->initWithNormalSprite(normalBomb,pressedBomb,NULL,this,menu_selector(GameLayer::menuBigBoomCallback));
			pBigBoomItem->setPosition(ccp(normalBomb->getContentSize().width/2+10,normalBomb->getContentSize().height/2+10));
			menuBigBoom=CCMenu::create(pBigBoomItem,NULL);
			menuBigBoom->setPosition(CCPointZero);
			this->addChild(menuBigBoom,0,TAG_BIGBOOM_MENUITEM);
		}
		if (this->getActionByTag(TAG_BIGBOOMCOUNT_LABEL))
		{
			this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL);
		}
	}
	else
	{
		if (!this->getChildByTag(TAG_BIGBOOM_MENUITEM))
		{
			CCMenuItemImage* pBigBoomItem=CCMenuItemImage::create();
			pBigBoomItem->initWithNormalSprite(normalBomb,pressedBomb,NULL,this,menu_selector(GameLayer::menuBigBoomCallback));
			pBigBoomItem->setPosition(ccp(normalBomb->getContentSize().width/2+10,normalBomb->getContentSize().height/2+10));
			menuBigBoom=CCMenu::create(pBigBoomItem,NULL);
			menuBigBoom->setPosition(CCPointZero);
			this->addChild(menuBigBoom,0,TAG_BIGBOOM_MENUITEM);
		}
		if (this->getChildByTag(TAG_BIGBOOMCOUNT_LABEL))
		{
			this->removeChildByTag(TAG_BIGBOOMCOUNT_LABEL,true);
		}
		if (bigBoomCount>=0 && bigBoomCount<=MAX_BIGBOOM_COUNT)
		{
			CCString* strScore=CCString::createWithFormat("X%d",bigBoomCount);
			bigBoomCountItem=CCLabelBMFont::create(strScore->m_sString.c_str(),"font/font.fnt");
			bigBoomCountItem->setColor(ccc3(143,146,147));
			bigBoomCountItem->setAnchorPoint(ccp(0,0.5));
			bigBoomCountItem->setPosition(ccp(normalBomb->getContentSize().width+15,normalBomb->getContentSize().height/2+5));
			this->addChild(bigBoomCountItem,0,TAG_BIGBOOMCOUNT_LABEL);
		}
	}
}

void GameLayer::menuBigBoomCallback( CCObject* pSender )
{
	if(bigBoomCount>0 && !CCDirector::sharedDirector()->isPaused())
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/use_bomb.mp3");
		bigBoomCount--;
		score+=this->enemyLayer->enemy1Array->count()*ENEMY1_SCORE;
		score+=this->enemyLayer->enemy2Array->count()*ENEMY2_SCORE;
		score+=this->enemyLayer->enemy3Array->count()*ENEMY3_SCORE;
		this->enemyLayer->removeAllEnemy();
		updateBigBoomItem(bigBoomCount);
		this->controlLayer->updateScore(score);
	}
}

void GameLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}

Level GameLayer::getCurLevel()
{
	return level;
}


