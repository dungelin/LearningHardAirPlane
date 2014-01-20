#include "WelcomeLayer.h"

WelcomeScene::WelcomeScene(void)
{
	welcomeLayer=NULL;
}
WelcomeScene::~WelcomeScene(void)
{

}
// 初始化方法
bool WelcomeScene::init()
{
	if(!CCScene::init())
	{
		return false;
	}

	welcomeLayer=WelcomeLayer::create();
	this->addChild(welcomeLayer);
	// 预加载音乐
	PreloadMusic();

	return true;
}

// 预加载音乐方法实现
void WelcomeScene::PreloadMusic()
{
	// 预加载Resources\sound下所有音乐文件
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound/game_music.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/bullet.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/enemy1_down.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/enemy2_down.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/enemy3_down.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/game_over.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/get_bomb.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/get_double_laser.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/use_bomb.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/big_spaceship_flying.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/achievement.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/out_porp.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/button.mp3");

	// 播放背景音乐
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3",true);
}