#include "GameScene.h"

GameScene::GameScene(void)
{
	
}

GameScene::~GameScene(void)
{
}
bool GameScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
	gameLayer =GameLayer::create();
	if (!gameLayer)
	{
		return false;
	}
	this->addChild(gameLayer);

	return true;
}