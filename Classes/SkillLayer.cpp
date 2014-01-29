#include "SkillLayer.h"


SkillLayer::SkillLayer( void )
{
	mutiBulletsArray=CCArray::create();
	mutiBulletsArray->retain();
	bigBoomArray=CCArray::create();
	bigBoomArray->retain();
}

SkillLayer::~SkillLayer( void )
{
	mutiBulletsArray->release();
	mutiBulletsArray=NULL;
	bigBoomArray->release();
	bigBoomArray=NULL;
}

bool SkillLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	this->schedule(schedule_selector(SkillLayer::AddMutiBullets),20.0);
	this->schedule(schedule_selector(SkillLayer::AddBigBoom),20.0,kCCRepeatForever,5.0);
	return true;
}

void SkillLayer::AddMutiBullets( float dt )
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/out_porp.mp3");
	CCSprite* mutiBullets=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ufo1.png"));

	CCSize mutiBlletsSize=mutiBullets->getContentSize();
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	int minX=mutiBlletsSize.width/2;
	int maxX=winSize.width-mutiBlletsSize.width/2;
	int rangeX=maxX-minX;
	int actualX=(rand()%rangeX)+minX;

	mutiBullets->setPosition(ccp(actualX,winSize.height+mutiBlletsSize.height/2));
	this->addChild(mutiBullets);
	this->mutiBulletsArray->addObject(mutiBullets);

	CCMoveBy* move1 = CCMoveBy::create(0.5f, CCPointMake(0, -150));
	CCMoveBy* move2 = CCMoveBy::create(0.3f, CCPointMake(0, 100));
	CCMoveBy* move3 = CCMoveBy::create(1.0f, CCPointMake(0,0-winSize.height-mutiBlletsSize.height/2));
	CCCallFuncN* moveDone = CCCallFuncN::create(this,callfuncN_selector(SkillLayer::mutiBulletsMoveFinished));

	CCFiniteTimeAction* sequence = CCSequence::create(move1,move2,move3,moveDone,NULL);
	mutiBullets->runAction(sequence);
}

void SkillLayer::mutiBulletsMoveFinished( CCNode* pSender )
{
	CCSprite* mutiBullets=(CCSprite*)pSender;
	// 从屏幕中移除
	this->removeChild(mutiBullets,true);
	//从数组中移除
	this->mutiBulletsArray->removeObject(mutiBullets);
}

void SkillLayer::AddBigBoom( float dt )
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/out_porp.mp3");
	CCSprite* bigBoom=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ufo2.png"));

	CCSize bigBoomSize=bigBoom->getContentSize();
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	int minX=bigBoomSize.width/2;
	int maxX=winSize.width-bigBoomSize.width/2;
	int rangeX=maxX-minX;
	int actualX=(rand()%rangeX)+minX;

	bigBoom->setPosition(ccp(actualX,winSize.height+bigBoomSize.height/2));
	this->addChild(bigBoom);
	this->bigBoomArray->addObject(bigBoom);

	CCMoveBy* move1 = CCMoveBy::create(0.5, CCPointMake(0, -150));
	CCMoveBy* move2 = CCMoveBy::create(0.3, CCPointMake(0, 100));
	CCMoveBy* move3 = CCMoveBy::create(1.0, CCPointMake(0,0-winSize.height-bigBoomSize.height/2));
	CCCallFuncN* moveDone = CCCallFuncN::create(this,callfuncN_selector(SkillLayer::bigBoomMoveFinished));

	CCFiniteTimeAction* sequence = CCSequence::create(move1,move2,move3,moveDone,NULL);
	bigBoom->runAction(sequence);
}

void SkillLayer::bigBoomMoveFinished( CCNode* pSender )
{
	CCSprite* bigBoom=(CCSprite*)pSender;
	this->removeChild(bigBoom,true);
	this->bigBoomArray->removeObject(bigBoom);
}

void SkillLayer::RemoveMutiBullets( CCSprite* mutiBullets )
{
	this->removeChild(mutiBullets,true);
	this->mutiBulletsArray->removeObject(mutiBullets);
}

void SkillLayer::RemoveBigBoom(CCSprite* bigBoom)
{
	this->removeChild(bigBoom,true);
	this->bigBoomArray->removeObject(bigBoom);
}
