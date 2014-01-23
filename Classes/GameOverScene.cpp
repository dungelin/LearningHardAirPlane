#include "GameOverScene.h"
GameOverScene::GameOverScene(void)
{
	gameOverLayer=NULL;
	score=0;
}
GameOverScene::~GameOverScene(void)
{

}

GameOverScene* GameOverScene::create(int passScore)
{
	GameOverScene *pRet = new GameOverScene();
	// ÉèÖÃ·ÖÊý
	pRet->score=passScore;
	if (pRet && pRet->init()) 
	{ 
		pRet->autorelease(); 
		return pRet; 
	} 
	else 
	{ 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	} 
}
bool GameOverScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
	gameOverLayer =GameOverLayer::create(score);
	this->addChild(gameOverLayer);
	return true;
}