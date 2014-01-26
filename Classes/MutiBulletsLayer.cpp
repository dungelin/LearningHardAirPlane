#include "MutiBulletsLayer.h"
#include "PlaneLayer.h"


MutiBulletsLayer::MutiBulletsLayer( void )
{
	mutiBulletsBatchNode=NULL;

	mutiBulletsArray=CCArray::create();
	mutiBulletsArray->retain();
}

MutiBulletsLayer::~MutiBulletsLayer( void )
{
	mutiBulletsArray->release();
	mutiBulletsArray=NULL;
}

bool MutiBulletsLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->textureForKey("ui/shoot.png");
	mutiBulletsBatchNode = CCSpriteBatchNode::createWithTexture(texture);
	this->addChild(mutiBulletsBatchNode);
	return true;
}

void MutiBulletsLayer::StartShoot( float delay/*=0.0f*/ )
{
	this->schedule(schedule_selector(MutiBulletsLayer::AddMutiBullets),0.2f,30,0.0f);
}

void MutiBulletsLayer::StopShoot()
{
	this->unschedule(schedule_selector(MutiBulletsLayer::AddMutiBullets));
}

void MutiBulletsLayer::AddMutiBullets( float dt )
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/bullet.mp3");

	CCSprite* bulletLeft=CCSprite::createWithSpriteFrameName("bullet2.png");
	CCSprite* bulletRight=CCSprite::createWithSpriteFrameName("bullet2.png");
	mutiBulletsBatchNode->addChild(bulletLeft);
	mutiBulletsBatchNode->addChild(bulletRight);
	this->mutiBulletsArray->addObject(bulletLeft);
	this->mutiBulletsArray->addObject(bulletRight);

	CCPoint planePosition=PlaneLayer::sharePlane->getChildByTag(AIRPLANE)->getPosition();
	CCPoint bulletLeftPosition=ccp(planePosition.x-33,planePosition.y+35);
	CCPoint bulletRightPosition=ccp(planePosition.x+33,planePosition.y+35);
	bulletLeft->setPosition(bulletLeftPosition);
	bulletRight->setPosition(bulletRightPosition);

	float length=CCDirector::sharedDirector()->getWinSize().height+bulletLeft->getContentSize().height/2-bulletLeftPosition.y;
	float velocity=1300/1;//1300pixel/sec
	float realMoveDuration=length/velocity;

	CCFiniteTimeAction* actionLeftMove=CCMoveTo::create(realMoveDuration,ccp(bulletLeftPosition.x,CCDirector::sharedDirector()->getWinSize().height+bulletLeft->getContentSize().height/2+60));
	CCFiniteTimeAction* actionLeftDone=CCCallFuncN::create(this,callfuncN_selector(MutiBulletsLayer::mutibulletsMoveFinished));
	CCSequence* sequenceLeft=CCSequence::create(actionLeftMove,actionLeftDone,NULL);

	CCFiniteTimeAction* actionRightMove=CCMoveTo::create(realMoveDuration,ccp(bulletRightPosition.x,CCDirector::sharedDirector()->getWinSize().height+bulletRight->getContentSize().height/2));
	CCFiniteTimeAction* actionRightDone=CCCallFuncN::create(this,callfuncN_selector(MutiBulletsLayer::mutibulletsMoveFinished));
	CCSequence* sequenceRight=CCSequence::create(actionRightMove,actionRightDone,NULL);

	bulletLeft->runAction(sequenceLeft);
	bulletRight->runAction(sequenceRight);
}

void MutiBulletsLayer::mutibulletsMoveFinished( CCNode *pSender )
{
	CCSprite *mutiBullets =(CCSprite*)pSender;
	this->mutiBulletsArray->removeObject(mutiBullets);
	this->mutiBulletsBatchNode->removeChild(mutiBullets,true);
	CCLog("MutiBuletsCout=&d",mutiBulletsArray->count());
}

void MutiBulletsLayer::RemoveMutiBullets( CCSprite *mutiBullets )
{
	if (mutiBullets!=NULL)
	{
		this->mutiBulletsArray->removeObject(mutiBullets);
		this->mutiBulletsBatchNode->removeChild(mutiBullets,true);
	}
}




