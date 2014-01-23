#include "PlaneLayer.h"
#include "GameOverScene.h"

PlaneLayer* PlaneLayer::sharePlane=NULL;
PlaneLayer::PlaneLayer(void)
{
	isAlive=true;
	score=0;
}

PlaneLayer::~PlaneLayer(void)
{

}
bool PlaneLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();

	CCSprite *plane =CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
	plane->setPosition(ccp(winSize.width/2,plane->getContentSize().height/2));
	this->addChild(plane,0,AIRPLANE);

	// ��˸���󣬵�һ������Ϊ��˸Ч������ʱ�䣬�ڶ�������Ϊ��˸�Ĵ���
	CCBlink *blink =CCBlink::create(1,3);
	
	CCAnimation *animation =CCAnimation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero1.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2.png"));
	CCAnimate *animate =CCAnimate::create(animation);

	// �ɾ���ִ�ж�������
	plane->runAction(blink);
	plane->runAction(CCRepeatForever::create(animate));
	return true;
}


// �ɻ��ƶ�
void PlaneLayer::MoveTo(CCPoint location)
{
if (isAlive&&!CCDirector::sharedDirector()->isPaused())
{
	CCPoint actualPoint;
	CCSize winSize =CCDirector::sharedDirector()->getWinSize();
	CCSize planeSize =this->getChildByTag(AIRPLANE)->getContentSize();
	
	// Ϊ�˱�֤�ɻ����Ƴ���Ļ�����ұ߽�
	if (location.x<planeSize.width/2)
	{
		location.x=planeSize.width/2;
	}
	if (location.x>winSize.width-planeSize.width/2)
	{
		location.x=winSize.width-planeSize.width/2;
	}
	// Ϊ�˱�֤�ɻ����Ƴ���Ļ�����±߽�
	if (location.y<planeSize.height/2)
	{
		location.y=planeSize.width/2+10;
	}
	if (location.y>winSize.height-planeSize.height/2)
	{
		location.y=winSize.height-planeSize.height/2;
	}
	this->getChildByTag(AIRPLANE)->setPosition(location);
}
}
// �ɻ���ը
void PlaneLayer::Blowup( int passScore )
{
	if (isAlive)
	{
		isAlive=false;
		score=passScore;
		
		CCAnimation *animation =CCAnimation::create();
		animation->setDelayPerUnit(0.2f);
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n1.png"));	
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n2.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n3.png"));
		animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero_blowup_n4.png"));

		CCAnimate *animate =CCAnimate::create(animation);
		CCCallFunc *removePlane =CCCallFunc::create(this,callfunc_selector(PlaneLayer::RemovePlane));
		CCSequence *sequence =CCSequence::create(animate,removePlane,NULL);
		this->getChildByTag(AIRPLANE)->stopAllActions();
		this->getChildByTag(AIRPLANE)->runAction(sequence);
	}
}
void PlaneLayer::RemovePlane()
{
	this->removeChildByTag(AIRPLANE,true);
	GameOverScene *pScene =GameOverScene::create(score);
	CCTransitionMoveInT *animateScene =CCTransitionMoveInT::create(0.8f,pScene);
	CCDirector::sharedDirector()->replaceScene(animateScene);
}