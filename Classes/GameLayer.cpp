#include "GameLayer.h"
#include "Enemy.h"

GameLayer::GameLayer(void)
{
	background1=NULL;
	background2=NULL;

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
		// ¼ÓÔØ±³¾°ÒôÀÖ
		if (!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3",true);
		}

		// ¼ÓÔØ±³¾°Í¼Æ¬1
		background1=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background1->setAnchorPoint(ccp(0,0));
		background1->setPosition(ccp(0,0));
		this->addChild(background1);

		//¼ÓÔØbackground2
		background2=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
		background2->setAnchorPoint(ccp(0,0));
		background2->setPosition(ccp(0,background2->getContentSize().height-2));
		this->addChild(background2);

		//¼ÓÈëplaneLayer
		this->planeLayer=PlaneLayer::create();
		this->addChild(planeLayer);

		//ÉèÖÃ¿É´¥Ãş
		this->setTouchEnabled(true);

		//Ö´ĞĞÈÎÎñ¼Æ»®
		this->schedule(schedule_selector(GameLayer::backgroundMove),0.01f);

		//Åö×²¼ì²â
		this->scheduleUpdate();

		//ÉèÖÃ°´¼üÓĞĞ§
		this->setKeypadEnabled(true);
		return true;
}

// ±³¾°¹ö¶¯
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

}

void GameLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void GameLayer::registerWithTouchDispatcher()
{

}

void GameLayer::update( float delta )
{

}

void GameLayer::menuBigBoomCallback( CCObject* pSender )
{

}

void GameLayer::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}
