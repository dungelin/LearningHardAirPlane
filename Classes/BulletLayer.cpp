#include "BulletLayer.h"
#include "PlaneLayer.h"

BulletLayer::BulletLayer(void)
{
	
	bulletBatchNode=NULL;
	bulletArray=CCArray::create();
	bulletArray->retain();
}

BulletLayer::~BulletLayer(void)
{
	bulletArray->release();
	bulletArray=NULL;
}
void BulletLayer::StartShoot(float delay)
{
	this->schedule(schedule_selector(BulletLayer::AddBullet),0.2f,kCCRepeatForever,delay);
}
void BulletLayer::StopShoot()
{
	this->unschedule(schedule_selector(BulletLayer::AddBullet));
}
bool BulletLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	CCTexture2D *texture =CCTextureCache::sharedTextureCache()->textureForKey("ui/shoot.png");
	bulletBatchNode =CCSpriteBatchNode::createWithTexture(texture);
	this->addChild(bulletBatchNode);

	return true;
}

void BulletLayer::AddBullet(float dt)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/bullet.mp3");
	CCSprite *bullet=CCSprite::createWithSpriteFrameName("bullet1.png");
	bulletBatchNode->addChild(bullet);
	this->bulletArray->addObject(bullet);

	CCPoint planePosition=PlaneLayer::sharePlane->getChildByTag(AIRPLANE)->getPosition();
	CCPoint bulletPosition=ccp(planePosition.x,planePosition.y+PlaneLayer::sharePlane->getChildByTag(AIRPLANE)->getContentSize().height/2+60);
	bullet->setPosition(bulletPosition);

	float length=CCDirector::sharedDirector()->getWinSize().height+bullet->getContentSize().height/2-bulletPosition.y;
	float velocity=1200/1;//1200pixel/sec
	float realMoveDuration=length/velocity;

	// 创建一个延时动作，该工作持续时间为realMoveDuration
	CCFiniteTimeAction* actionMove=CCMoveTo::create(realMoveDuration,ccp(bulletPosition.x,CCDirector::sharedDirector()->getWinSize().height+bullet->getContentSize().height/2));
	CCFiniteTimeAction* actionDone=CCCallFuncN::create(this,callfuncN_selector(BulletLayer::bulletMoveFinished));

	CCSequence* sequence=CCSequence::create(actionMove,actionDone,NULL);
	bullet->runAction(sequence);
}

void BulletLayer::bulletMoveFinished(CCNode *pSender)
{
	CCSprite *bullet =(CCSprite*)pSender;
	this->bulletBatchNode->removeChild(bullet,true);
	this->bulletArray->removeObject(bullet);
}

void BulletLayer::RemoveBullet(CCSprite *bullet)
{
	if (bullet!=NULL)
	{
		this->bulletBatchNode->removeChild(bullet,true);
		this->bulletArray->removeObject(bullet);
	}
}