#include "WelcomeLayer.h"
#include "GameScene.h"
#include "GameOverLayer.h"

WelcomeLayer::WelcomeLayer(void)
{
}
WelcomeLayer::~WelcomeLayer(void)
{
}

bool WelcomeLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	// ��ͼƬ��ӽ�ȫ�ֵľ����֡����
	// CCSpriteFrameCache��Ҫ�����ڶ�����ͼƬ�ϲ�����������ͼƬ
	// ����ͨ���л���ͬ�Ŀ�֡����ʾ��ͬ��ͼ��
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot_background.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot.plist");

	// ��ô����С
	CCSize winSize =CCDirector::sharedDirector()->getWinSize();

	// ��ӱ���ͼƬ��������ʾλ��
	CCSprite *background =CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
	background->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(background);

	// ��Ӱ�ȨͼƬ��������ʾλ��
	CCSprite *copyright =CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("shoot_copyright.png"));
	//copyright->setAnchorPoint(ccp(0.5,0.5));
	copyright->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(copyright);

	//���loadingͼƬ������λ��
	CCSprite* loading=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
	loading->setPosition(ccp(winSize.width/2,winSize.height/2-40));
	this->addChild(loading);

	// ����һ����������
	CCAnimation *animation =CCAnimation::create();
	// ����ÿ֡���ŵ�ʱ����Ϊ0.2��
	animation->setDelayPerUnit(0.2f);
	// Ϊ��������ĸ�֡
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading2.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading3.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading4.png"));

	// �����������������������ɶ������󴴽������ɾ���ִ��
	CCAnimate *animate =CCAnimate::create(animation);
	// ����һ���ظ��Զ��������øö����ظ�2��
	CCRepeat *repeataction=CCRepeat::create(animate,2);
	// �����������ö�����loadingDone�����ڲ����궯���󱻵���
	CCCallFuncN *repeatDone =CCCallFuncN::create(this,callfuncN_selector(WelcomeLayer::loadingDone));
	// �������ж��������������ϣ����϶����ᰴ��˳��ִ��
	CCSequence *sequenceaction =CCSequence::create(repeataction,repeatDone,NULL);
	// �þ���ִ�����ж���
	loading->runAction(sequenceaction);

	// �����ʷ��߷���
	getHighestHistoryScore();

	// ���ý��ռ����¼�Ϊtrue
	this->setKeypadEnabled(true);
	return true;
}

// ִ���궯����ص�����
void WelcomeLayer::loadingDone(CCNode* pNode)
{
	CCScene *gameScene =GameScene::create();
	// �������±��ƶ����ϱ߳�����Ч
	CCTransitionMoveInB *animateScene =CCTransitionMoveInB::create(0.05f,gameScene);
	// �л�������ʹ��Ϸ�����ɼ���WelcomeScene�����
	CCDirector::sharedDirector()->replaceScene(animateScene);
}

// �����ʷ��߷���
void WelcomeLayer::getHighestHistoryScore()
{
	if (isHaveHistoryScore())
	{
		GameOverLayer::highestHistoryScore=CCUserDefault::sharedUserDefault()->getIntegerForKey("HighestScore",0);
	}
}
// Android���ؼ�������
void WelcomeLayer::keyBackClicked()
{
	// ����end�������������������˳�Ӧ��
	CCDirector::sharedDirector()->end();
}
// ������ʷ��¼
bool WelcomeLayer::isHaveHistoryScore()
{
	if (!CCUserDefault::sharedUserDefault()->getBoolForKey("isHaveHistoryScore"))
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("isHaveHistoryScore",true);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("HighestScore",0);
		CCUserDefault::sharedUserDefault()->flush();
		return false;
	} 
	else
	{
		return true;
	}
}
