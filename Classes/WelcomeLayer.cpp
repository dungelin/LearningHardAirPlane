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
	// 把图片添加进全局的精灵框帧缓存
	// CCSpriteFrameCache主要服务于多张碎图片合并起来的纹理图片
	// 精灵通过切换不同的框帧来显示不同的图案
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot_background.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot.plist");

	// 获得窗体大小
	CCSize winSize =CCDirector::sharedDirector()->getWinSize();

	// 添加背景图片并设置显示位置
	CCSprite *background =CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("background.png"));
	background->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(background);

	// 添加版权图片并设置显示位置
	CCSprite *copyright =CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("shoot_copyright.png"));
	//copyright->setAnchorPoint(ccp(0.5,0.5));
	copyright->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(copyright);

	//添加loading图片并设置位置
	CCSprite* loading=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
	loading->setPosition(ccp(winSize.width/2,winSize.height/2-40));
	this->addChild(loading);

	// 创建一个动画对象
	CCAnimation *animation =CCAnimation::create();
	// 设置每帧播放的时间间隔为0.2秒
	animation->setDelayPerUnit(0.2f);
	// 为动画添加四个帧
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading1.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading2.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading3.png"));
	animation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("game_loading4.png"));

	// 创建动画动作，动画动作由动画对象创建，并由精灵执行
	CCAnimate *animate =CCAnimate::create(animation);
	// 创建一个重复性动作，设置该动作重复2次
	CCRepeat *repeataction=CCRepeat::create(animate,2);
	// 创建方法调用动作，loadingDone方法在播放完动画后被调用
	CCCallFuncN *repeatDone =CCCallFuncN::create(this,callfuncN_selector(WelcomeLayer::loadingDone));
	// 创建序列动作，即动作集合，集合动作会按照顺序执行
	CCSequence *sequenceaction =CCSequence::create(repeataction,repeatDone,NULL);
	// 让精灵执行序列动作
	loading->runAction(sequenceaction);

	// 获得历史最高分数
	getHighestHistoryScore();

	// 设置接收键盘事件为true
	this->setKeypadEnabled(true);
	return true;
}

// 执行完动画后回调方法
void WelcomeLayer::loadingDone(CCNode* pNode)
{
	CCScene *gameScene =GameScene::create();
	// 创建从下边移动到上边场景特效
	CCTransitionMoveInB *animateScene =CCTransitionMoveInB::create(0.05f,gameScene);
	// 切换创建，使游戏场景可见，WelcomeScene被替代
	CCDirector::sharedDirector()->replaceScene(animateScene);
}

// 获得历史最高分数
void WelcomeLayer::getHighestHistoryScore()
{
	if (isHaveHistoryScore())
	{
		GameOverLayer::highestHistoryScore=CCUserDefault::sharedUserDefault()->getIntegerForKey("HighestScore",0);
	}
}
// Android返回键被按下
void WelcomeLayer::keyBackClicked()
{
	// 调用end方法来结束场景，并退出应用
	CCDirector::sharedDirector()->end();
}
// 保持历史记录
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
